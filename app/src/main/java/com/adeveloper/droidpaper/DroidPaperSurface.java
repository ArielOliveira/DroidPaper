package com.adeveloper.droidpaper;

import android.view.SurfaceHolder;

/**
 * Created by ariel on 02/02/18.
 */

public class DroidPaperSurface implements SurfaceHolder.Callback {

    public void surfaceCreated(SurfaceHolder holder) {

    }

    public void surfaceChanged(SurfaceHolder holder, int w, int h, int format) {
        NativeLibLoader.nativeSurfaceChanged(holder.getSurface());
    }

    public void surfaceDestroyed(SurfaceHolder holder) {

    }


}