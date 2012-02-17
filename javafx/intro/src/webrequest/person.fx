/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package webrequest;

/**
 * @author mbains
 */

public class Person {

    public var age: Integer;
    public var name: String;
    public var money: Integer;

    public function toStr()
    {
        return "My name is {name}. I am {age} years old, and I have ${money}";
    }


}
