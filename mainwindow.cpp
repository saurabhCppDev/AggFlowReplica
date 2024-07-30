#include "MainWindow.h"
#include <QStringListModel>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QMimeData>
#include <QDrag>
#include <QMenuBar>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , centralWidget(new QWidget(this))
    , listView(new QListView(this))
    , delegate(new CustomDelegate(64, this))
    , graphicsView(new CustomGraphicsView(this))
    , clrBtn(new QPushButton("Clear", this))
    , oldData(new QLabel)
    , newData(new QLabel)
    , UndoData(new QLabel)
    , RedoData(new QLabel)
{
    SetupUI();

    connect(delegate, &CustomDelegate::sizeHintChanged, listView, &QListView::doItemsLayout);
    connect(clrBtn, &QPushButton::clicked, this, &MainWindow::OnClearClicked);

    connect(graphicsView, &CustomGraphicsView::PublishOldData, this, &MainWindow::onOldPos);
    connect(graphicsView, &CustomGraphicsView::PublishNewData, this, &MainWindow::onNewPos);

    connect(graphicsView, &CustomGraphicsView::PublishUndoData, this, &MainWindow::onUndoPos);
    connect(graphicsView, &CustomGraphicsView::PublishRedoData, this, &MainWindow::onRedoPos);

    QAction *saveAction = new QAction("Save", this);
    QAction *loadAction = new QAction("Load", this);

    connect(saveAction, &QAction::triggered, this, &MainWindow::onSave);
    connect(loadAction, &QAction::triggered, this, &MainWindow::onLoad);

    menuBar()->addAction(saveAction);
    menuBar()->addAction(loadAction);

    QAction *undoAction = new QAction("Undo", this);
    QAction *redoAction = new QAction("Redo", this);

    connect(undoAction, &QAction::triggered, graphicsView, &CustomGraphicsView::UndoTriggered);
    connect(redoAction, &QAction::triggered, graphicsView, &CustomGraphicsView::RedoTriggered);

    menuBar()->addAction(undoAction);
    menuBar()->addAction(redoAction);
}

void MainWindow::OnClearClicked()
{
    graphicsView->ClearScene();
}

void MainWindow::SetupUI()
{
    QStringList labels = {"Item 0", "Item 1", "Item 2", "Item 3", "Item 4", "Item 5", "Item 6", "Item 7"};
    QList<QIcon> icons;
    icons << QIcon(":/icons/images/start_point.png")
          << QIcon(":/icons/images/tractor_black.png")
          << QIcon(":/icons/images/tractor_ok.png")
          << QIcon(":/icons/images/tractor_On_Field.png")
          << QIcon(":/icons/images/tractor_orange.png")
          << QIcon(":/icons/images/tractor_red.png")
          << QIcon(":/icons/images/tractor_transperant.png")
          << QIcon(":/icons/images/tractor_yellow.png");

    IconListModel *model = new IconListModel(this);
    model->setData(labels, icons);

    listView->setModel(model);
    listView->setIconSize(QSize(64, 64));
    listView->setItemDelegate(delegate);
    listView->setDragEnabled(true);
    listView->setFixedWidth(200);

    setCentralWidget(centralWidget);
    QVBoxLayout *vlayout = new QVBoxLayout();
    QHBoxLayout *hlayout = new QHBoxLayout(centralWidget);
    vlayout->addWidget(listView);
    vlayout->addWidget(clrBtn);
//    vlayout->addWidget(oldData);
//    vlayout->addWidget(newData);
//    vlayout->addWidget(new QLabel("After Undo/Redo"));
//    vlayout->addWidget(UndoData);
//    vlayout->addWidget(RedoData);
    hlayout->addLayout(vlayout);
    hlayout->addWidget(graphicsView);

    setMinimumSize(800, 600);
}

void MainWindow::onSave()
{
    QString fileName = "saveTest.scene";//QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Scene Files (*.scene)"));
    if (!fileName.isEmpty()) {
        graphicsView->saveToFile(fileName);
    }
}

void MainWindow::onLoad()
{
    graphicsView->ClearScene();
    QString fileName = "saveTest.scene";//QFileDialog::getOpenFileName(this, tr("Load File"), "", tr("Scene Files (*.scene)"));
    if (!fileName.isEmpty()) {
        graphicsView->loadFromFile(fileName);
    }
}

void MainWindow::onOldPos(QString data)
{
    oldData->setText(data);
}

void MainWindow::onNewPos(QString data)
{
    newData->setText(data);
}

void MainWindow::onUndoPos(QString data)
{
    UndoData->setText(data);
}

void MainWindow::onRedoPos(QString data)
{
    RedoData->setText(data);
}
