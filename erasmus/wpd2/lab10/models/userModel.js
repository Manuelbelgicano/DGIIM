const Datastore = require("nedb")
const bcrypt = require("bcrypt")
const saltRounds = 10

class UserDAO {
    constructor(dbFilePath) {
        if(dbFilePath) {
            this.db = new Datastore({filename: dbFilePath, autoload: true});
        } else {
            this.db = new Datastore();
        }
    }

    init() {
        this.db.insert({
            user: 'Peter',
            password: '$2b$10$I82WRFuGghOMjtu3LLZW9OAMrmYOlMZjEEkh.vx.K2MM05iu5hY2C'
        });
        console.log('user record inserted in init');
        this.db.insert({
            user: 'Ann',
            password: '$2b$10$bnEYkqZM.MhEF/LycycymOeVwkQONq8kuAUGx6G5tF9UtUcaYDs3S'
        });
        console.log('user record inserted in init');
        
        return this;
    }
    create(username, password) {
        const userDB = this.db;
        bcrypt.hash(password, saltRounds).then(function(hash) {
            var entry = {
                user: username,
                password: hash,
            };
            console.log('user entry is: ', entry);
            
            userDB.insert(entry, function (err) { 
                if (err) {
                    console.log("Can't insert user: ", username);
                }
            });
        });
    }
    lookup(username, cb) {
        console.log("Looking up user: ",username);
        this.db.find({user: username}, function (err, entries) {
            if (err) {
                return cb(null, null);
            } else {
                if (entries.length == 0) {
                    return cb(null, null);
                } else {
                    console.log("User is: ",entries[0]);
                    return cb(null, entries[0]);
                }
            }
        });
    }
}

const dao = new UserDAO();
dao.init()
module.exports = dao;