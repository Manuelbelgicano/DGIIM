const { response } = require("express");
const guestbookDAO = require("../models/guestbookModel");
const db = new guestbookDAO();


exports.entries_list = function(req,res) {
    res.send("<h1>TODO: show a list of guestbook entries</h1>");
    db.getAllEntries();
}

exports.landing_page = function(req,res) {
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
    res.render("new-entry", {"title": "Guestbook. Add entry"});
}

exports.peter_entries = function(res,req) {
    db.getPeterEntries();
}

exports.post_new_entry = function(req,res) {
    console.log("Processing new entry controller");

    if (!req.body.author) {
        res.status(400).send("Entries must have an author");
        return;
    }
    db.addEntry(req.body.author,req.body.subject,req.body.contents);
    res.redirect("/");
}