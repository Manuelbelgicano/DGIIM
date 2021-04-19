const express = require('express');
const router = express.Router();
const controller = require('../controllers/guestbookControllers');
const auth = require("../auth/auth");
const {ensureLoggedIn} = require("connect-ensure-login"); 

// Request handling with controller
router.get("/",controller.landing_page)
router.get("/posts",controller.entries_list)
router.get("/new",ensureLoggedIn("/login"),controller.new_entry)
router.get("/peter",controller.peter_entries)
router.post("/new",ensureLoggedIn("/login"),controller.post_new_entry)
router.get("/posts/:author",controller.get_user_entries)
router.get("/delete/:id",controller.delete_entry)
router.get("/register",controller.show_register_page)
router.post("/register",controller.post_new_user)
router.get("/login",controller.show_login_page)
router.post("/login",auth.authorize("/login"),controller.post_login)
//router.post("/login",controller.post_login)
router.get("/logout", controller.logout);

// Other requests
router.get("/about",function(req,res) {
    res.redirect("/about.html");
})

router.use(function(req,res) {     
    res.status(404);     
    res.type("text/plain");     
    res.send("404 Not found."); 
}) 

router.use(function(req,res) {
    res.status(401);
    res.type("text/plain");     
    res.send("401 Registration error.");
})

router.use(function(err,req,res,next) {     
    res.status(500);     
    res.type("text/plain");     
    res.send("Internal Server Error."); 
}) 

// To make router accessible form index.js
module.exports = router;