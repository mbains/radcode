/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

var chartexns  = {
    paper: null,
    drawGrid : function(paper, x, y, width, height, widthDivision, heightDivision, color) {
        //color = color || "#000";
        rex1ns.log("Loading grid (x,y)= " + [x,y]  + ". (width,height)=" + [width, height]);
        var offset = 0;
        var gridPath = ["M",    Math.round(x) + offset,
                                Math.round(y) + offset,

                        "L",    Math.round(x + width) + offset,
                                Math.round(y) + offset,
                                Math.round(x + width) + offset,
                                Math.round(y + height) + offset,
                                Math.round(x) + offset,
                                Math.round(y + height) + offset,
                                Math.round(x) + offset,
                                Math.round(y) + offset];

        var rowHeight = height/heightDivision;
        var columnWidth = width/widthDivision;
        rex1ns.log("RowHeight: " + rowHeight);
        rex1ns.log("columnWidth: " + columnWidth);

        for(var i = 1; i < heightDivision; i++) {
            gridPath = gridPath.concat(["M",
                                        Math.round(x) + offset,
                                        Math.round(y + i * rowHeight) + offset,
                                        
                                        "H", 
                                        Math.round(x + width) + offset]);
        }

        for(var j = 1; j < widthDivision; j++) {
            gridPath = gridPath.concat(["M",
                                        Math.round(x + j * columnWidth) + offset,
                                        Math.round(y) + offset,

                                        "V",
                                        Math.round(y + height) + offset]);
        }

        paper.path(gridPath);

    },
    onload: function() {
        var paperWidth = parseInt($("#holder").css('width'));
        var paperHeight = parseInt($("#holder").css('height'));
        var topMargin = 0;

        chartexns.paper = Raphael("holder", paperWidth, paperHeight);
        rex1ns.attachEvents("#holder");
        paper = chartexns.paper;
        chartexns.circle = paper.circle(100, 100, 10).attr({fill:"#fff"});
        //rex1ns.attachEvents(chartexns.circle.node);
        chartexns.drawGrid(paper, topMargin, topMargin, paperWidth - topMargin*2, paperHeight - topMargin*2, 10, 10, Raphael.getColor());
    }
};

window.onload = chartexns.onload;
