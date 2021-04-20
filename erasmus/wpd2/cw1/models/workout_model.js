const nedb = require('nedb');

class training_plan {
    // Constructor
    constructor(db_file_path_strength,db_file_path_cardio,db_file_path_sport) {
        // Strength collection init
        if (db_file_path_strength) {
            this.db_strength = new nedb({filename: db_file_path_strength,autoload: true});
            console.log("strength DB connected to "+db_file_path_strength);
        } else {
            this.db_strength = new nedb();
            this.db_strength.insert({
                name: "Bench press",
                weight: "30", 
                repetitions: "10"
            });
            console.log("Initial entries inserted to Strength db");
        }
        // Cardio collection init
        if (db_file_path_cardio) {
            this.db_cardio = new nedb({filename: db_file_path_cardio,autoload: true});
            console.log("Cardio DB connected to "+db_file_path_cardio);
        } else {
            this.db_cardio = new nedb();
            this.db_cardio.insert({
                name: "Cycling",
                distance: "20"
            });
            console.log("Initial entries inserted to Cardio db");
        }
        // Sports collection init
        if (db_file_path_sport) {
            this.db_sport = new nedb({filename: db_file_path_sport,autoload: true});
            console.log("strength DB connected to "+db_file_path_sport);
        } else {
            this.db_sport = new nedb();
            this.db_sport.insert({
                name: "Basketball",
                duration: "1.5"
            });
            console.log("Initial entries inserted to Sport db");
        }

    }
    // Gets all strength entries
    get_strength_entries() {
        return new Promise((resolve,reject) => {
            this.db_strength.find({},function(err,entries) {
                if (err) {
                    reject(err);
                } else {
                    resolve(entries);
                    console.log("Function 'get_strength_entries' returns:",entries);
                }
            })
        });
    }
    // Gets all cardio entries
    get_cardio_entries() {
        return new Promise((resolve,reject) => {
            this.db_cardio.find({},function(err,entries) {
                if (err) {
                    reject(err);
                } else {
                    resolve(entries);
                    console.log("Function 'get_cardio_entries' returns:",entries);
                }
            })
        });
    }
    // Gets all sport entries
    get_sport_entries() {
        return new Promise((resolve,reject) => {
            this.db_sport.find({},function(err,entries) {
                if (err) {
                    reject(err);
                } else {
                    resolve(entries);
                    console.log("Function 'get_sport_entries' returns:",entries);
                }
            })
        });
    }
    // Gets one cardio entry
    get_cardio_entry(id) {
        return new Promise((resolve,reject) => {
            this.db_cardio.find({_id: id},function(err,entry) {
                if (err) {
                    reject(err);
                } else {
                    resolve(entry);
                    console.log("Function 'get_cardio_entry' returns:",entry);
                }
            })
        });
    }
    // Gets one strength entry
    get_strength_entry(id) {
        return new Promise((resolve,reject) => {
            this.db_strength.find({_id: id},function(err,entry) {
                if (err) {
                    reject(err);
                } else {
                    resolve(entry);
                    console.log("Function 'get_strength_entry' returns:",entry);
                }
            })
        });
    }
    // Gets one sport entry
    get_sport_entry(id) {
        return new Promise((resolve,reject) => {
            this.db_sport.find({_id: id},function(err,entry) {
                if (err) {
                    reject(err);
                } else {
                    resolve(entry);
                    console.log("Function 'get_sport_entry' returns:",entry);
                }
            })
        });
    }
    // Deletes an exercise
    delete_exercise(type,id) {
        if (type=="cardio") {
        this.db_cardio.remove({_id: id},function(err,num_deleted) {
            if (err) {
                console.log("Document with ID ",id," not in Cardio DB");
            } else {
                console.log("Deleted cardio exercise with ID ",id);
            }
        });
        } else if (type=="strength") {
        this.db_strength.remove({_id: id},function(err,num_deleted) {
            if (err) {
                console.log("Document with ID ",id," not in Strength DB");
            } else {
                console.log("Deleted strength exercise with ID ",id);
            }
        });
        } else if (type=="sport") {
        this.db_sport.remove({_id: id},function(err,num_deleted) {
            if (err) {
                console.log("Document with ID ",id," not in Sport DB");
            } else {
                console.log("Deleted sport exercise with ID ",id);
            }
        });
        } else {
            console.log("No DB of type ",type);
        }
    }
    // Adds one cardio entry
    add_cardio(name,dist) {
        var entry = {
            name: name,
            distance: dist
        }
        this.db_cardio.insert(entry,function(err,doc) {
            if (err) {
                console.log("Error inserting document",name);
            } else {
                console.log("Document inserted in db",entry);
            }
        });
    }
    // Adds one strength entry
    add_strength(name,weight,reps) {
        var entry = {
            name: name,
            weight: weight,
            repetitions: reps
        }
        this.db_strength.insert(entry,function(err,doc) {
            if (err) {
                console.log("Error inserting document",name);
            } else {
                console.log("Document inserted in db",entry);
            }
        });
    }
    // Adds one sport entry
    add_sport(name,dur) {
        var entry = {
            name: name,
            duration: dur
        }
        this.db_sport.insert(entry,function(err,doc) {
            if (err) {
                console.log("Error inserting document",name);
            } else {
                console.log("Document inserted in db",entry);
            }
        });
    }
}

module.exports = training_plan;