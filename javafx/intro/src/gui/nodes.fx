/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package gui;

import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.scene.paint.LinearGradient;
import javafx.scene.shape.Circle;
import javafx.scene.text.Text;
import javafx.scene.transform.Transform;
import javafx.animation.Timeline;
import javafx.animation.KeyFrame;
import javafx.scene.Group;
import javafx.scene.paint.Stop;
import javafx.scene.effect.Reflection;
import javafx.animation.Interpolator;
import javafx.scene.control.Button;
import javafx.scene.input.MouseEvent;
import com.javafx.preview.control.TreeItem;
import com.javafx.preview.control.TreeView;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import gui.offButtonToggle.OffButtonToggle;
import gui.onButtonToggle.OnButtonToggle;
import gui.toggleButtonGroup.ToggleButtonGroup;

var angle = 0.0;
var condition: Boolean = true;

//just a sandbox timeline
var timeline = Timeline {
    repeatCount: Timeline.INDEFINITE
    keyFrames: KeyFrame {
                time: 1s
                action: function()
                {
                    //println(angle = {angle});
                    angle+=1;
                    if(condition==true)
                        condition = false
                    else
                        condition = true;
                }

            }

}

var circleColor = Color{};
var circleXCordinate = 200.0;
var cirSlideTimeLine = Timeline {
    autoReverse:true
    repeatCount: Timeline.INDEFINITE
    keyFrames: KeyFrame {
        time: 3s
        values: circleXCordinate => 500 tween Interpolator.EASEIN;
    }
    
}

var toggleButton1 = toggleButtonGroup.ToggleButtonGroup{
                            onPositionCB: function():Void {println("toggleButton1: on position");}
                            offPositionCB: function():Void {println("toggleButton1: off position");}
                        };
var toggleButton2 = toggleButtonGroup.ToggleButtonGroup{
                                onPositionCB: function():Void {println("toggleButton2: on position");}
                                offPositionCB: function():Void {println("toggleButton2: off position");}
                        };


var cirSelected: Boolean = false;
Stage{
    title: "Nodes"
    scene: Scene {
        fill: LinearGradient{
                startX: 0, startY: 0, endX: 0, endY: 1 proportional: true
                stops: [Stop {offset: 0.0 color: Color.WHITE}
                        Stop {offset: 1.0 color: Color.BLACK}]
            }
        width: 700
        height: 400
        content: [
            Button {
                translateX:circleXCordinate
                translateY:150
                text: "Animate"
                action: function(): Void
                {
                    if(cirSelected)
                    {
                        cirSlideTimeLine.pause();

                        println("clicked");
                        cirSelected = false;
                        circleColor = Color.TRANSPARENT;
                        //bug in JavaFX, using the timeline on the circle inhibits color change
                        }
                    else
                    {
                        cirSlideTimeLine.play();
                        cirSelected = true;
                        circleColor = Color.RED;
                    }
                }

            },
            TreeView{
             root: TreeItem {data: Button{text:"some button"}}
             },

            Circle {
                centerX: bind circleXCordinate
                centerY: 200
                radius: 10
                fill: bind circleColor
                stroke: Color.RED

            },
            toggleButton2.getGroup(230,45),
            toggleButton1.getGroup(230,-20),
            Group {
                    translateX:330
                    translateY:150
                    onMouseEntered: function(e:MouseEvent) {
                                    println("mouse entered group");
                                }
                    content:[
                        Circle {
                        centerX: 50
                        centerY: 50
                        radius: 50
                        stroke: Color.GREEN
                        fill: Color.WHITE
                        visible: bind condition
                        onMouseClicked: function(e) { println("circle clicked");
                            }
                        },

                        Text {  content: "Tux"
                                transforms: bind Transform.rotate(33, 10, 100)
                            },
                        ImageView {
                            image: Image {url: "{__DIR__}tux_small.jpg" }
                            transforms: Transform.rotate(33, 10, 100)
                            translateX:-10
                        }
                    ]
                   effect:Reflection{fraction:0.9 topOpacity: 0.5 topOffset: 2.5}
            }

        ]
    }
}

timeline.play();
