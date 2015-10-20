package com.example.dawrig.ndkexample;
import android.text.TextUtils;
/**
 * Created by dawrig on 10/19/15.
 */
public class Color {
    private int color;
    public Color(String color) {
        if(TextUtils.isEmpty(color)){
            throw  new IllegalArgumentException();
        }
        this.color = android.graphics.Color.parseColor(color);
    }

    @Override
    public String toString() {
        return String.format("#%06X", color);
    }
}
