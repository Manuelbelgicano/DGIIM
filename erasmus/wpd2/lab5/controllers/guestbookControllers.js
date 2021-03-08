const guestbookDAO = require("../models/guestbookModel");
const db = new guestbookDAO();


exports.entries_list = function(req,res) {
    res.send("<h1>TODO: show a list of guestbook entries</h1>");
    db.getAllEntries();
}

exports.landing_page = function(req,res) {
    res.send("<h1>Welcome to my application!</h1>");
    db.init();
}

exports.new_entry = function(req,res) {
    res.send("<h1>TODO: show a new entry page</h1>");
}

exports.peter_entries = function(res,req) {
    db.getPeterEntries();
}