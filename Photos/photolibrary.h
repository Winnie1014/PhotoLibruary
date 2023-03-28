#ifndef PHOTOLIBRARY_H
#define PHOTOLIBRARY_H
#include <QHBoxLayout>
#include <QMainWindow>
#include <QAction>
#include <QTranslator>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include "graphitem.h"
QT_BEGIN_NAMESPACE
namespace Ui { class PhotoLibrary; }
QT_END_NAMESPACE

class PhotoLibrary : public QMainWindow
{
    Q_OBJECT

public:
    PhotoLibrary(QWidget *parent = nullptr);
    ~PhotoLibrary();

private slots:
    void on_pushButton_openF_clicked();

    void on_Languages_clicked();

    void zoom(QString path);

    void on_pushButton_add_clicked();

private:
    void open();
    void retranslate();

    QMenu *file;
    QAction *openAction;
    Ui::PhotoLibrary *ui;

    QTranslator translator;

    QHBoxLayout* layout;

    void LoadImages(const QString &path, QGraphicsScene *scenes);

};


class PixmapWidget : public QGraphicsWidget {
public:
    PixmapWidget(const QPixmap &pixmap, QGraphicsItem *parent = nullptr)
        : QGraphicsWidget(parent), m_pixmapItem(new QGraphicsPixmapItem(pixmap, this)){
    }
protected:
    QGraphicsPixmapItem *m_pixmapItem;
};

#endif // PHOTOLIBRARY_H
