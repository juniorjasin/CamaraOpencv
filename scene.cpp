#include "scene.h"
#include <QDebug>

Scene::Scene(QWidget *parent): QGLWidget( parent ),
                               device( 1 ),
                               videoCapture ( new cv::VideoCapture( device ) ),
                               sceneTimer(new QTimer),
                               textures( new QVector< Texture * > )
{
    sceneTimer->start( 10 );
    connect( sceneTimer, SIGNAL( timeout() ), SLOT( slot_updateScene() ) );
}


void Scene::initializeGL()
{
    initializeGLFunctions();

    glClearColor( 0, 0, 0, 0 );
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );


    // no se que son estas cosas
    GLfloat lightAmbient[4]; lightAmbient[0] = 0.5f;  lightAmbient[1] = 0.5f;
            lightAmbient[2] = 0.5f;  lightAmbient[3] = 1.0f;

    GLfloat lightDiffuse[4]; lightDiffuse[0] = 1.0f;  lightDiffuse[1] = 1.0f;
            lightDiffuse[2] = 1.0f;  lightDiffuse[3] = 1.0f;

    GLfloat lightPosition[4];lightPosition[0]= 0.0f;  lightPosition[1]= 0.0f;
            lightPosition[2]= 2.0f;  lightPosition[3]= 1.0f;

    glLightfv( GL_LIGHT1, GL_AMBIENT, lightAmbient );  glLightfv( GL_LIGHT1, GL_DIFFUSE, lightDiffuse );
    glLightfv( GL_LIGHT1, GL_POSITION,lightPosition ); glEnable( GL_LIGHT1 );

    textures->append( new Texture( "CameraTexture" ) );

//    Resolver: No existe un decodificador disponible...
//    loadVideos();
//    emit message( "Videos cargados" );
}

void Scene::resizeGL( int width, int height )
{
    glViewport( 0, 0, width, height );
}

void Scene::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glOrtho( 0, RESOLUTION_WIDTH, 0, RESOLUTION_HEIGHT, 1, 1000 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    // Inicio: Gráfico de cámara
    glEnable( GL_TEXTURE_2D );
    glColor3f( 1, 1, 1 );
    glBindTexture( GL_TEXTURE_2D, textures->at( 0 )->id );
    glBegin( GL_QUADS );

        glTexCoord2f( 0, 0 ); glVertex3f( 0, RESOLUTION_HEIGHT, -999 );
        glTexCoord2f( 1, 0 ); glVertex3f( RESOLUTION_WIDTH, RESOLUTION_HEIGHT, -999 );
        glTexCoord2f( 1, 1 ); glVertex3f( RESOLUTION_WIDTH, 0, -999 );
        glTexCoord2f( 0, 1 ); glVertex3f( 0, 0, -999 );

    glEnd();
    glDisable( GL_TEXTURE_2D );
    // Fin: Gráfico de cámara


 /*
    // Fin: Gráfico de cámara

    glMatrixMode( GL_PROJECTION );
    double projectionMatrix[16];

    cv::Size2i sceneSize( RESOLUTION_WIDTH, RESOLUTION_HEIGHT );
    cv::Size2i openGlSize( RESOLUTION_WIDTH, RESOLUTION_HEIGHT );
    cameraParameters->glGetProjectionMatrix( sceneSize, openGlSize, projectionMatrix, 0.05, 10 );

    glLoadMatrixd( projectionMatrix );
    glMatrixMode( GL_MODELVIEW );
    double modelview_matrix[16];

    // Inicio: Graficos sobre la mano abierta
40
columnas Mat: 640
columnas Mat: 640
columnas Mat: 640
columnas Mat: 640
columnas Mat: 640
columnas Mat: 640
    if( matrix.size() == 12 && relevants.size() == 12 )
    {
        vector< Point2f > corners;
        corners.clear();

        corners.push_back( relevants.at( 10 ) );
        corners.push_back( relevants.at( 9 ) );
        corners.push_back( relevants.at( 2 ) );
        corners.push_back( relevants.at( 1 ) );

        Marker marker( corners, 1 );

        marker.calculateExtrinsicsHandMatrix( 0.08f,
                                              cameraParameters->CameraMatrix,
                                              matrix,
                                              cameraParameters->Distorsion,
                                              true );

        marker.glGetModelViewMatrix( modelview_matrix );
        glLoadMatrixd( modelview_matrix );

        // Dibuja imagenes planas
        glTranslatef( 0.005, y, z );
        glRotatef( rotacion, 1, 0, 0 );

//        drawSheet( ( textures->at( textureIndex )->name ), 35 );
        drawBox( ( textures->at( textureIndex )->name ), 20 );
//        drawModel( ( models->at( modelIndex )->name ), 8 );
//        drawVideo( "trailer-RF7.mp4", 100, 200 );

    }

    // Fin: Graficos sobre la mano abierta

    */

    glFlush();
}


/* slot llamado por la señal timeout de sceneTimer.
 * se obtiene cada nuevo frame y se lo pasa al metodo process
 * donde se procesara dicho frame
 */
void Scene::slot_updateScene()
{
    if(!this->getVideoCapture()->isOpened()){  // check if we succeeded
        qDebug() << "videocapture no se abrio correctamente";
        return;
    }


    videoCapture->operator >>( textures->operator []( 0 )->mat );
    process( textures->operator []( 0 )->mat );
    textures->operator []( 0 )->generateFromMat();
    this->updateGL();

    /*
    videoCapture->operator >>( this->getCameraTexture() );
    process( textures->operator []( 0 )->mat );
    textures->operator []( 0 )->generateFromMat();
    this->updateGL();
    */
}


/* se procesa cada frame de la camara o video
 * todo el trabajo esta en este metodo.
 */
void Scene::process(Mat &frame){
    Mat hsvFrame;
    cvtColor( frame, hsvFrame, CV_BGR2Lab );
}



//----------------------------getters and setters---------------------------------
VideoCapture *Scene::getVideoCapture() const
{
    return videoCapture;
}

void Scene::setVideoCapture(VideoCapture *value)
{
    videoCapture = value;
}



