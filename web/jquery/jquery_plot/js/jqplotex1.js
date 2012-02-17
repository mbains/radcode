/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


var jqplotex1ns = {
    doIt: function() {
        //optionsObj =
        jqplotex1ns.chart=$.jqplot('chartdiv', [[[1, 2],[3,5.12],[5,13.1],[7,33.6],[9,85.9],[11,219.9]]]);
    },
    onReady: function(){
      //go through jquery
      $(document).ready(this.doIt);
    }
}
