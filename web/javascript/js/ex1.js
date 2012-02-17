/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


ex1ns = {}

Klass = function(){
    this.foobar = 42
    this.insideFunc = function() {
        console.log(this)
    }
}

Klass.prototype.doitFromProto = function() {
    
    console.log(this)
}

Klass.doit = function() {
    
    console.log(this)
}

Sclass = function() {}

Sclass.doit = function()
{
    this.foo = 42;
}


ex1ns.readyFunc = function () {
    console.log("ready")
    var k = new Klass()
    k.doitFromProto()
    k.insideFunc()
    //k.doit() won't work'
    Sclass.doit()
}   

$(document).ready(ex1ns.readyFunc);
