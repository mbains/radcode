/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


ex1ns = {}

ex1ns.readyFunc = function () {
    console.log("ready");
    var canvas = $('#canvascontainer canvas');
    var context = canvas.get(0).getContext('2d');
    context.globalAlpha = 0.5;
    context.save();
    var lastFunc = ''
    $('input').click(function (event) {
        var fname = event.currentTarget.value
        if(lastFunc != 'translate') {
            console.log("restored state");
            context.restore();
            context.save();
        }
        ex1ns[fname](context);
        lastFunc = fname;
    });
}

animate = function(context) {
    if(false === (this instanceof animate)) {
        return new animate();
    }
    this.run = true
    this.iterations = 0
    return this;
}

animate.prototype.go = function () {
    this.iterations += 1
    
    
    
    
    var me = this
    if(this.run) {
        setTimeout(function () {
            me.go();
        }, 33)
    }
}

ex1ns.drawRect = function (context) {
    context.fillRect(40, 40, 100, 100);
}

ex1ns.drawCir = function (context) {
    context.beginPath();
    context.arc(230, 90, 50, 0, Math.PI*2, false);
    context.closePath();
    context.fill();
}

ex1ns.fillctx = function (context) {
    context.fillStyle = "rgb(255, 0, 0)";
    context.fillRect(40, 40, 100, 100);
    
    context.fillStyle = "#00FF00";
    context.fillRect(0, 0, 30, 30);
    
    context.beginPath();
    context.strokeStyle = "blue";
    context.lineWidth = 5;
    context.fillStyle = "yellow";
    context.arc(300, 300, 100, 0, (3/2)*Math.PI, false);
    context.stroke();
    context.closePath();
    context.fill();
}

ex1ns.drawLines = function(context) {
    context.beginPath();
    context.strokeStyle = "blue";
    context.moveTo(40, 40);
    context.lineWidth = 20;
    context.lineTo(340, 340);
    context.closePath();
    context.stroke();
}

ex1ns.writeText = function(context) {
    context.lineWidth = 1;
    context.fillStyle = "green";
    context.strokeStyle = "blue";
    
    var text = "Hello, World!";
    context.font = "italic 30px serif";
    context.fillText(text, 30, 30);
    
    var text2 = "Good Bye World!";
    context.strokeText(text2, 350, 350);
}

ex1ns.translate = function(context) {
    context.translate(20, 20);
}

ex1ns.scale = function(context) {
    context.save();

    context.fillStyle = "yellow";
    context.translate(-150, -150);
    context.scale(2, 2);
    context.fillRect(150, 150, 100, 100);
    context.restore();
    
    context.fillStyle = "red";
    context.fillRect(150, 150, 100, 100); //draw reference
}

ex1ns.rotate = function(context) {
    context.save(); //save 2
    
    //move origin
    context.translate(200, 200);
    context.fillStyle="yellow"
    
    //main rotated square
    context.save()
    context.rotate(Math.PI/4);
    //place center of sqare at origin
    context.fillRect(-50, -50, 100, 100);
    context.restore()
    
    //reference 1 without rotation, origin offset
    context.save() //save 1
    context.globalAlpha = 0.2;
    context.fillStyle = "orange";
    context.fillRect(-50, -50, 100, 100);
    
    context.fillStyle="red"
    context.fillRect(0, 0, 100, 100); //draw reference
    context.restore(); //restore 1
    
    context.restore(); //restore 2
}

ex1ns.eraseAll = function(context) {
    var canvas = $('canvas');
    context.save();
    context.globalAlpha = 1;
    context.fillStyle = "white";
    context.fillRect(0, 0, canvas.width(), canvas.height());
    context.restore();
}

ex1ns.transmatrix = function(context) {
    
    context.save();
    
    context.fillStyle = "yellow";
    
    /*  -
     * |
     * |
     * |
     * |
     * |
     *  -
     * */
    context.transform(2, 0, 0, 2, 150, 150);
    context.fillRect(0, 0, 100, 100);
    
    context.restore();
}

ex1ns.shadow = function(context) {
    context.save();
    context.shadowBlur = 30;
    context.shadowColor = "rgb(255,255,0)";
    context.fillRect(50, 50, 100, 100);
    context.restore();
    
}

$(document).ready(ex1ns.readyFunc);
