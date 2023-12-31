const koa = require('koa');
const koaStatic = require('koa-static');
const path = require('path');
const koaBodyParser = require('koa-bodyparser');
const koaViews = require('koa-views');
const session = require('koa-session-minimal');
const multer = require('@koa/multer');
const mysql2 = require('mysql2');

const app = new koa();
const upload = multer({dest: 'public/uploads'})
const router = require('./routes');

app.use(session({
    key: 'SESSION_ID',
    cookie: {
        maxAge: 1000 * 60 * 60
    }
}));

app.use(koaBodyParser());
app.use(koaStatic(path.join(__dirname, "public")));

app.use(koaViews(path.join(__dirname, "views"), {
    extension: 'ejs',
}));
router.get('/list', async (ctx, next) => {
    console.log(ctx.cookies.get('name'))
    console.log(ctx.session);
    ctx.session.user = 'admin';
    ctx.cookies.set('name', 'jackc');

    let promisePool = mysql2.createPool({
        host: '127.0.0.1',
        port: '3306',
        user: 'root',
        password: '123456',
        database: 'jackc_test',
        connectionLimit: 1,
    }).promise();
    promisePool.query('SELECT * FROM jt_user').then(data => {
        console.log(data[0]);
    })
    await ctx.render('list', {name: 'list'});
})
router.post('/list', upload.single('file'), (ctx, next) => {
    let filepath = path.join(__dirname, '/public/uploads', ctx.file.filename);
    console.log(filepath);
    ctx.body = {ok: 1};
})

app.use(router.routes()).use(router.allowedMethods());

app.listen(3000, () => {
    console.log('server start: http://127.0.0.1:3000/')
});
