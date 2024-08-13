#include "mainwindow.h"
#include <QAction>
#include <QDockWidget>
#include <QMenuBar>
#include <QMessageBox>
#include <QToolBar>
#include <QStatusBar>
#include <QLayout>
#include <QOpenGLWidget>
#include <QToolButton>
#include <QHeaderView>
#include <QScrollArea>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QGridLayout>
#include <QGroupBox>
#include <QTreeView>
#include <QListView>
#include <QTableView>
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle( "FileSytem Model" );

    //QGridLayout *mainLayout = new QGridLayout;
    QSplitter *splitterMain = new QSplitter(Qt::Horizontal, 0);
    QGroupBox *tree = new QGroupBox("TreeView", splitterMain);
    QTreeView *treeview = new QTreeView;
    QVBoxLayout *treeLayout = new QVBoxLayout;
    treeLayout->addWidget( treeview );
    tree->setLayout(treeLayout);
    //mainLayout->addWidget( tree, 0, 0, /*row span*/2, /*col span*/1 );

    QSplitter *splitterRight = new QSplitter( Qt::Vertical, splitterMain );
    QGroupBox *list = new QGroupBox("ListView", splitterRight);
    QListView *listview = new QListView;
    QVBoxLayout *listLayout = new QVBoxLayout;
    listLayout->addWidget( listview );
    list->setLayout(listLayout);
    //mainLayout->addWidget( list, 0, 1, /*row span*/1, /*col span*/1 );

    QGroupBox *table = new QGroupBox("TableView", splitterRight);
    QTableView *tableview = new QTableView;
    QVBoxLayout *tableLayout = new QVBoxLayout;
    tableLayout->addWidget( tableview );
    table->setLayout(tableLayout);
    //mainLayout->addWidget( table, 1, 1, /*row span*/1, /*col span*/1 );

    //mainLayout->setRowStretch( 0, 1 );
    //mainLayout->setRowStretch( 1, 1 );
    //mainLayout->setOriginCorner( Qt::BottomLeftCorner );

    //QWidget *centralWidget = new QWidget;
    setCentralWidget( splitterMain );
    //this->centralWidget()->setLayout( mainLayout );
    fileModel = new QFileSystemModel(this);
    fileModel->setRootPath(QDir::currentPath()); //设置根目录

    treeview->setModel(fileModel); //设置数据模型
    listview->setModel(fileModel); //设置数据模型
    tableview->setModel(fileModel); //设置数据模型

    connect( treeview,SIGNAL(clicked(QModelIndex)),
             listview,SLOT(setRootIndex(QModelIndex)));

    connect( treeview,SIGNAL(clicked(QModelIndex)),
             tableview,SLOT(setRootIndex(QModelIndex)));
}

MainWindow::~MainWindow()
{
}
