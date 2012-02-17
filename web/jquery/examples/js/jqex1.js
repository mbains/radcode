/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


var Klass = function() {
   this.value = 42;
}

Klass.prototype.testprototype = function(){
   this
   console.log(this)
}

klass.test = function() {
   this
   console.log(this)
}


var nsex1 = {
    readyFunc: function() {
        var $nodes = $('#root').children();
        if(window.console != null) {
            console.log("Html for root: %s", $('#root').html());
            console.log("Number of nodes %s", $nodes.length);

            //use for each
            $("#tableDiv tbody td").each(function() {
                console.log("body of table", $(this).html());
            });

        }
        $('#recorder').html("<h1> Number of nodes " + $nodes.length + "</h1>");
        $('body').prepend('Appended text to body from jquery');
        $('<div id=newdiv>yet another way to prepend</div>').prependTo('body');

    },
    applyHighLight: function() {
        $('#newdiv').addClass('highlight');
    },
    clearHighLight: function() {
        $('#newdiv').removeClass('highlight');
    },
    onLoad: function() {
        $(document).ready(nsex1.readyFunc);
    }
};

//b = foobar()
nsex1.foobar = function(args)
{
    if(args==null) {
        args = {value:5};
    }
    else if(args.value == null) {
        args = {value:args};
    }
    
    this.args = args.value;
    console.log("Foobar created: ", args);
}

nsex1.foobar.prototype.toString = function() {
        return "foobar instance " + this.args;
}

window.onload = nsex1.onLoad;
