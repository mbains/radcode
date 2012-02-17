/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package charts;
import javafx.animation.Timeline;
import javafx.scene.Scene;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.part.NumberAxis;
import javafx.stage.Stage;
import javafx.animation.Interpolator;




var value = 20.0;

var timeline = Timeline {
    repeatCount: Timeline.INDEFINITE
    keyFrames: [
            at(3s) { value => 5.0 tween Interpolator.LINEAR}
            at(6s) { value => 20.0 tween Interpolator.LINEAR}
        ]

}

var theScene = Scene {
        width: 800,
        height: 800,
        content: [
            LineChart {
                title: "Line Chart"
                xAxis: NumberAxis{
                    lowerBound:1
                    upperBound:10
                }
                yAxis: NumberAxis {
                    lowerBound: 0
                    upperBound: 35

                }
                data: [
                    LineChart.Series {
                        name: "Line 1"
                        data: [
                               LineChart.Data {xValue: 3 yValue: bind 25 - value}
                               LineChart.Data {xValue: 6 yValue: bind value}
                               LineChart.Data {xValue: 9 yValue: bind 20 - value/2}
                            ]
                    }

                    ]
            }
        ]


}


Stage {
    title: "MyApp",
    scene: theScene,
}




timeline.play()