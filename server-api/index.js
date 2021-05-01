const express = require('express');
const helmet = require('helmet');
const cors = require('cors');
const morgan = require('morgan');

const port = 8080;
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

app.get('/weight', (req, res) => {
    let valuesAfter;

    if (res.body == "week") {
        valuesAfter = Date.now() - 7*24*60*60*1000;
    } else if (res.body == "month") {
        valuesAfter = Date.now() - 30*24*60*60*1000;
    } else if (res.body == "year") {
        valuesAfter = Date.now() - 365*24*60*60*1000;
    } else {
        res.status(400);
        res.send({error: "No time specified."});
    }

    // query database for weight

});

app.post('/weight', (req, res) => {
    const timestamp = Date.now();
    const weightValue = res.body;

    // insert into database
});

app.get('/settings', (req, res) => {
    receivedSettings = true;
    res.send(settings);
});

app.post('/settings', (req, res) => {
    receivedSettings = false;
    res.send();

});

app.listen(port, () => {
    console.log(`Listening on http://127.0.0.1:${port}/`);
});
