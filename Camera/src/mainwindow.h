#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include "openglwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QAction *drawAction, *clearAction, *wireframeAction;
    OpenGLWidget *centralWidget;
    int wireframeChecked = 0;
    ~MainWindow();

private slots:
    void drawShape();
    void clear();
    void drawWireFrame();
};

#endif // MAINWINDOW_H
