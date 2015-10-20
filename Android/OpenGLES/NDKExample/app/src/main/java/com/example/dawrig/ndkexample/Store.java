package com.example.dawrig.ndkexample;

/**
 * Created by dawrig on 10/17/15.
 */
public class Store {

    static{
        System.loadLibrary("NDKLib");
    }

    public native int getCount();
    public native String getString(String key);
    public native void setString(String key, String value);
    public native int getInteger(String key);
    public native void setInteger(String key, int value);

}
