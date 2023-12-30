var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const cors = require('cors');

var indexRouter = require('./routes/index');
var userApiRouter = require('./routes/userApi');
var loginApiRouter = require('./routes/loginApi');
const JWT = require("./utils/JWT");
const UserBlackService = require('./services/UserBlackService');

var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({extended: false}));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use(cors());

app.use((req, res, next) => {
    if (req.url.includes('login')) {
        next();
        return;
    }
    let token = req.headers['authorization']?.split(' ')[1];
    if (token) {
        let payload = JWT.verify(token);
        if (payload) {
            UserBlackService.get(token).then(data => {
                if (data.length) {
                    req.url.includes('api') ? res.status(401).send({ok: 0}) : res.redirect('/login');
                } else {
                    // const newToken = JWT.generate({
                    //     _id: payload._id,
                    //     username: payload.username,
                    //     expire: new Date(Date.now() + 100),
                    // }, '1h');
                    // res.header('Authorization', newToken);
                    next();
                }
            });
        } else {
            req.url.includes('api') ? res.status(401).send({ok: 0}) : res.redirect('/login');
        }
    } else {
        next();
    }
});

app.use('/', indexRouter);
app.use('/api/user', userApiRouter);
app.use('/api/login', loginApiRouter);

// catch 404 and forward to error handler
app.use(function (req, res, next) {
    next(createError(404));
});

// error handler
app.use(function (err, req, res, next) {
    // set locals, only providing error in development
    res.locals.message = err.message;
    res.locals.error = req.app.get('env') === 'development' ? err : {};

    // render the error page
    res.status(err.status || 500);
    res.render('error');
});

module.exports = app;
