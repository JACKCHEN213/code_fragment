const fs = require("fs");
const path = require('path');
const mime = require('mime');
const zlib = require("zlib");

const gzip = zlib.createGzip();

function render(res, path, type = 'text/html') {
    res.writeHead(200, {
        'Content-Type': `${type};charset=utf8`,
        // 'Content-Encoding': 'gzip'
    });
    const readStream = fs.createReadStream(path);
    // readStream.pipe(gzip).pipe(res)
    readStream.pipe(res)
    // res.write(fs.readFileSync(path), 'utf-8')
    // res.end()
}

function readStaticFile(req, res) {
    const url = new URL(req.url, 'http://127.0.0.1');
    let fileRealPath = path.join(__dirname, '/static', url.pathname);
    if (fs.existsSync(fileRealPath)) {
        render(res, fileRealPath, mime.getType(path.extname(fileRealPath)))
        return true;
    }
    return false;
}

const route = {
    '/login': (req, res) => {
        render(res, './static/login.html');
    },
    '/home': (req, res) => {
        render(res, './static/home.html');
    },
    '/': (req, res) => {
        render(res, './static/home.html');
    },
    '/404': (req, res) => {
        if (readStaticFile(req, res)) {
            return;
        }
        res.writeHead(404, {
            'Content-Type': 'text/html;charset=utf8'
        })
        res.write(fs.readFileSync('./static/404.html'), 'utf-8')
        res.end()
    },
}

module.exports = {
    route
}