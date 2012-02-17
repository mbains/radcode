/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package classes;

/**
 * @author mbains
 */

public class Point {
    public var x: Number;
    public var y: Number;

    public function clear(): Void
    {
        x = 0;
        y = 0;
    }

    public function show(): String
    {
        return "x = {x}, y = {y}";
    }

}

function run(args: String[])
{
    var p = Point{x:10, y:20}
    println(p.show());

}
