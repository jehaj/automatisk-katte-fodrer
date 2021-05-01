const express = require('express');
const helmet = require('helmet');
const cors = require('cors');
const morgan = require('morgan');

const port = 8080;
const app = express();

app.use(helmet()); // basic security
app.use(morgan('tiny')); // logger
app.use(cors()); // allows any origin
app.use(express.json());

let settings = [
    { time: "08:30", value: 5 },
    { time: "18:30", value: 3 },
];
let receivedSettings = false;

app.get('/weight', (req, res) => {

});

app.post('/weight', (req, res) => {

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
