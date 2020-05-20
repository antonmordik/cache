const path = require('path');
const sqlite3 = require('sqlite3').verbose();

const db = new sqlite3.Database(path.resolve(__dirname, '../cache/storage.db'));

const getStatistics = async () => {
  return await new Promise((resolve, reject) => {
    db.all('SELECT * FROM statistics;', (error, result) => {
      if (error) { reject(error) }
      else { resolve(result) }
    })
  });
}

const getMatrixes = async () => {
  return await new Promise((resolve, reject) => {
    db.all('SELECT * FROM matrix;', (error, result) => {
      if (error) { reject(error) }
      else { resolve(result) }
    })
  });
}

module.exports = {
  getStatistics,
  getMatrixes
}