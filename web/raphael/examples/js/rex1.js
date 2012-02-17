/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


var rex1ns = {
    paper: null,
    curved: null,
    event: null,
    onLoad: function(){
        rex1ns.loadPaths2();
        rex1ns.loadPathArch();
    },
    log: function(stri) {
       if(window.console){
            console.log(stri.toString());
        }
    },
    loadPaths1: function() {
        rex1ns.attachEvents("#rex1div");
        this.log("Loaded paths1");
        rex1ns.paper = Raphael("rex1div", 640, 480);

        rex1ns.paper.circle(300, 300, 5).attr({fill:Raphael.getColor()});
        rex1ns.paper.circle(300+40, 300+40, 5).attr({fill:Raphael.getColor()});
        rex1ns.paper.circle(340+250, 340-200, 5).attr({fill:Raphael.getColor()});
        //draw a curved and straight path
        
        //draw the point at the first control point
        rex1ns.paper.circle(340-160, 340-10, 10).attr({stroke:Raphael.getColor()});
                                                              //x1  y1  x2 y2  x    y
        //rex1ns.curved = rex1ns.paper.path("M 300 300 l 40 40 c 100 100 250 100 250 -200");
        rex1ns.curved = rex1ns.paper.path("M 300 300 l 40 40 c -160 -10 250 -200 250 -200");

        var straight = rex1ns.paper.path("M 300 300 l 40 40 l 250 -200");
        c = Raphael.getColor();
        rex1ns.curved.attr({stroke: c});

    },
    loadPaths2: function() {
        rex1ns.attachEvents("#rex1div");
        rex1ns.log("Loaded paths2");
        rex1ns.paper = Raphael("rex1div", 800, 600);
        rex1ns.paper.path("M 100 200 C 100 100 250 100 250 200 S 400 300 400 200").attr({stroke:Raphael.getColor()});

        //connect
        rex1ns.paper.path("M 100 200 L 100 100");
        rex1ns.paper.path("M 250 100 L 250 200");
        rex1ns.paper.path("M 250 200 L 250 300");
        rex1ns.paper.path("M 400 300 L 400 200");

        //endpoints
        rex1ns.paper.circle(100, 200, 10).attr({fill:Raphael.getColor()});
        rex1ns.paper.circle(250, 200, 10).attr({fill:Raphael.getColor()});
        rex1ns.paper.circle(400, 200, 10).attr({fill:Raphael.getColor()});
        
        //ctrl points
        rex1ns.paper.circle(100, 100, 10).attr({fill:Raphael.getColor()});
        rex1ns.paper.circle(250, 100, 10).attr({fill:Raphael.getColor()});
        rex1ns.paper.circle(400, 300, 10).attr({fill:Raphael.getColor()});

        //auto ctrl point
        rex1ns.paper.circle(250, 300, 9).attr({fill:Raphael.getColor()});

    },

    loadPathArch: function() {
        rex1ns.attachEvents("#rex2div");
        paper = Raphael("rex2div", 800, 900);
                                   //rx  ry  xrot lflag sflag  x    y
        paper.path("M275,175 v-150 a 150 150 0    0     0     -150  150 z").attr({fill: Raphael.getColor()});
        paper.path("M300,200 h-150 a 150 150 0    1     0      150,-150 z").attr({fill: Raphael.getColor()});

        paper.path("M 100 700      a 100 40  0    1     1      250  50")
        paper.path("M 100 700      a 100 40  15   1     1      250  50");
        paper.path("M 100 700      a 100 40  30   1     1      250  50");
        paper.path("M 100 700      a 100 40  45   1     1      250  50");
        paper.path("M 100 700      a 100 40  60   1     1      250  50");
        paper.path("M 100 700      a 100 40  75   1     1      250  50");
        paper.path("M 100 700      a 100 40  90   1     1      250  50");
        paper.path("M 100 700 l 250 50").attr({stroke: '#ff0000'});
    },
    
    attachEvents: function(objName) {
        $(objName).click(function(event){
            rex1ns.event = event;
            rex1ns.log("clicked on " + [event.layerX, event.layerY]);
        });
    }
};
/*
 * <?xml version="1.0" standalone="no"?>
<!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN"
  "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd">
<svg width="12cm" height="5.25cm" viewBox="0 0 1200 400"
     xmlns="http://www.w3.org/2000/svg" version="1.1">
  <title>Example arcs01 - arc commands in path data</title>
  <desc>Picture of a pie chart with two pie wedges and
        a picture of a line with arc blips</desc>
  <rect x="1" y="1" width="1198" height="398"
        fill="none" stroke="blue" stroke-width="1" />

  <path d="M300,200 h-150 a150,150 0 1,0 150,-150 z"
        fill="red" stroke="blue" stroke-width="5" />
  <path d="M275,175 v-150 a150,150 0 0,0 -150,150 z"
        fill="yellow" stroke="blue" stroke-width="5" />

  <path d="M600,350 l 50,-25
           a25,25 -30 0,1 50,-25 l 50,-25
           a25,50 -30 0,1 50,-25 l 50,-25
           a25,75 -30 0,1 50,-25 l 50,-25
           a25,100 -30 0,1 50,-25 l 50,-25"
        fill="none" stroke="red" stroke-width="5"  />
</svg>
 * */