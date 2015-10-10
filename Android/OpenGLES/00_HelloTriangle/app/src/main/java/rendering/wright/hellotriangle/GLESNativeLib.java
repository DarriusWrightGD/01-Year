package rendering.wright.hellotriangle;

/**
 * Created by Darrius on 10/8/2015.
 */
public class GLESNativeLib {
    static{
        System.loadLibrary("OpenGLLib");
    }

    public static native void initGL(String path);
    public static native void resizeGL(int width, int height);
    public static native void updateGL();
}
