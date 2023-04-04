#include <QMenuBar>
#include <QMessageBox>
#include <QToolBar>
#include <QStatusBar>
#include <QFile>
#include <QGraphicsScene>
#include <QDir>
#include <QImageReader>
#include <QGraphicsPixmapItem>
#include <QGraphicsProxyWidget>
#include <QGraphicsGridLayout>
#include <QDirIterator>
#include "drawingwidget.h"

#include <QDebug>
#include <QTranslator>

#include "photolibrary.h"
#include "ui_photolibrary.h"

PhotoLibrary::PhotoLibrary(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PhotoLibrary)
{

    ui->setupUi(this);


        qApp->installTranslator(&translator);
//        translator.load(":/trans/Photos_en_GB.qm");
//        ui->retranslateUi(this);


    file = menuBar()->addMenu(tr("&File"));

    openAction = new QAction(tr("Open Folder..."), this);
    openAction->setObjectName("opennn");
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing folder"));
    connect(openAction, &QAction::triggered, this, &PhotoLibrary::on_pushButton_openF_clicked);

    file->addAction(openAction);
    ui->retranslateUi(this);

}

PhotoLibrary::~PhotoLibrary()
{
    delete ui;
}


void PhotoLibrary::LoadImages(const QString &path, QGraphicsScene *scene)
{
    int thumbnailSize = 100;
    QDirIterator it(path, QStringList() << "*.jpg" << "*.png" << "*.bmp" << "*.jpeg", QDir::Files, QDirIterator::Subdirectories);
    int x = 0;
    int y = 0;
    while (it.hasNext()) {
        QString filePath = it.next();
        QPixmap pixmap(filePath);
        if (!pixmap.isNull()) {
            QPixmap scaledPixmap = pixmap.scaled(thumbnailSize, thumbnailSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            graphItem* item = new graphItem(scaledPixmap, filePath);
            //PixmapWidget *widgetItem = new PixmapWidget(scaledPixmap);

//            QGraphicsProxyWidget* proxy = new QGraphicsProxyWidget();
//            proxy->setWidget(item);
            //QGraphicsGridLayout* layout = new QGraphicsGridLayout();
            //layout->addItem(item,x,y,1,1);

            item->setPos(x * thumbnailSize, y * thumbnailSize);
            item->setToolTip(filePath);
            item->setFlag(QGraphicsItem::ItemIsSelectable, true);
            scene->addItem(item);
            ++x;
            if (x >= 8) {
                x = 0;
                ++y;
            }
//            connect(&item, &QGraphicsPixmapItem::isSelected, this, &PhotoLibrary::zoom);
        }
    }
}

void PhotoLibrary::zoom(QString filePath){
    QDialog dialog;
    dialog.setWindowTitle(filePath);
    //dialog.
    //dialog.exec();
}

void PhotoLibrary::on_pushButton_openF_clicked()
{
    QString currentPath = QFileDialog::getExistingDirectory(this, tr("Select Directory"), QDir::currentPath());
    if(currentPath == "")
    {
//        QMessageBox::critical(this, "Errorrorrorror", "$!@#$%^&*()(*&^%$#@#$%^&*");
        return;
    }

    QFileInfo fileinformation(currentPath);
    ui->label_curPath->setText(fileinformation.filePath());

    QGraphicsScene* scene = new QGraphicsScene(this);

    PhotoLibrary::LoadImages(currentPath, scene);
//    QGridLayout* layout = new QGridLayout();

    QGraphicsView* view = ui->graphicsView;
    view->setScene(scene);
//    view->setLayout(layout);

    view->setRenderHint(QPainter::Antialiasing);
    view->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);


}

void PhotoLibrary::retranslate()
{
    openAction->setText(tr("Open Folder..."));
    openAction->setStatusTip(tr("Open an existing folder"));
    file->setTitle(tr("File"));
}


void PhotoLibrary::on_Languages_clicked()
{
    static bool chinese = false;
    if (!chinese)
    {
        translator.load(":/trans/Photos_en_GB.qm");
    }
    else
    {
        translator.load("");
    }
    chinese = !chinese;
    ui->retranslateUi(this);
    retranslate();
}

void PhotoLibrary::on_pushButton_add_clicked()
{
    //DrawingWidget widget();

}
