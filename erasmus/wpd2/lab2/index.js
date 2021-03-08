const express = require('express');
const app = express();

const path = require('path');
const public = path.join(__dirname,'public');

// Use the public folder for static resources
app.use(express.static(public));

// () => equals function()
app.listen(3000,() => {
    console.log('Server started in port 3000. Ctrl^c to quit.');
})

// handler for the root page
app.get('/',function(req,res) {
    res.send('Hello! Welcome to my application.');
})

// handler for the /guestbook page
app.get('/guestbook',function(req,res) {
    res.send('<h1>Guestbook Messages</h1>');
})

// handler for the /about page
app.get('/about',function(req,res) {
    res.sendFile(path.join(public,'about.html'));
})

// handle a request that is not handled by any other request handler
app.use(function(req,res) {
    res.status(404);
    res.send('Oops! We didn\'t find what you are looking for.');
})