package rendering.wright.hellotriangle;

import android.content.Context;
import android.opengl.GLSurfaceView;

/**
 * Created by Darrius on 10/8/2015.
 */
public class MyGLSurfaceView extends GLSurfaceView {
    private final MyGLRenderer renderer;

    public MyGLSurfaceView(Context context) {
        super(context);
        setEGLContextClientVersion(3);
        renderer = new MyGLRenderer(context.getPackageResourcePath());
        setRenderer(renderer);
    }

}
