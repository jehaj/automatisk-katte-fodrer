const express = require('express');
const helmet = require('helmet');
const cors = require('cors');
const morgan = require('morgan');

const app = express();

app.use(helmet()); // basic security
app.use(morgan('tiny')); // logger
app.use(cors()); // allows any origin
app.use(express.json());