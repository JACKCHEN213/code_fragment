const app = require('./server');
const {route} = require("./route");
const {apiRoute} = require("./api");

app.use(route);
app.use(apiRoute);

app.run();