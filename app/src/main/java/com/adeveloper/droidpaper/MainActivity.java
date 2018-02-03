package com.adeveloper.droidpaper;

import android.app.ActivityManager;
import android.support.v7.app.AppCompatActivity;
import android.content.Context;
import android.content.pm.ConfigurationInfo;

import android.os.Bundle;
import android.view.SurfaceView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        ActivityManager activityManager
                = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
        ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();

        final boolean supportsEs2 = configurationInfo.reqGlEsVersion >= 0x20000;

        if (supportsEs2) {

            setContentView(R.layout.activity_main);

            NativeLibLoader.load();

            DroidPaperSurface surface = new DroidPaperSurface();
            SurfaceView surfaceView = (SurfaceView)findViewById(R.id.glSurface);
            surfaceView.getHolder().addCallback(surface);

        } else {
            Toast.makeText(this, "This device does not support OpenGL ES 2.0", Toast.LENGTH_LONG).show();
            return;
        }

    }

    @Override
    protected void onStart() {
        super.onStart();
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
    }

    @Override
    protected void onStop() {
        super.onStop();
    }

}
