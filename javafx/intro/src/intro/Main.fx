//intro
package intro;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;

var numOne = 100;
def numTwo = 2;
var result;

var timeline : Timeline = Timeline {
    repeatCount: Timeline.INDEFINITE
    keyFrames :
        KeyFrame {
            time : 1s
            action: function() {
               add(1,numOne); numOne++;
               if(numOne>120)
               {
                   timeline.stop();
               }

            }
    }
};


add();
add(50, 50);
println("getAdd(70,70)={getAdd(70,70)}");
// class args can be separated by "," or ";"
var myAddress: Address = Address{number_m:120; street_m:"Main St", city_m:"Santa Clara";};
var yourAddress = Address{city_m:"Oakland";};
def hisAddress = Address{city_m:"San Francisco"};
def weekDays = ["Mon", "Tue", "Wed", "Thu", "Fri"];
var weekDaysStr: String[] = ["Mon", "Tue", "Wed", "Thu", "Fri"];

var days = [weekDaysStr, "Sat", "Sun"];
insert "Barbecue Day" into days;
insert "Imaginary Day" after days[2];
println("Days of the week: {days}");

def to100 = [1..100];
def to100Even = [0..100 step 2];
var numsOver90 = to100[n|n>90];
println("My address {myAddress.show()}");
println("List upto 100: {to100}");
println("Numbers over 90: {numsOver90}");
println("Even numbers: {to100Even}");


var rows = ["A", "B"];
var columns = [1,2];
var matrixStr = for (row in rows, column in columns) "{row}{column}";
println("matrix = {matrixStr}, Iterating over: {for (item in matrixStr) "{item} "}");

var digits = [1..6];

//timeline.play();

function add() {
    result = numOne + numTwo;
    println("{numOne} + {numTwo} = {result}");
}

function add(argOne: Integer, argTwo: Integer)
{
    result = argOne + argTwo;
    println("{argOne} + {argTwo} = {result}");
}

function getAdd(argOne: Integer, argTwo: Integer) :Integer
{
    var result2 = argOne + argTwo;
    println("{argOne} + {argTwo} = {result2}");
    return result2;
}

