const http = require('http');

let Router = {};

function use(route) {
    Object.assign(Router, route);
}

function run() {
    http.createServer((req, res) => {
        let url = new URL(req.url, 'http://127.0.0.1');
        console.log(url.pathname)
        try {
            Router[url.pathname](req, res);
        } catch (e) {
            Router['/404'](req, res);
        }
    }).listen(9001, () => {
        console.log("server start");
    });
}

exports.run = run;
exports.use = use;
