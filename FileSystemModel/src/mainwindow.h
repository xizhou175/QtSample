#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QTreeWidget>
#include <QLabel>
#include <QDebug>
#include <iostream>
#include <QScrollArea>
#include <QFileSystemModel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QFileSystemModel *fileModel;

private slots:
};

#endif // MAINWINDOW_H
