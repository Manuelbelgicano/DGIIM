// Import nedb module
const nedb = require('nedb');

// Create a db
const db = new nedb({filename: 'students.db', autoload: true});
console.log('db created.');

// Inserting to db
db.insert({
    student: 'Peter',
    age: 20,
    programme: 'Computing',
    grant: false,
    modules: [{
        name: 'Programming',
        grade: 65
    },
    {
        name: 'Databases',
        grade: 70
    },
    {
        name: 'Networking',
        grade: 80
    }]
}, function(err,newDoc) {
    if (err) {
        console.log('error',err);
    } else {
        console.log('document inserted:',newDoc);
    }
});
db.insert({
    student: 'Ann',
    age: 21,
    programme: 'Networking',
    grant: true,
    modules: [{
        name: 'Routing',
        grade: 70
    },
    {
        name: 'Security',
        grade: 61
    },
    {
        name: 'Server Management',
        grade: 62
    }]
}, function(err,newDoc) {
    if (err) {
        console.log('error',err);
    } else {
        console.log('document inserted:',newDoc);
    }
});