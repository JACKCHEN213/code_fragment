const https = require('https');

function httpGet() {
    let url = 'https://www.zhipin.com/wapi/zpgeek/common/data/city/site.json'
    return new Promise((resolve, reject) => {
        const request = https.get(url, { timeout: 1000 }, (res) => {
            if (res.statusCode < 200 || res.statusCode > 299) {
                return reject(new Error(`HTTP status code ${res.statusCode}`))
            }
            const body = []
            res.on('data', (chunk) => body.push(chunk))
            res.on('end', () => {
                const resString = Buffer.concat(body).toString()
                resolve(resString)
            })
        })
        request.on('error', (err) => {
            reject(err)
        })
        request.on('timeout', () => {
            request.destroy()
            reject(new Error('timed out'))
        })
    });
}

function httpPost() {
    let url = 'https://www.xiaomiyoupin.com/mtop/market/cat/list'
    return new Promise((resolve, reject) => {
        let options = {
            hostname: 'www.xiaomiyoupin.com',
            port: 443,
            path: '/mtop/market/cat/list',
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            }
        };
        const request = https.request(options, (res) => {
            if (res.statusCode < 200 || res.statusCode > 299) {
                return reject(new Error(`HTTP status code ${res.statusCode}`))
            }
            const body = []
            res.on('data', (chunk) => body.push(chunk))
            res.on('end', () => {
                const resString = Buffer.concat(body).toString()
                resolve(resString)
            })
        })

        request.write(JSON.stringify([{},{}]));
        request.end();
        request.on('error', (err) => {
            reject(err)
        })
        request.on('timeout', () => {
            request.destroy()
            reject(new Error('timed out'))
        })
    });
}

exports.httpGet = httpGet;
exports.httpPost = httpPost;
