#include "mainwindow.h"
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QToolBar>
#include <QOpenGLWidget>
#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle( "Hello Widget" );

    QMenu *file = menuBar()->addMenu(tr("&File"));
    drawAction = new QAction(tr("Draw A Shape"), this);
    clearAction = new QAction(tr("Clear"), this);
    wireframeAction = new QAction(tr("WireFrame"), this);
    //file->addAction(openAction);
    QToolBar *toolBar = addToolBar(tr(""));
    toolBar->addAction(drawAction);
    toolBar->addAction(clearAction);
    toolBar->addAction(wireframeAction);

    connect(drawAction, SIGNAL(triggered()), this, SLOT(drawShape()));
    connect(clearAction, SIGNAL(triggered()), this, SLOT(clear()));
    connect(wireframeAction, SIGNAL(triggered()), this, SLOT(drawWireFrame()));


    //QVBoxLayout *layout = new QVBoxLayout;
    centralWidget = new OpenGLWidget;
    setCentralWidget(centralWidget);
    //layout->addWidget(widget);
    //this->setLayout(layout);
}

void MainWindow::drawShape()
{
    centralWidget->drawShape(OpenGLWidget::Rect);
}

void MainWindow::clear()
{
    centralWidget->clearShape();
}

void MainWindow::drawWireFrame()
{
    this->wireframeChecked = this->wireframeChecked == 0 ? 1 : 0;
    centralWidget->drawWireFrame(wireframeChecked);
}

MainWindow::~MainWindow()
{
}
