const express = require('express');

const router = express.Router();

router.get('/home', (req, res) => {
    console.log('views home.ejs')
    res.render('home', {
        list: ['apply', 'banana', 'cherry', 'dragon', 'elderberry'],
        show: '<h1>Welcome Start</h1>'
    });
});

router.get('/login', (req, res) => {
    // console.log(req.query)
    // res.send('login-get');  //片段 & json
    // res.json();
    console.log('views login.ejs')
    res.render('login', {error: ''});
});

// router.post('/login', (req, res) => {
//     console.log(req.body)
//     res.send('login-post');
// });

router.post('/login', (req, res) => {
    if (req.body.username === 'admin' && req.body.password === '123456') {
        res.redirect('/home');
    } else {
        res.render('login', {error: '用户名或密码错误'});
    }
});

module.exports = router;
