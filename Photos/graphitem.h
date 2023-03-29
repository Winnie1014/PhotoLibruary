#ifndef GRAPHITEM_H
#define GRAPHITEM_H
#include <QGraphicsPixmapItem>
#include <QPixmap>

class graphItem : public QGraphicsPixmapItem
{
public:
    graphItem(const QPixmap &pixmap, QString path);


protected:

    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
private:
    QString         m_path;
    QImage qimage;
};

#endif // GRAPHITEM_H
