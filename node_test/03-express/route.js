const express = require('express');

const router = express.Router();

router.get('/home', (req, res) => {
    res.send('home');
});

router.get('/login', (req, res) => {
    console.log(req.query)
    res.send('login-get');
});

router.post('/login', (req, res) => {
    console.log(req.body)
    res.send('login-post');
});

module.exports = router;
