/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package org.me.now;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import java.util.Date;

/**
 *
 * @author mbains
 */
public class MainActivity extends Activity 
        implements View.OnClickListener{
        Button btn;

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        setContentView(R.layout.main);

        btn = (Button)findViewById(R.id.button);
        btn.setOnClickListener(this);
        updateTime();
    }

    public void onClick(View view)
    {
        updateTime();
    }

    private void updateTime()
    {
        btn.setText(new Date().toString());
    }

}
