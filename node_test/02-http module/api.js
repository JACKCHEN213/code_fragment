const fs = require("fs");

function render(res, data, type = 'application/json') {
    res.writeHead(200, {
        'Content-Type': `${type};charset=utf8`
    });
    res.write(data, 'utf-8')
    res.end()
}

const apiRoute = {
    '/api/login': (req, res) => {
        const url = new URL(req.url, 'http://127.0.0.1');
        let searchParams = url.searchParams;
        if (searchParams.get('username') === 'admin' && searchParams.get('password') === '123456') {
            render(res, '{"ok": 1}');
        } else {
            render(res, '{"ok": 0}');
        }
    },
    '/api/login_post': (req, res) => {
        let data = '';
        req.on('data', function (chunk) {
            data += chunk;
        });

        req.on('end', function () {
            data = JSON.parse(data);
            if (data.username === 'admin' && data.password === '123456') {
                render(res, '{"ok": 1}');
            } else {
                render(res, '{"ok": 0}');
            }
        })
    },
}

module.exports = {
    apiRoute
}