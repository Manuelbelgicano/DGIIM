const { response } = require("express");
const passport = require("passport");
const guestbookDAO = require("../models/guestbookModel");
const userDAO = require("../models/userModel");
const db = new guestbookDAO();

exports.entries_list = function(req,res) {
    res.send("<h1>TODO: show a list of guestbook entries</h1>");
    db.getAllEntries();
}

exports.landing_page = function(req,res) {
    db.getAllEntries().then((list) => {
        res.render("entries", {
            "title": "GuestBook",
            "user": req.user,
            "entries": list
        });
        console.log("promise resolved.");

    }).catch((err) => {
        console.log("promise rejected.");
    });
}

exports.new_entry = function(req,res) {
    console.log("User writing is: ",req.user.user);
    res.render("new-entry", {
        "title": "Guestbook. Add entry",
        "user": req.user.user
    });
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

exports.get_user_entries = function(req,res) {
    console.log("filtering author name:",req.params.author);

    var user = req.params.author;
    db.getEntriesByUser(user).then((list) => {
        res.render("entries", {
            "title": "Guestbook",
            "entries": list
        });
        console.log("Promise resolved");
    }).catch((err) => {
        console.log("Promise rejected");
    }); 
}

exports.delete_entry = function(req,res) {
    console.log("id in delete_entry", req.params.id)
    db.deleteEntry(req.params.id)
    res.redirect("/")
}

exports.show_register_page = function(req,res) { 
    res.render("user/register"); 
}

exports.post_new_user = function(req, res) { 
    const user = req.body.username;
    const password = req.body.password;
    console.log("register user with name: ", user, " and password: ",  password);
    
    if (!user || !password) {
        console.log("Error: no user or no password");
        res.send(401, 'no user or no password'); 
        return;     
    }

    userDAO.lookup(user,function(err,name) {
        if (name) {
            console.log("Error: user exists");
            res.send(401, "User exists:", user);
            return;         
        } else {
            console.log("Saving user with name: ",user," and password: ",password);
            userDAO.create(user,password);
            res.redirect("/login");
        }   
    });
}

exports.show_login_page = function(req, res) {    
    console.log("Login page");
    res.render("user/login");
}

exports.post_login = function(req,res) {
    console.log("Redirecting...");
    res.redirect("/");
}

exports.logout = function(req, res) {
    req.logout();     
    res.redirect("/"); 
};