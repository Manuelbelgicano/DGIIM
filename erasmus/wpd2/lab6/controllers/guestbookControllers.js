const guestbookDAO = require("../models/guestbookModel");
const db = new guestbookDAO();


exports.entries_list = function(req,res) {
    db.init();
    res.send("<h1>TODO: show a list of guestbook entries</h1>");
    db.getAllEntries();
}

exports.landing_page = function(req,res) {
    db.init();
    db.getAllEntries().then((list) => {
        res.render("entries", {
            "title": "GuestBook",
            "entries": list
        });
        console.log("promise resolved.");

    }).catch((err) => {
        console.log("promise rejected.");
    });
}

exports.new_entry = function(req,res) {
    db.init();
    res.send("<h1>TODO: show a new entry page</h1>");
}

exports.peter_entries = function(res,req) {
    db.init();
    db.getPeterEntries();
}