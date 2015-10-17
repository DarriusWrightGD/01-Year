package rendering.wright.esengine.nativec;

/**
 * Created by Darrius on 10/11/2015.
 */
public class NativeLib {

    static{
        System.loadLibrary("NativeEngine");
    }

    public static native void Init(String path);
    public static native void Resize(int width, int height);
    public static native void Update();
}
