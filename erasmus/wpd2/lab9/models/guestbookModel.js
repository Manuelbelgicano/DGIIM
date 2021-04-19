const nedb = require('nedb');

class GuestBook {
    constructor(dbFilePath) {
        if (dbFilePath) {
            this.db = new nedb({filename: dbFilePath,autoload: true});
            console.log("DB connected to "+dbFilePath);
        } else {
            this.db = new nedb();
        }
    }
    init() {
        this.db.insert({
            subject: "I liked the exhibition",
            contents: "nice",
            published: "2020-02-16",
            author: "Peter"
        });
        console.log("db entry Peter inserted");

        this.db.insert({
            subject: "Didn't like it",
            contents: "it was horrible",
            published: "2020-02-17",
            author: "Wendy"
        });
        console.log("db entry Wendy inserted");
    }
    getAllEntries() {
        return new Promise((resolve,reject) => {
            this.db.find({},function(err,entries) {
                if (err) {
                    reject(err);
                } else {
                    resolve(entries);
                    console.log("Function all() returns: ",entries);
                }
            });
        });
    }
    getPeterEntries() {
        return new Promise((resolve,reject) => {
            this.db.find({author: "Peter"},function(err,entries) {
                if (err) {
                    reject(err);
                } else {
                    resolve(entries);
                    console.log("Function Peter() returns: ",entries);
                }
            });
        });
    }
    addEntry(author,subject,contents) {
        var entry = {
            author: author,
            subject: subject,
            contents: contents,
            published: new Date().toISOString().split("T")[0]
        }
        console.log("Entry created",entry);

        this.db.insert(entry,function(err,doc) {
            if (err) {
                console.log("Error inserting document",subject);
            } else {
                console.log("Entry inserted in db",entry);
            }
        });
    }

    getEntriesByUser(authorName) {
        return new Promise((resolve,reject) => {
            this.db.find({author: authorName},function(err,entries) {
                if (err) {
                    reject(err);
                } else {
                    resolve(entries);
                    console.log("Function EntriesByUser() returns: ",entries);
                }
            });
        });
    }

    deleteEntry(id) {
        this.db.remove({_id:id},{}, function(err,rem) {
            if (err) {
                console.log("Error deleting entry",err)
            } else {
                console.log(rem," entries deleted")
            }
        })
    }
}

module.exports = GuestBook;