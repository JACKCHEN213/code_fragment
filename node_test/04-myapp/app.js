var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
var session = require('express-session');
var MongoStore = require('connect-mongo');

var indexRouter = require('./routes/index');
var userApiRouter = require('./routes/userApi');
var loginApiRouter = require('./routes/loginApi');

var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use(session({
  name: 'JackC',
  secret: '342d2fgb42',
  cookie: {
    maxAge: 1000 * 60 * 60,
    secure: false
  },
  resave: true,  // 重新设置session后刷新时间
  saveUninitialized: true,
  rolling: true,  // 超时前刷新，cookie会重新记值
  store: MongoStore.create({
    mongoUrl: 'mongodb://127.0.0.1:27017/jackc_session',
    ttl: 1000 * 60 * 60,
  })
}));

app.use((req, res, next) => {
  if (req.url.includes('login')) {
    next();
    return;
  }
  if (req.session.user) {
    req.session.date = Date.now();
    next()
  } else {
    req.url.includes('api') ? res.status(401).send({ok: 0}) : res.redirect('/login');
  }
});

app.use('/', indexRouter);
app.use('/api/user', userApiRouter);
app.use('/api/login', loginApiRouter);

// catch 404 and forward to error handler
app.use(function(req, res, next) {
  next(createError(404));
});

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
});

module.exports = app;
