require('dotenv').config();

const express = require('express');
const helmet = require('helmet');
const cors = require('cors');
const morgan = require('morgan');
const { Client } = require('pg');

const client = new Client({
    connectionString: process.env.DATABASE_URL
});

client.connect()
    .catch((error) => {
        console.log('Could not connect to server: ' + error);
    });

const port = process.env.PORT || 8080;
const app = express();

app.use(helmet()); // basic security
app.use(morgan('tiny')); // logger
app.use(cors()); // allows any origin
app.use(express.json()); // only allows json

let settings = [
    { time: "08:30", value: 5 },
    { time: "18:30", value: 3 },
];
let receivedSettings = false;

app.get('/weight/:before', (req, res) => {
    let valuesAfter;

    if (req.params.before == "week") {
        valuesAfter = Date.now() - 7 * 24 * 60 * 60 * 1000;
    } else if (req.params.before == "month") {
        valuesAfter = Date.now() - 30 * 24 * 60 * 60 * 1000;
    } else if (req.params.before == "year") {
        valuesAfter = Date.now() - 365 * 24 * 60 * 60 * 1000;
    } else {
        res.status(400);
        res.send({ error: "No time specified." });
    }

    // query database for weight
    client.query('SELECT * FROM aukafo WHERE insertedon > $1', [valuesAfter], (err, result) => {
        res.send(result.rows);
    });
});

app.post('/weight', (req, res) => {
    const weightValue = req.body.value;
    const timestamp = Date.now();

    // insert into database
    client.query('INSERT INTO aukafo VALUES ($1, $2)', [weightValue, timestamp], (err, res) => {
        console.log(err ? `${err}` : `Successfully inserted ${weightValue} into the db.`);
    });
    res.send({ message: "Succes" });
});

app.get('/settings', (req, res) => {
    receivedSettings = true;
    res.send(settings);
});

app.post('/settings', (req, res) => {
    settings = req.body;
    receivedSettings = false;
    res.send({message: "Successfully changed settings!"});

});

app.listen(port, () => {
    console.log(`Listening on http://127.0.0.1:${port}/`);
});

process.on('SIGINT', (code) => {
    console.log("Ending the program.");
    client.end();
});
