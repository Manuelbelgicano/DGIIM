const { response } = require("express");
const workout_class = require("../models/workout_model");
const db = new workout_class();

exports.landing_page = function(req,res) {
    console.log("Landing page");
    
    Promise.all([db.get_cardio_entries(),db.get_strength_entries(),db.get_sport_entries()]).then((list) => {
        res.render("exercises",{
            "title": "Training plan",
            "cardio": list[0],
            "gym": list[1],
            "sport": list[2]
        });
        console.log("Promise resolved.",list);
    }).catch((err) => {
        console.log("Promise rejected:",err);
    });
}

exports.show_exercise = function(req,res) {
    var type = req.params.type;
    var id = req.params.id;
    console.log("filtering type: ",type);
    console.log("filtering id: ",id);
    if (type=="cardio") {
        db.get_cardio_entry(id).then((data) => {
            res.render("delete", {
                "title": "Delete exercise",
                "cardio": data
            });
            console.log("Promise resolved.",data);
        }).catch((err) => {
            console.log("Promise rejected:",err);
        });
    } else if (type=="strength") {
        db.get_strength_entry(id).then((data) => {
            res.render("delete", {
                "title": "Delete exercise",
                "strength": data
            });
            console.log("Promise resolved.",data);
        }).catch((err) => {
            console.log("Promise rejected:",err);
        });
    } else if (type=="sport") {
        db.get_sport_entry(id).then((data) => {
            res.render("delete", {
                "title": "Delete exercise",
                "sport": data
            });
            console.log("Promise resolved.",data);
        }).catch((err) => {
            console.log("Promise rejected:",err);
        });
    } else {
        console.log("Error: No exercises of type ",type);
    }
}

exports.delete_exercise = function(req,res) {
    var type = req.params.type;
    var id = req.params.id;
    console.log("filtering type: ",type);
    console.log("filtering id: ",id);
    
    db.delete_exercise(type,id);
    res.redirect("/");
}

exports.new_entry = function(req,res) {
    var type = req.params.type;
    console.log("New",type);

    if (type=="cardio") {
        res.render("new_cardio", {
            "title": "Add exercise"
        });
    } else if (type=="strength") {
        res.render("new_strength", {
            "title": "Add exercise"
        });
    } else if (type=="sport") {
        res.render("new_sport", {
            "title": "Add exercise"
        });
    } else {
        console.log("Error: No type ",type);
    }
}

exports.post_new_entry = function(req,res) {
    var type = req.params.type;
    console.log("Adding one",type);
    if (type=="cardio") {
        db.add_cardio(req.body.name,req.body.distance);
    } else if (type=="strength") {
        db.add_strength(req.body.name,req.body.weight,req.body.repetitions);
    } else if (type=="sport") {
        db.add_sport(req.body.name,req.body.duration);
    } else {
        console.log("Error: No type ",type);
    }

    res.redirect("/");
}