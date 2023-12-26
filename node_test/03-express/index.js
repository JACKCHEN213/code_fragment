const express = require('express');
const router = require('./route');
const api = require('./api');

const app = express();

app.set('views', './views');
app.set('view engine', 'ejs');
// app.set('view engine', 'html');
// app.engine('html', require('ejs').renderFile);

app.use(express.static('public'));

app.use(express.urlencoded({extended: false})); //text/x-www-form-urlencoded
app.use(express.json());

app.use((req, res, next) => {
    console.log('fun1');
    next();
});

app.use('/', router);
app.use('/api', api);

app.use((req, res) => {
    res.status(404).send('404');
});

app.listen(3000, () => {
    console.log('server start: http://localhost:3000/');
})