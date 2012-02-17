/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package gui;
import javafx.scene.Group;
import onButtonToggle.OnButtonToggle;
import offButtonToggle.OffButtonToggle;

public class ToggleButtonGroup
{

    var onButtonVisible: Boolean = false;
    var onButton =  OnButtonToggle {visible: bind onButtonVisible};
    var offButton = OffButtonToggle {visible: bind not onButtonVisible};
    public var onPositionCB: function():Void = null;
    public var offPositionCB: function():Void = null;

    public function getGroup(xpos:Number, ypos: Number): Group
    {
        Group {
            translateX: xpos,
            translateY: ypos,
            content: [onButton, offButton],
            onMousePressed:handleMousePress,

        };

    }

    function handleMousePress(e): Void
    {
        onButtonVisible = not onButtonVisible;
        if(onButtonVisible and onPositionCB != null)
        {
            onPositionCB();
        }
        else if(onButtonVisible == false and offPositionCB != null)
        {
            offPositionCB()
        }

    }

}
