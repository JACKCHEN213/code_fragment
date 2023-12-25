function renderStatus(url) {
    let route = [
        '/home',
        '/list',
        '/api/home',
        '/api/list',
        '/api/jsonp',
        '/api/json',
        '/cat_eyes',
        '/xiaomi_youpin',
    ];
    return route.includes(url) ? 200 : 404;
}

module.exports = renderStatus;
