#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QTreeWidget>
#include <QLabel>
#include <QDebug>
#include <iostream>
#include <QScrollArea>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QTextEdit>
#include <QPlainTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    enum    treeItemType{itTopItem=1001,itGroupItem,itImageItem};

    //枚举类型，表示列号
    enum    treeColNum{colItem=0, colItemType=1}; //目录树列的编号定义
private:
    QAction *openFileAction;
    QLabel *labelFilename;
    QLabel *labelCellPos;
    QLabel *labelCellText;
    QPlainTextEdit *text;

    QStandardItemModel* itemModel;
    QItemSelectionModel* selectionModel;

    void initModelFromStringList( QStringList& aFileContent );

    void initModel();

private slots:
    void data_changed( const QModelIndex&, const QModelIndex& );
    void on_actOpenFile_triggered();
    void on_currentChanged( QModelIndex i1, QModelIndex i2 );
};

#endif // MAINWINDOW_H
