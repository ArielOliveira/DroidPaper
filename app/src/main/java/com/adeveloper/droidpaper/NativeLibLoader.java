package com.adeveloper.droidpaper;

import android.view.Surface;

/**
 * Created by ariel on 02/02/18.
 */

public class NativeLibLoader {
    private static boolean loaded = false;

    private static boolean running = false;

    protected static synchronized void load() {
        if (loaded) return;
        System.loadLibrary("native-lib");
        loaded = true;
    }

    protected static synchronized void setRunning(boolean var) {
        running = var;
    }

    public static synchronized boolean getRunning() {return running;}


    public static native void nativeSurfaceCreated();
    public static native void nativeSurfaceChanged(Surface surface, boolean running);
    public static native void nativeSurfaceDestroyed();

    public static native void nativeOnStart();
    public static native void nativeOnResume();
    public static native void nativeOnPause();
    public static native void nativeOnStop();


}
