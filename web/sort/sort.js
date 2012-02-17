/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

var numnames = 0;
var names = new Array();
function SortNames()
{
    //get the name from teh text field
    thename = document.theform.newname.value;
    //add the name to the array
    names[numnames]=thename;
    //increment the counter
    numnames++;
    //sort the array
    names.sort();
    document.theform.sorted.value=names.join("\n");
}
