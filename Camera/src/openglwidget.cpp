#include "openglwidget.h"
#include <iostream>

float vertices[] = {
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
 0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
 0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};

QVector<QVector3D> cubePositions= {
QVector3D( 0.0f, 0.0f, 0.0f),
QVector3D( 2.0f, 5.0f, -15.0f),
QVector3D(-1.5f, -2.2f, -2.5f),
QVector3D(-3.8f, -2.0f, -12.3f),
QVector3D( 2.4f, -0.4f, -3.5f),
QVector3D(-1.7f, 3.0f, -7.5f),
QVector3D( 1.3f, -2.0f, -2.5f),
QVector3D( 1.5f, 2.0f, -2.5f),
QVector3D( 1.5f, 0.2f, -1.5f),
QVector3D(-1.3f, 1.0f, -1.5f)
};

unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};

#define TIMEOUT 100
OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
    //Camera position
    auto cameraPos = QVector3D(0.0f, 0.0f, 2.0f);
    auto up = QVector3D(0.0f, 1.0f, 0.0f);

    m_camera = Camera(std::move(cameraPos), std::move(up) );

    connect(&timer,SIGNAL(timeout()),this,SLOT(on_timeout()));
    timer.start(100);
    m_time.start();
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices, GL_STATIC_DRAW);

    //告知显卡如何解析缓冲里的属性值
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    //开启VAO管理的第一个属性值
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

	/*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);*/

    int success;
    this->shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/shapes.vert");
    this->shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/shapes.frag");

    success=this->shaderProgram.link();
    if(!success)
        qDebug()<<"ERR:"<<shaderProgram.log();

    if( success )
    {
        this->shaderProgram.bind();
        this->shaderProgram.setUniformValue("offset", 0.4f);
    }

    textureWall=new QOpenGLTexture(QImage(":/images/wall.jpg").mirrored());
    textureSmile=new QOpenGLTexture(QImage(":/images/awesomeface.png").mirrored());
    textureSmall=new QOpenGLTexture(QImage(":/images/small.png").mirrored());

    shaderProgram.bind();
    shaderProgram.setUniformValue("textureWall",0);
    shaderProgram.setUniformValue("textureSmile",1);
    shaderProgram.setUniformValue("textureSmall",3);
 
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // go take a rest for now
	glBindVertexArray(0);

}

void OpenGLWidget::resizeGL(int w, int h)
{

}

void OpenGLWidget::paintGL()
{
    QMatrix4x4 model;
    QMatrix4x4 projection;
    projection.perspective( m_camera.Zoom, (float)width() / height(), 0.1, 100 );

    //const float radius = 30.0f;
    float time = m_time.elapsed()/1000.0;
    //float camX = sin(time) * radius;
    //float camZ = cos(time) * radius;
    QMatrix4x4 view = m_camera.GetViewMatrix();

    //unsigned int time = QTime::currentTime().msec();

    model.rotate(time, 1.0f, 0.0f, 0.0f);
    //model.translate(0,-0.0,0.3);

    view.translate(0.0,0.0,-4);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->shaderProgram.bind();
    glBindVertexArray(VAO);

    switch (m_shape) {
    case Rect:
        textureWall->bind(0);
        textureSmile->bind(1);
        textureSmall->bind(3);

        shaderProgram.setUniformValue("model", model);
        shaderProgram.setUniformValue("view", view);
        shaderProgram.setUniformValue("projection", projection);

        glDrawArrays(GL_TRIANGLES,0,36);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

        foreach (auto item, cubePositions) {
            model.setToIdentity();
            model.translate(item);
            model.rotate(time, 1.0f, 5.0f, 0.5f);
            shaderProgram.setUniformValue("model", model);
            glDrawArrays(GL_TRIANGLES,0,36);
        }
        break;
    default:
        break;
    }
}

void OpenGLWidget::drawShape(OpenGLWidget::Shape shape)
{
    m_shape = shape;
    update();
}

void OpenGLWidget::clearShape()
{
    m_shape = OpenGLWidget::None;
    update();
}

void OpenGLWidget::drawWireFrame(bool checked)
{
    makeCurrent();
    if(checked)
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    update();
    doneCurrent();
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    float deltaTime = TIMEOUT/1000.0;
    switch (event->key()) {
    case Qt::Key_Up:
        break;
    case Qt::Key_Down:
        break;
    case Qt::Key_W: m_camera.ProcessKeyboard(FORWARD, deltaTime);break;
    case Qt::Key_S: m_camera.ProcessKeyboard(BACKWARD, deltaTime);break;
    case Qt::Key_D: m_camera.ProcessKeyboard(RIGHT, deltaTime);break;
    case Qt::Key_A: m_camera.ProcessKeyboard(LEFT, deltaTime);break;
    default:
        break;
    }

    update();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    static QPoint lastPos(width()/2,height()/2);
    auto currentPos=event->pos();
    QPoint deltaPos=currentPos-lastPos;
    lastPos=currentPos;

    m_camera.ProcessMouseMovement(deltaPos.x(),-deltaPos.y());
    update();
}

void OpenGLWidget::wheelEvent(QWheelEvent *event)
{
    m_camera.ProcessMouseScroll(event->angleDelta().y()/120);
    update();
}

OpenGLWidget::~OpenGLWidget()
{
    if(!isValid()) return;
    makeCurrent();
    glDeleteBuffers(1,&VBO);
    //glDeleteBuffers(1,&EBO);
    glDeleteVertexArrays(1,&VAO);
    doneCurrent();
}

void OpenGLWidget::on_timeout()
{
    update();
}
