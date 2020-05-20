const Koa = require('koa');
const path = require('path');
const Pug = require('koa-pug');
const opn = require('opn');
const db = require('./database');

const app = new Koa();

const pug = new Pug({
  viewPath: path.resolve(__dirname, './templates'),
  locals: {},
  helperPath: [],
  app: app,
});

app.use(async ctx => {
  const statistics = await db.getStatistics();
  const matrixes = await db.getMatrixes();
  console.log(statistics, matrixes);
  await ctx.render('index.pug');
});

app.listen(9000, () => {
  console.log('Dashboard started at http://localhost:9000/');
  opn('http://localhost:9000/');
});