#ifndef SCENE_H
#define SCENE_H

#define RESOLUTION_WIDTH  640
#define RESOLUTION_HEIGHT 480

#include <stdio.h>
#include <stdlib.h>

// qt headers
#include <QDir>
#include <QFile>
#include <QTimer>
#include <QVector>
#include <QSlider>
#include <QGLWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGLFunctions>

// opencv headers
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>

//#include <aruco/aruco.h>

//my headers
#include "principal.h"
#include "texture.h"

using namespace cv;
using namespace std;


class Scene:  public QGLWidget, protected QGLFunctions
{
    Q_OBJECT

    // VideoCapture para levantar la camara numero device
    int device;
    VideoCapture *videoCapture;

    // timer que determina cada cuando se obtiene un nuevo Mat
    QTimer * sceneTimer;

    // vector de clase propia que tiene Mat para cargar textura de la camara
    QVector< Texture * > *textures;

    // metodo principal, donde se procesara cada frame
    void process(Mat &frame);

public:

    Scene(QWidget *parent = 0);

    virtual ~Scene() {}

    // getters and setters
    VideoCapture *getVideoCapture() const;
    void setVideoCapture(VideoCapture *value);

protected:

    // metodos de opengl
    void initializeGL();
    void resizeGL( int width, int height );
    void paintGL();


private slots:

    void slot_updateScene();
};

#endif // SCENE_H
