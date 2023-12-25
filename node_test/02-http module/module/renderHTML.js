const {httpGet, httpPost} = require('./httpClient');

/**
 * @param url
 * @param {ParsedUrlQuery} query
 * @returns {string}
 */
async function renderHTML(url, query = {}) {
    let data = [];
    switch (url) {
        case '/home':
            return `<h1>首页</h1>`;
        case '/list':
            return `<h1>列表</h1>`;
        case '/api/home':
            return `{"id": 1, "name": "JackC"}`;
        case '/api/list':
            return `[1,2,3,4]`;
        case '/api/jsonp':
            data = [{
                id: 1, name: 'JackC', age: 18,
            }, {
                id: 2, name: 'Alex', age: 19,
            }];
            let callback = query.callback ? query.callback : 'jsonp';
            return `${callback}(${JSON.stringify(data)})`;
        case '/api/json':
            data = [{
                id: 1, name: 'JackC', age: 18,
            }, {
                id: 2, name: 'Alex', age: 19,
            }];
            return `${JSON.stringify(data)}`;
        case '/cat_eyes':
            data = await httpGet();
            return data;
        case '/xiaomi_youpin':
            data = await httpPost();
            console.log(data)
            return data;
        default:
            return `<h1>404 not found</h1>`;
    }
}

exports.renderHTML = renderHTML
