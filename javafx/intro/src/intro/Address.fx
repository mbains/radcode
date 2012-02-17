/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package intro;

/**
 * @author mbains
 */

public class Address {

    public var number_m: Number;
    public var street_m: String;
    public var city_m: String;

    public function show(): String
    {
        "Street Number:{number_m}\nStreet:{street_m}\nCity:{city_m}";
    };
}
