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

// Import the router
const router = require('./routes/guestbookRoutes');

// Use the router handling
app.use('/',router);