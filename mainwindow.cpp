#include "MainWindow.h"
#include <QStringListModel>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QMimeData>
#include <QDrag>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , centralWidget(new QWidget(this))
    , listView(new QListView(this))
    , menuListView(new QListView(this))
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

    connect(listView, &QListView::clicked, this, &MainWindow::onItemClicked);

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

void MainWindow::SetupUI()
{

    QStringList labels;
    QList<QIcon> icons;
    labels << "Item 1" << "Item 2" << "Item 3"<< "Item 4"
           << "Item 5" << "Item 6" << "Item 7"<< "Item 8"
           << "Item 9" << "Item 10" << "Item 11" << "Item 12"
           << "Item 13"<< "Item 14" ;//<< "Item 15" << "Item 16";

    icons << QIcon(":/icons/images/parent/parent_1.png")
          << QIcon(":/icons/images/parent/parent_2.png")
          << QIcon(":/icons/images/parent/parent_3.png")
          << QIcon(":/icons/images/parent/parent_4.png")
          << QIcon(":/icons/images/parent/parent_5.png")
          << QIcon(":/icons/images/parent/parent_6.png")
          << QIcon(":/icons/images/parent/parent_7.png")
          << QIcon(":/icons/images/parent/parent_8.png")
          << QIcon(":/icons/images/parent/parent_9.png")
          << QIcon(":/icons/images/parent/parent_10.png")
          << QIcon(":/icons/images/parent/parent_11.png")
          << QIcon(":/icons/images/parent/parent_12.png")
          << QIcon(":/icons/images/parent/parent_13.png")
          << QIcon(":/icons/images/parent/parent_14.png");
          // << QIcon(":/icons/images/new/parent_15.png")
          // << QIcon(":/icons/images/new/parent_16.png");

    IconListModel *model = new IconListModel(this);
    model->setData(labels, icons);

    listView->setModel(model);
    listView->setIconSize(QSize(40, 40));
    listView->setItemDelegate(delegate);
    listView->setDragEnabled(true);
    listView->setFixedWidth(80);
    menuListView->setFixedWidth(60);
    menuListView->setIconSize(QSize(50, 50));

    clrBtn->setFixedWidth(50);
    setCentralWidget(centralWidget);
    QVBoxLayout *vlayout = new QVBoxLayout();
    QHBoxLayout *hlayout = new QHBoxLayout(centralWidget);
    vlayout->addWidget(listView);
    // vlayout->addWidget(clrBtn);    // to be removed
    hlayout->addLayout(vlayout);
    hlayout->addWidget(menuListView);
    hlayout->addWidget(graphicsView);


    hlayout->setSpacing(7);

    setMinimumSize(800, 600);
}


void MainWindow::OnClearClicked()
{
    graphicsView->ClearScene();
}

void MainWindow::onSave()
{
    QString fileName = "saveTest.scene";
    if (!fileName.isEmpty()) {
        graphicsView->saveToFile(fileName);
    }
}

void MainWindow::onLoad()
{
    graphicsView->ClearScene();
    QString fileName = "saveTest.scene";
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

void MainWindow::onItemClicked(const QModelIndex &index)
{
    QStandardItemModel *menuModel = new QStandardItemModel(this);
    QList<QIcon> menuIcons;

    switch (index.row()) {
    case 0:
        menuIcons = {QIcon(":/icons/images/parent/Child1/child_1_1.png"),
                     QIcon(":/icons/images/parent/Child1/child_1_2.png"),
                     QIcon(":/icons/images/parent/Child1/child_1_3.png"),
                     QIcon(":/icons/images/parent/Child1/child_1_4.png"),
                     QIcon(":/icons/images/parent/Child1/child_1_5.png"),
                     QIcon(":/icons/images/parent/Child1/child_1_6.png"),
                     QIcon(":/icons/images/parent/Child1/child_1_7.png")};
        break;
    case 1:
        menuIcons = {QIcon(":/icons/images/parent/Child2/child_2_1.png"),
                     QIcon(":/icons/images/parent/Child2/child_2_2.png"),
                     QIcon(":/icons/images/parent/Child2/child_2_2.png"),
                     QIcon(":/icons/images/parent/Child2/child_2_3.png"),
                     QIcon(":/icons/images/parent/Child2/child_2_4.png"),
                     QIcon(":/icons/images/parent/Child2/child_2_5.png"),
                     QIcon(":/icons/images/parent/Child2/child_2_6.png"),
                     QIcon(":/icons/images/parent/Child2/child_2_7.png")};
        break;
    case 2:
        menuIcons = {QIcon(":/icons/images/parent/Child3/child_3_1.png"),
                     QIcon(":/icons/images/parent/Child3/child_3_2.png"),
                     QIcon(":/icons/images/parent/Child3/child_3_3.png"),
                     QIcon(":/icons/images/parent/Child3/child_3_4.png"),
                     QIcon(":/icons/images/parent/Child3/child_3_5.png"),
                     QIcon(":/icons/images/parent/Child3/child_3_6.png"),
                     QIcon(":/icons/images/parent/Child3/child_3_7.png"),
                     QIcon(":/icons/images/parent/Child3/child_3_8.png")};
        break;
    case 3:
        menuIcons = {QIcon(":/icons/images/parent/Child4/child4_1.png"),
                     QIcon(":/icons/images/parent/Child4/child4_2.png"),
                     QIcon(":/icons/images/parent/Child4/child4_3.png"),
                     QIcon(":/icons/images/parent/Child4/child4_4.png"),
                     QIcon(":/icons/images/parent/Child4/child4_5.png")};
        break;
    case 4:
        menuIcons = {QIcon(":/icons/images/parent/Child5/child_5_1.png"),
                     QIcon(":/icons/images/parent/Child5/child_5_2.png"),
                     QIcon(":/icons/images/parent/Child5/child_5_3.png"),
                     QIcon(":/icons/images/parent/Child5/child_5_4.png"),
                     QIcon(":/icons/images/parent/Child5/child_5_5.png"),
                     QIcon(":/icons/images/parent/Child5/child_5_6.png")};
        break;
    case 5:
        menuIcons = {QIcon(":/icons/images/parent/Child6/child_6_1.png"),
                     QIcon(":/icons/images/parent/Child6/child_6_2.png"),
                     QIcon(":/icons/images/parent/Child6/child_6_2.png"),
                     QIcon(":/icons/images/parent/Child6/child_6_3.png"),
                     QIcon(":/icons/images/parent/Child6/child_6_4.png"),
                     QIcon(":/icons/images/parent/Child6/child_6_5.png"),
                     QIcon(":/icons/images/parent/Child6/child_6_6.png"),
                     QIcon(":/icons/images/parent/Child6/child_6_7.png"),
                     QIcon(":/icons/images/parent/Child6/child_6_8.png"),
                     QIcon(":/icons/images/parent/Child6/child_6_9.png")};
        break;
    case 6:
        menuIcons = {QIcon(":/icons/images/parent/Child7/child_7_1.png"),
                     QIcon(":/icons/images/parent/Child7/child_7_2.png"),
                     QIcon(":/icons/images/parent/Child7/child_7_2.png"),
                     QIcon(":/icons/images/parent/Child7/child_7_3.png"),
                     QIcon(":/icons/images/parent/Child7/child_7_4.png"),
                     QIcon(":/icons/images/parent/Child7/child_7_5.png"),
                     QIcon(":/icons/images/parent/Child7/child_7_6.png"),
                     QIcon(":/icons/images/parent/Child7/child_7_7.png")};
        break;
    case 7:
        menuIcons = {QIcon(":/icons/images/parent/Child8/child_8_1.png"),
                     QIcon(":/icons/images/parent/Child8/child_8_2.png"),
                     QIcon(":/icons/images/parent/Child8/child_8_3.png"),
                     QIcon(":/icons/images/parent/Child8/child_8_4.png"),
                     QIcon(":/icons/images/parent/Child8/child_8_5.png"),
                     QIcon(":/icons/images/parent/Child8/child_8_6.png"),
                     QIcon(":/icons/images/parent/Child8/child_8_7.png"),
                     QIcon(":/icons/images/parent/Child8/child_8_8.png"),
                     QIcon(":/icons/images/parent/Child8/child_8_9.png")};
        break;
    case 8:
        menuIcons = {QIcon(":/icons/images/parent/Child9/child_9_1.png"),
                     QIcon(":/icons/images/parent/Child9/child_9_2.png")};
        break;
    case 9:
        menuIcons = {QIcon(":/icons/images/parent/Child10/child_10_1.png"),
                     QIcon(":/icons/images/parent/Child10/child_10_2.png"),
                     QIcon(":/icons/images/parent/Child10/child_10_3.png"),
                     QIcon(":/icons/images/parent/Child10/child_10_4.png"),
                     QIcon(":/icons/images/parent/Child10/child_10_5.png")};
        break;
    case 10:
        menuIcons = {QIcon(":/icons/images/parent/Child11/child_11_1.png"),
                     QIcon(":/icons/images/parent/Child11/child_11_2.png"),
                     QIcon(":/icons/images/parent/Child11/child_11_3.png"),
                     QIcon(":/icons/images/parent/Child11/child_11_4.png"),
                     QIcon(":/icons/images/parent/Child11/child_11_5.png"),
                     QIcon(":/icons/images/parent/Child11/child_11_6.png"),
                     QIcon(":/icons/images/parent/Child11/child_11_7.png"),
                     QIcon(":/icons/images/parent/Child11/child_11_8.png")};
        break;
    case 11:
        menuIcons = {QIcon(":/icons/images/parent/Child12/child_12_1.png")};
        break;
    case 12:
        menuIcons = {QIcon(":/icons/images/parent/Child13/child_13_1.png"),
                     QIcon(":/icons/images/parent/Child13/child_13_2.png"),
                     QIcon(":/icons/images/parent/Child13/child_13_3.png"),
                     QIcon(":/icons/images/parent/Child13/child_13_4.png")};
        break;
    case 13:
        menuIcons = {QIcon(":/icons/images/parent/Child14/child_14_1.png"),
                     QIcon(":/icons/images/parent/Child14/child_14_2.png"),
                     QIcon(":/icons/images/parent/Child14/child_14_3.png"),
                     QIcon(":/icons/images/parent/Child14/child_14_4.png"),
                     QIcon(":/icons/images/parent/Child14/child_14_5.png"),
                     QIcon(":/icons/images/parent/Child14/child_14_6.png"),
                     QIcon(":/icons/images/parent/Child14/child_14_7.png"),
                     QIcon(":/icons/images/parent/Child14/child_14_8.png"),
                     QIcon(":/icons/images/parent/Child14/child_14_9.png"),
                     QIcon(":/icons/images/parent/Child14/child_14_10.png"),
                     QIcon(":/icons/images/parent/Child14/child_14_11.png"),
                     QIcon(":/icons/images/parent/Child14/child_14_12.png")};
        break;

    default:
        menuIcons = {QIcon()};
        break;
    }

    for (const auto &icon : menuIcons) {
        QStandardItem *menuItem = new QStandardItem();
        menuItem->setIcon(icon);
        menuModel->appendRow(menuItem);
    }

    menuListView->setModel(menuModel);
}
