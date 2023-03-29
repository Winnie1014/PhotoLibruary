#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QPainter>
#include <QMouseEvent>
#include <QRect>
#include <QPixmap>
#include <QToolBar>
#include <QAction>
#include <QLayout>
#include <QLabel>
#include <QTransform>


class DrawingWidget : public QDialog
{
    Q_OBJECT
public:
    explicit DrawingWidget(const QString& Ipath,QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void setCircleMode();
    void setLineMode();
    void setRectMode();
    void setNoneMode();

private:
    QPixmap m_image;
    QPixmap z_image;
    QImage image;
    QPoint m_startPoint;
    QPoint m_endPoint;
    bool m_isDrawing = false;
    QList<QRect> m_rectangles;
    QList<QLine> m_lines;
    QList<QRect> m_circles;
    QPainter painter;
    //QLabel piclable;
    QWidget *widd;
    enum Shape {Rectangle, Line, Circle, None};
    Shape m_currShape = None;

    qreal ratio;

    QTransform m_transform;
    void updatePixmap();

signals:

};

#endif // DRAWINGWIDGET_H
