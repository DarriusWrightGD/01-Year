package rendering.wright.esengine;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLES30;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import rendering.wright.esengine.nativec.NativeLib;

/**
 * Created by Darrius on 10/11/2015.
 */
public class GLESView extends GLSurfaceView{
    private GLESRenderer renderer;
    public GLESView(Context context) {
        super(context);
        setEGLContextClientVersion(3);
        renderer = new GLESRenderer(context.getPackageResourcePath());
        setRenderer(renderer);
    }

    public class GLESRenderer implements GLSurfaceView.Renderer{

        private final String path;

        GLESRenderer(String path)
        {
            this.path = path;
        }

        @Override
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            GLES30.glClearColor(0.5f,0.7f,1.0f,1.0f);
            NativeLib.Init(path);
        }

        @Override
        public void onSurfaceChanged(GL10 gl, int width, int height) {
            GLES30.glViewport(0,0,width,height);
            NativeLib.Resize(width,height);
        }

        @Override
        public void onDrawFrame(GL10 gl) {
            GLES30.glClear(GLES30.GL_COLOR_BUFFER_BIT);
            NativeLib.Update();
        }
    }
}
