/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package intro;

//binding 
var mainVar = 100;
def boundVar = bind mainVar;

println("mainVar = {mainVar}, boundVar = {boundVar}");
println("Setting mainVar to 200");
mainVar = 200;
println("boundVar now = {boundVar}");



// example of bound function
var scale = 2.0;
//the variable bound to makePoint will be updated even if a non argument
// such as scale changes
bound function makePoint(xPos: Number, yPos: Number) : Point {
    Point {
        x: xPos * scale
        y: yPos * scale
    }
}

class Point {
    var x: Number;
    var y: Number;
}

var myX = 3.0;
var myY = 3.0;
def pt = bind makePoint(myX, myY);
println("pt.x is bound to myX = {pt.x}, scale = {scale}");

println("Changing myX to 10");
myX = 10.0;
println("ptx.x = {pt.x}");
println("Decreasing scale by 1/2");
scale = 1.0;
println("ptx.x = {pt.x}");



// binding to sequence
var seq1 = [1..10];
def seq2 = bind for (item in seq1) item;
def seq3 = bind seq1;
seq1[4] = 99;

function printSeqs()
{
    print("seq1: ");
    for(i in seq1) {print(" {i}");}
    println("");
    
    print("seq2 is bounded, per variable: ");
    for(i in seq2) {print(" {i}");}
    println("");

    print("seq3 is directly bound:");
    for(i in seq3) {print(" {i}");}
    println("");
}

printSeqs();
