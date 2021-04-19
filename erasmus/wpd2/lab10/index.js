const express = require('express');
const session = require('express-session');
const router = require('./routes/guestbookRoutes');
const path = require('path');
const mustache = require('mustache-express');
const bodyParser = require('body-parser');
const auth = require('./auth/auth');
const passport = require('passport');

const app = express();
const public = path.join(__dirname, 'public');
console.log("public is:", public);
app.use(express.static('public'));
app.engine('mustache', mustache());
app.set('view engine', 'mustache');
app.use(bodyParser.urlencoded({ extended: false }));
app.use(session({ secret: "do not tell anyone", resave: false, saveUninitialized: false }));
app.use(passport.initialize());
app.use(passport.session());

// initialize authentication with passport
auth.init(app)
// Use the router handling
app.use('/',router);
// () => equals function()
app.listen(3000,() => {
    console.log('Server started in port 3000. Ctrl^c to quit.');
})