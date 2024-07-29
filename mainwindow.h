#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include "CustomGraphicsView.h"
#include <customdelegate.h>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void OnClearClicked();
    void onSave();
    void onLoad();
    void onOldPos(QString data);
    void onNewPos(QString data);
    void onUndoPos(QString data);
    void onRedoPos(QString data);

private:
    void SetupUI();

    QWidget *centralWidget;
    QListView *listView;
    CustomDelegate *delegate;
    CustomGraphicsView *graphicsView;
    QPushButton* clrBtn;
    QLabel* oldData;
    QLabel* newData;
    QLabel* UndoData;
    QLabel* RedoData;
};

#endif // MAINWINDOW_H
