#include "MainWindow.h"
#include <QStringListModel>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QMimeData>
#include <QDrag>
#include <QMenuBar>
#include <QLabel>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>


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
    , status(new QLabel(this))
    ,currentFile("saveTest.scene")
    ,zoomFactor(1.5)

{
    SetupUI();
    createActions();
    createMenus();
    createToolbar();

    connect(delegate, &CustomDelegate::sizeHintChanged, listView, &QListView::doItemsLayout);
    connect(clrBtn, &QPushButton::clicked, this, &MainWindow::OnClearClicked);

    connect(graphicsView, &CustomGraphicsView::PublishOldData, this, &MainWindow::onOldPos);
    connect(graphicsView, &CustomGraphicsView::PublishNewData, this, &MainWindow::onNewPos);

    connect(graphicsView, &CustomGraphicsView::PublishUndoData, this, &MainWindow::onUndoPos);
    connect(graphicsView, &CustomGraphicsView::PublishRedoData, this, &MainWindow::onRedoPos);
    connect(graphicsView, &CustomGraphicsView::resultUpdated, this, &MainWindow::updateResult);

    runAction = new QAction("Run", this);
    menuBar()->addAction(runAction);

    connect(runAction, &QAction::triggered, graphicsView, &CustomGraphicsView::onResult);
    status->setText("Result : 0");
    statusBar()->addPermanentWidget(status);

}

void MainWindow::OnClearClicked()
{
    graphicsView->ClearScene();
    CustomPixmapItem::GlobalItemId = 0;
    status->setText("Result : 0");
    statusBar()->showMessage(tr("Scene cleared"), 2000);
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
    statusBar();
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(loadAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));

    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
    editMenu->addSeparator();

    viewMenu = menuBar()->addMenu(tr("&View"));

    viewMenu->addAction(zoomInAction);
    viewMenu->addAction(zoomOutAction);
    viewMenu->addSeparator();

}

void MainWindow::createActions()
{

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Ctrl+S"));
    saveAction->setIcon(QIcon(":/icons/images/save.png"));
    connect(saveAction, &QAction::triggered, this, &MainWindow::onSave);

    saveAsAction = new QAction(tr("&Save As"), this);
    saveAsAction->setShortcuts(QKeySequence::SaveAs);
    saveAsAction->setShortcut(tr("Ctrl+Shift+S"));
    saveAsAction->setIcon(QIcon(":/icons/images/save_as.png"));
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::onSaveAs);

    loadAction = new QAction(tr("&Load"), this);
    loadAction->setShortcuts(QKeySequence::Open);
    loadAction->setStatusTip(tr("Ctrl+O"));
    loadAction->setIcon(QIcon(":/icons/images/loading.png"));
    connect(loadAction, &QAction::triggered, this, &MainWindow::onLoad);

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit"));
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);

    undoAction = new QAction(tr("&Undo"), this);
    undoAction->setShortcut(tr("Ctrl+Z"));
    undoAction->setStatusTip(tr("Undo last operation"));
    undoAction->setIcon(QIcon(":/icons/images/undo.png"));
    connect(undoAction, &QAction::triggered, graphicsView, &CustomGraphicsView::UndoTriggered);

    redoAction = new QAction(tr("&Redo"), this);
    redoAction->setShortcut(tr("Ctrl+Shift+Z"));
    redoAction->setStatusTip(tr("Redo last operation"));
    redoAction->setIcon(QIcon(":/icons/images/redo.png"));
    connect(redoAction, &QAction::triggered, graphicsView, &CustomGraphicsView::RedoTriggered);

    zoomInAction = new QAction(tr("&Zoom In"), this);
    zoomInAction->setStatusTip(tr("Zoom In"));
    zoomInAction->setIcon(QIcon(":/icons/images/zoom_in.png"));
    connect(zoomInAction, &QAction::triggered, this, &MainWindow::zoomIn);

    zoomOutAction = new QAction(tr("&Zoom Out"), this);
    zoomOutAction->setStatusTip(tr("Zoom Out"));
    zoomOutAction->setIcon(QIcon(":/icons/images/zoom_out.png"));
    connect(zoomOutAction, &QAction::triggered, this, &MainWindow::zoomOut);
}

void MainWindow::createToolbar()
{
    QToolBar *editToolBar;
    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(saveAction);
    editToolBar->addSeparator();
    editToolBar->addAction(undoAction);
    editToolBar->addAction(redoAction);
    editToolBar->addSeparator();
    editToolBar->addAction(zoomInAction);
    editToolBar->addAction(zoomOutAction);
    editToolBar->addSeparator();
    removeToolBar(editToolBar);
    addToolBar(editToolBar);
    editToolBar->show();

}

void MainWindow::setCurrentFile(const QString &fileName)
{
    currentFile = fileName;
    setWindowModified(false);
    setWindowFilePath(currentFile.isEmpty() ? tr("untitled.xml") : currentFile);
}

void MainWindow::onSave()
{
    QString fileName = "saveTest.scene";//QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Scene Files (*.scene)"));
    if (!fileName.isEmpty()) {
        graphicsView->saveToFile(fileName);
    }

    QString file = "saveTest.xml";
    if (!file.isEmpty()) {
        graphicsView->saveToXml(file);
    }
}


void MainWindow::onSaveAs()
{

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As File"), "", tr("XML Files (*.xml);;Scene Files(*.scene)"));
    if (fileName.isEmpty())
        return;
    setCurrentFile(fileName);
    onSave();

}

void MainWindow::onLoad()
{
    graphicsView->ClearScene();
    QString fileName = "saveTest.scene";//QFileDialog::getOpenFileName(this, tr("Load File"), "", tr("Scene Files (*.scene)"));
    if (!fileName.isEmpty()) {
        graphicsView->loadFromFile(fileName);
    }
//        QString file = "saveTest.xml";
//        if (!file.isEmpty()) {
//            graphicsView->loadFromXml(file);
//        }
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

void MainWindow::updateResult(const QString &result)
{
    status->setText("Result : " + result);
}

void MainWindow::zoomIn()
{
    zoomFactor *= 1.5;
    graphicsView->scale(1.5, 1.5);
}

void MainWindow::zoomOut()
{
    zoomFactor /= 1.5;
    graphicsView->scale(1.0 / 1.5, 1.0 / 1.5);
}

