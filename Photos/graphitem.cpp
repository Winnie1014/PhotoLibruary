#include "graphitem.h"
#include "drawingwidget.h"

#include <QDebug>
#include <QLabel>

#include <QHBoxLayout>
#include <QDialog>
#include <QPixmap>

graphItem::graphItem(const QPixmap &pixmap, QString path): QGraphicsPixmapItem(pixmap), m_path(path)
{

}

void graphItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    //QPixmap pic(m_path);
    //QPixmap zoom = pic.scaled(1900, 1065, Qt::KeepAspectRatio, Qt::SmoothTransformation);



//    QHBoxLayout *lay = new QHBoxLayout;



    DrawingWidget widget(m_path);



//    QWidget *wid = new QWidget();
//    wid->setMinimumSize(200, 200);

//    lay->addWidget(wid);
//    lay->addWidget(&widget);



    //widget.setMaximumSize(192,108);

//    QHBoxLayout layout(&widget);
//    QLabel label;
//    label.setPixmap(zoom);
//    layout.addWidget(&label);
//    widget.adjustSize();

    qimage.load(m_path);
    qreal ratio = static_cast<qreal>(qimage.width()) / static_cast<qreal>(qimage.height());

    qDebug() << "qimagesize" << qimage.width() << qimage.height() << "qratio" <<ratio;

    widget.resize(static_cast<qreal>(864) * ratio, 864);
    qDebug() << "diawidth" << 864 * ratio;
//    widget.setMinimumSize(1536, 864);
    widget.exec();
}
