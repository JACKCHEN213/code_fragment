const express = require('express');
const path = require("path");
const {WebSocketServer, WebSocket} = require('ws');

const wss = new WebSocketServer({port: 8080});

wss.on('connection', function connection(ws, fd) {
    ws.on('message', function message(data) {
        console.log('received: %s', data);
        ws.send('server say: fk u!');
    });

    wss.clients.forEach(function each(client) {
        if (client.readyState === WebSocket.OPEN) {
            client.send('new connection');
        }
    })

    // console.log(fd)
    // ws.send('hello world');
});

const app = express();
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');
app.use(express.static('./public'));

app.get('/', (req, res) => {
    res.render('index');
});

app.listen(3000, () => {
    console.log('server start: http://127.0.0.1:3000/')
});
