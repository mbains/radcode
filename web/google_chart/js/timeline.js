/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


google.load('visualization', '1', {packages: ['annotatedtimeline']});
var graphData;
var timelineNameSpace = {
    drawVisualization: function(){
      graphData = new google.visualization.DataTable();
      graphData.addColumn('date', 'Date');
      graphData.addColumn('number', 'Sold Pencils');
      graphData.addColumn('string', 'title1');
      graphData.addColumn('string', 'text1');
      graphData.addColumn('number', 'Sold Pens');
      graphData.addColumn('string', 'title2');
      graphData.addColumn('string', 'text2');
      graphData.addRows(6);
      graphData.setValue(0, 0, new Date(2008, 1 ,1));
      graphData.setValue(0, 1, 30000);
      graphData.setValue(0, 4, 40645);
      graphData.setValue(1, 0, new Date(2008, 1 ,2));
      graphData.setValue(1, 1, 14045);
      graphData.setValue(1, 4, 20374);
      graphData.setValue(2, 0, new Date(2008, 1 ,3));
      graphData.setValue(2, 1, 55022);
      graphData.setValue(2, 4, 50766);
      graphData.setValue(3, 0, new Date(2008, 1 ,4));
      graphData.setValue(3, 1, 75284);
      graphData.setValue(3, 4, 14334);
      graphData.setValue(3, 5, 'Out of Stock');
      graphData.setValue(3, 6, 'Ran out of stock on pens at 4pm');
      graphData.setValue(4, 0, new Date(2008, 1 ,5));
      graphData.setValue(4, 1, 41476);
      graphData.setValue(4, 2, 'Bought Pens');
      graphData.setValue(4, 3, 'Bought 200k pens');
      graphData.setValue(4, 4, 66467);
      graphData.setValue(5, 0, new Date(2008, 1 ,6));
      graphData.setValue(5, 1, 33322);
      graphData.setValue(5, 4, 39463);

      timelineNameSpace.annotatedtimeline = new google.visualization.AnnotatedTimeLine(
          document.getElementById('visualization'));
      timelineNameSpace.annotatedtimeline.draw(graphData, {
          'displayAnnotations': false,
          'allowRedraw': true
      });
    }
};

window.onload = timelineNameSpace.drawVisualization;
