/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package webrequest;

import javafx.data.pull.Event;
import javafx.data.pull.PullParser;
import java.io.InputStream;
import webrequest.person.Person;

/**
 * @author mbains
 */

public class InputParser {

    var person: Person;
    public var people: Person[];

    def parseEventCallback = function(event: Event)
    {
            println("event.name  = {event.name}, event.level = {event.level}");
            print(" event.type = ");
            if (event.type == PullParser.NULL)
                println("Null")
            else if(event.type == PullParser.NUMBER)
            {
                println("Number")
            }
            else if(event.type == PullParser.TEXT)
            {
                println("text")
            }
            else if(event.type == PullParser.END_ARRAY)
            {
                println("End array")
            }
            else if(event.type == PullParser.END_ARRAY_ELEMENT)
                println("End Array element")
            else if(event.type == PullParser.END_DOCUMENT)
            {
                println("End document");
            }
            else if(event.type == PullParser.END_ELEMENT)
            {
                println("End Element");
                addPersonToPeople();
            }
            else if(event.type == PullParser.END_VALUE)
            {
                println("EndValue");
                if(event.name == "name")
                    person.name = event.text
                else if(event.name == "age")
                    person.age = event.integerValue
                else if(event.name == "money")
                    person.money = event.integerValue

            }
            else if(event.type == PullParser.FALSE)
            {
                println("False");
            }
            else if(event.type == PullParser.TRUE)
            {
                println("True");
            }
            else if(event.type == PullParser.INTEGER)
            {
                println("Integer");
            }
            else if(event.type == PullParser.START_ARRAY)
            {
                println("Start array");
            }
            else if(event.type == PullParser.START_ARRAY_ELEMENT)
            {
                println("Start array element");
            }
            else if(event.type == PullParser.START_DOCUMENT)
            {
                println("Start Document");
            }
            else if(event.type == PullParser.START_ELEMENT)
            {
                println("Start Element");
                createPerson();
            }
            else if(event.type == PullParser.START_VALUE)
            {
                println("Start Value");
            }
            else
            {
                println("Something else")
            }


            println("   event.qname = {event.qname}, event.qname.name = {event.qname.name}");
            println("   event.text = {event.text}, event.integer= {event.integerValue}");
            println("\n");
            if (event.type == PullParser.END_DOCUMENT)
            {
                println("End of document reached");
            }
    }

    public function createPerson()
    {
        person = Person{};
    }

    public function addPersonToPeople()
    {
        insert person into people;
    }



    public function parse(input: InputStream)
    {
        println("Raw input = {input.toString()}");
        def parser = PullParser {
            input: input;
            onEvent: parseEventCallback;
            documentType: PullParser.JSON;
        }
        parser.parse();
    }

}
