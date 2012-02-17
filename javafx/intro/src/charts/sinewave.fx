/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package charts;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


import javafx.scene.Scene;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.part.NumberAxis;
import javafx.stage.Stage;
import java.lang.Math;




Stage {
    title: "Line Chart"
    scene: Scene {
            content: [createLineChart()]
        }
}

function createLineChart()
{
    LineChart {
        title: "Line Chart"
        xAxis: createXAxis()
        yAxis: createYAxis()
        data: [
            LineChart.Series {
                name: "Sine Wave"
                data: for (rads in [0..2*Math.PI step 0.01]) {
                LineChart.Data {
                    xValue: rads
                    yValue: Math.sin(rads)
                    }
                }
            }

            ]
    }

}


function createXAxis()
{
    NumberAxis {
        label: "Radians"
        upperBound: 2*Math.PI
        tickUnit: Math.PI/2
        formatTickLabel: function(value) {
        "{%.2f value}"
        }
    }
}

function createYAxis()
{
    NumberAxis {
        upperBound: 1.0
        lowerBound:-1.0
        tickUnit: 0.5
    }

}


