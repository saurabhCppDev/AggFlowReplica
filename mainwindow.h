#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include "customgraphicsview.h"
#include <customdelegate.h>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void OnClearClicked();

private:
    void SetupUI();

    QWidget *centralWidget;
    QListView *listView;
    CustomDelegate *delegate;
    CustomGraphicsView *graphicsView;
    QPushButton* clrBtn;
};

#endif // MAINWINDOW_H
