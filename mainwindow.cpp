#include "mainwindow.h"
#include <QStringListModel>
#include <QHBoxLayout>
#include <QMimeData>
#include <QDrag>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , centralWidget(new QWidget(this))
    , listView(new QListView(this))
    , delegate(new CustomDelegate(64, this))
    , graphicsView(new CustomGraphicsView(this))
    , clrBtn(new QPushButton("Clear", this))
{
    SetupUI();

    connect(delegate, &CustomDelegate::sizeHintChanged, listView, &QListView::doItemsLayout);
    connect(clrBtn, &QPushButton::clicked, this, &MainWindow::OnClearClicked);
}

void MainWindow::OnClearClicked()
{
    graphicsView->ClearScene();
}

void MainWindow::SetupUI()
{
    QStringList labels = {"Item 1", "Item 2", "Item 3", "Item 4", "Item 5", "Item 6", "Item 7"};
    QList<QIcon> icons;
    icons << QIcon(":/icons/images/tractor_black.png")
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
    hlayout->addLayout(vlayout);
    hlayout->addWidget(graphicsView);

    setMinimumSize(800, 600);
}
