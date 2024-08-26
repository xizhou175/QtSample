#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLShaderProgram>
#include <math.h>
#include <QTimer>
#include <QTime>
#include <QOpenGLTexture>
#include <QKeyEvent>
#include "camera.h"

class OpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_4_3_Core
{
    Q_OBJECT
public:
    enum Shape{ None, Rect, Circle, Triangle };
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();
    unsigned int VBO, VAO, EBO;

    void drawShape(OpenGLWidget::Shape shape);
    void clearShape();
    void drawWireFrame(bool checked);
    QTimer timer;
    QTime m_time;

    OpenGLWidget::Shape m_shape;
    QOpenGLShaderProgram shaderProgram;
    QOpenGLTexture * textureWall;
    QOpenGLTexture * textureSmile;
    QOpenGLTexture * textureSmall;
    Camera m_camera;

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

signals:

public slots:
    void on_timeout();
};

#endif
