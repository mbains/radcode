/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


var cradle = require('cradle');
var db = new (cradle.Connection)().database('grocer');
var fs = require('fs');
var xml2js = require('xml2js');
var parser = new xml2js.Parser();
var eyes = require('eyes');

var addView = function(thedb) {
    thedb.save('_design/fruits', {
        views: {
            all: {
                map: function(doc) {
                    emit(doc, doc.type);
                }
            },
            best: {
                map: function(doc) {
                    var store, price, value;
                    if(doc.item && doc.prices) {
                        for (store in doc.prices) {
                            price = doc.prices[store];
                            value = [doc.item, store];
                            //key = price, value = value
                            emit(price, value);
                        }

                    }
                }
            }
        }
    });
};



var getAll = function(thedb) {
    thedb.view('fruits/all', function(err, doc) {
        console.log('err ' + err)
        eyes.inspect(doc);
    });
}

var getBest = function(thedb) {
    thedb.view('fruits/best', function(err, doc) {
        console.log('err ' + err)
        eyes.inspect(doc);
    });
}


//does not work
var getByKey = function(thedb) {
    thedb.view('fruits/all', {key: 'oranges'}, 
        function(err, doc){
            eyes.inspect(doc);
    });
}



db.exists(function (err, exists) {
    
    if (err) {
        console.log('error', err);
    } else if (exists) {
        console.log('db exists');
        getBest(db);
//        addView(db);
//        getByKey(db);
    } else {
        console.log('database does not exists.');
        db.create(function(err, result){
            console.log(err);
        });
        /* populate design documents */
        
        
    }
});




  
