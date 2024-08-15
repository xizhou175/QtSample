#include "mainwindow.h"
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QToolBar>
#include <QStatusBar>
#include <QLayout>
#include <QOpenGLWidget>
#include <QToolButton>
#include <QHeaderView>
#include <QFileDialog>
#include <QTableView>
#include <QSplitter>
#include <QGroupBox>
#include <QFileDialog>
#include <QSizePolicy>
#include <QCoreApplication>

#define FixedColumnCount 2

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle( "Hello Widget" );

    QSplitter *splitterMain = new QSplitter(Qt::Horizontal, 0);

    QGroupBox *tableBox = new QGroupBox("TableView", splitterMain);
    QTableView *tableView = new QTableView;
    QGridLayout *tableLayout = new QGridLayout;
    tableLayout->addWidget( tableView, 0, 0 );
    tableBox->setLayout(tableLayout);

    QGroupBox *textBox = new QGroupBox("TextEdit", splitterMain);
    text = new QPlainTextEdit;
    QVBoxLayout *scrollAreaLayout = new QVBoxLayout;
    scrollAreaLayout->addWidget( text );
    textBox->setLayout(scrollAreaLayout);

    QMenu *file = menuBar()->addMenu(tr("&File"));
    QToolBar *toolBar = addToolBar(tr(""));
    labelFilename = new QLabel;
    labelCellPos = new QLabel;
    labelCellText = new QLabel;
    labelFilename->setMinimumWidth(400);
    labelCellPos->setMinimumWidth(150);
    labelCellText->setMinimumWidth(150);
    this->statusBar()->addWidget(labelFilename);
    this->statusBar()->addWidget(labelCellPos);
    this->statusBar()->addWidget(labelCellText);

    auto openFileButton = new QToolButton(toolBar);
    openFileButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    openFileAction = new QAction( QIcon(":/icons/folder1.bmp"), tr("&Open File"), this );
    openFileAction->setIconText("Open File");
    openFileButton->setDefaultAction(openFileAction);
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(on_actOpenFile_triggered()));
    toolBar->addWidget( openFileButton );

    //itemModel = new QStandardItemModel(10, FixedColumnCount, this);
    itemModel = new QStandardItemModel( this );
    itemModel.setColumnCount( 2 );
    selectionModel = new QItemSelectionModel(itemModel);
    tableView->setModel(itemModel);
    tableView->setSelectionModel(selectionModel);
    //tableView->sizePolicy().setHorizontalStretch(80);;

    connect(selectionModel, SIGNAL(currentChanged(QModelIndex, QModelIndex)),
            this, SLOT(on_currentChanged(QModelIndex, QModelIndex)));

    setCentralWidget(splitterMain);
}

void MainWindow::on_actOpenFile_triggered()
{
    QString curPath = QCoreApplication::applicationDirPath(); //获取应用程序的路径
    //调用打开文件对话框打开一个文件
    QString aFileName = QFileDialog::getOpenFileName( this, "打开一个文件", curPath,
                 "井数据文件(*.txt);;所有文件(*.*)" );
    if (aFileName.isEmpty())
        return; //如果未选择文件，退出

    QStringList fFileContent;//文件内容字符串列表
    QFile aFile(aFileName);  //以文件方式读出
    if (aFile.open(QIODevice::ReadOnly | QIODevice::Text)) //以只读文本方式打开文件
    {
        QTextStream aStream(&aFile); //用文本流读取文件
        text->clear();//清空
        while (!aStream.atEnd())
        {
            QString str=aStream.readLine();//读取文件的一行
            text->appendPlainText(str); //添加到文本框显示
            fFileContent.append(str); //添加到 StringList
        }
        aFile.close();//关闭文件

        this->labelFilename->setText("当前文件：" + aFileName);//状态栏显示

        //initModelFromStringList( fFileContent );//从StringList的内容初始化数据模型
    }
}

void MainWindow::on_currentChanged( QModelIndex current, QModelIndex i2 )
{
    labelCellPos->setText(QString::asprintf("当前单元格：%d行，%d列", current.row(),current.column()));
    QStandardItem *aItem = itemModel->itemFromIndex( current );
    this->labelCellText->setText( QString( "单元格内容：" + aItem->text() ) );
}

void MainWindow::initModel()
{
    itemModel->setHorizontalHeaderLabels( ["item", "summary"] );
    QStandardItem *aItem = new QStandardItem( "Getting Started" );
    QStandardItem *bItem = new QStandardItem( "How to familiarize yourself with Qt Designer" );
    QStandardItem *parent = itemModel.invisibleRootItem();

    QList<QStandardItem*> childColumns;
    childColumns<< aItem << bItem;

    parent->appendRow( childColumns );
}

void MainWindow::initModelFromStringList(QStringList& aFileContent)
{
    //从一个StringList 获取数据，初始化数据Model
    int rowCnt=aFileContent.count(); //文本行数，第1行是标题
    itemModel->setRowCount(rowCnt-1); //实际数据行数

    QString header=aFileContent.at( 0 );//第1行是表头
    QStringList headerList = header.split( QRegExp("\\s+"), QString::SkipEmptyParts );
    itemModel->setHorizontalHeaderLabels( headerList ); //设置表头文字

    int j;
    QStandardItem *aItem;
    for (int i = 1; i < rowCnt; i++ )
    {
        QString aLineText = aFileContent.at(i);
        QStringList tmpList = aLineText.split( QRegExp("\\s+"), QString::SkipEmptyParts );
        for( j = 0; j < FixedColumnCount - 1; j++ )
        {
            aItem = new QStandardItem( tmpList.at( j ) );//创建item
            itemModel->setItem( i-1, j, aItem ); //为模型的某个行列位置设置Item
        }

        aItem = new QStandardItem( headerList.at(j) );//最后一列是Checkable,需要设置
        aItem->setCheckable( true ); //设置为Checkable
        if( tmpList.at(j) == "0" )
            aItem->setCheckState(Qt::Unchecked); //根据数据设置check状态
        else
            aItem->setCheckState(Qt::Checked);
        itemModel->setItem( i-1, j, aItem); //为模型的某个行列位置设置Item
    }
}

MainWindow::~MainWindow()
{
}
