const express = require('express');

const apiRouter = express.Router();

apiRouter.get('/login', (req, res) => {
    console.log(req.query)
    res.send({
        ok: 1,
    });
});

apiRouter.post('/login', (req, res) => {
    console.log(req.body)
    res.send({
        ok: 1
    });
});

module.exports = apiRouter;
