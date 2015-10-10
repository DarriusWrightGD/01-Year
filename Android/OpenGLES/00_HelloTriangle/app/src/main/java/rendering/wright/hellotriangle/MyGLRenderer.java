package rendering.wright.hellotriangle;

import android.opengl.GLES30;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by Darrius on 10/8/2015.
 */
public class MyGLRenderer implements GLSurfaceView.Renderer {
    private final String filePath;

    MyGLRenderer(String filePath)
    {
        this.filePath = filePath;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        GLESNativeLib.initGL(filePath);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        GLESNativeLib.resizeGL(width,height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        GLESNativeLib.updateGL();
    }
}
