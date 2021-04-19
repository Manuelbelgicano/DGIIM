const passport = require('passport');
const Strategy = require("passport-local").Strategy;
const bcrypt = require("bcrypt");
const userModel = require("../models/userModel");

exports.init = function(app) {
    // Password setup
    passport.use(new Strategy(
        function(username,password,cb) {
            userModel.lookup(username,function(err,user) {
                if (err) {
                    console.log("Error looking for user",err);
                    return cb(err);
                }
                if (!user) {
                    console.log("user ",username," not found");
                    return cb(null,false);
                }
                // Password comparing
                bcrypt.compare(password,user.password,function(err,result) {
                    if (result) {
                        console.log("User authenticated ",user);
                        cb(null,user);
                    } else {
                        console.log("Passwords don't match");
                        cb(null,false);
                    }
                });
            });
        }
    ));
    // Session handling
    passport.serializeUser(function(user,cb) {
        console.log("Serializing: ",user.user);
        cb(null,user.user);
    });
    passport.deserializeUser(function(id,cb) {
        userModel.lookup(id, function(err,user) {
            if (err) {
                console.log("Error deserializing user");
                return cb(err);
            }
            return cb(null,user);
        });
    });
}

exports.authorize = function(redirect) {
    console.log("Trying to redirect to",redirect);
    return passport.authenticate("local", {failureRedirect: redirect});
}