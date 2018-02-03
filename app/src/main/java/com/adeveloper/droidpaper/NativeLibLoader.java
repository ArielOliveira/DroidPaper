package com.adeveloper.droidpaper;

import android.view.Surface;

/**
 * Created by ariel on 02/02/18.
 */

public class NativeLibLoader {
    private static boolean loaded = false;

    protected static synchronized void load() {
        if (loaded) return;
        System.loadLibrary("native-lib");
        loaded = true;
    }

    public static native void nativeSurfaceCreated();
    public static native void nativeSurfaceChanged(Surface surface);
    public static native void nativeSurfaceDestroyed();


}
