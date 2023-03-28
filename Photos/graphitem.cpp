#include "graphitem.h"
#include <QDebug>
#include <QLabel>

#include <QHBoxLayout>
#include <QDialog>
#include <QPixmap>
#include "drawingwidget.h"

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
   // widget.resize(1536, 864);
    widget.exec();
}
