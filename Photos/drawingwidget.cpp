#include "drawingwidget.h"

#include "graphitem.h"

#include <QList>
#include <QDebug>
#include <QVBoxLayout>
#include <QStyle>

DrawingWidget::DrawingWidget(const QString& Ipath ,QWidget *parent) : QDialog(parent),  m_image(Ipath)
{
    QToolBar *bar = new QToolBar(this);

    qDebug() << Ipath.toStdString().c_str();

    //widd = new QWidget();
    //widd->setMinimumSize(200,200);
    //this->setStyleSheet(QString("border-image: url(%1);").arg("m_image"));
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QAction *Circle = new QAction(tr("Circle"), this);
    QAction *Line = new QAction(tr("Line"), this);
    QAction *Rect = new QAction(tr("Rectangle"), this);
    QAction *None = new QAction(tr("None"), this);

    bar->addAction(Circle);
    bar->addSeparator();
    bar->addAction(Line);
    bar->addSeparator();
    bar->addAction(Rect);
    bar->addSeparator();
    bar->addAction(None);

    mainLayout->setMenuBar(bar);

    connect(None, &QAction::triggered, this, &DrawingWidget::setNoneMode);
    connect(Circle, &QAction::triggered, this, &DrawingWidget::setCircleMode);
    connect(Line, &QAction::triggered, this, &DrawingWidget::setLineMode);
    connect(Rect, &QAction::triggered, this, &DrawingWidget::setRectMode);



    setMouseTracking(false);

    ratio = static_cast<qreal>(m_image.width()) / static_cast<qreal>(m_image.height());

    qDebug() << "m_image" <<m_image.width()<<m_image.height()<<"m_ratio"<<ratio;

    z_image = m_image.scaled(864*ratio, 864, Qt::KeepAspectRatio, Qt::SmoothTransformation);


    setLayout(mainLayout);


    image = z_image.toImage();


//    widd = this->layout()->;

//    QPaintDevice *device = centralWidget()->paintDevice();

    //mainLayout->addWidget(&piclable);
//    piclable.setPixmap(z_image);
//    painter.setPen(QPen(Qt::black, 5));
//    painter.setBrush(Qt::NoBrush);

}



void DrawingWidget::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton){
        m_startPoint = event->pos();
        m_isDrawing = true;
    }
    qDebug() <<"press";
}

void DrawingWidget::mouseMoveEvent(QMouseEvent *event) {
    if(m_isDrawing){
        m_endPoint = event->pos();
        update();
    }
}

void DrawingWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_endPoint = event->pos();
        m_isDrawing = false;

        switch (m_currShape) {
        case None:{

        }
            break;
        case Rectangle:{
            QRect rect(m_startPoint, m_endPoint);
            m_rectangles.push_back(rect);
        }
            break;
        case Line:{
            QLine line(m_startPoint, m_endPoint);
            m_lines.push_back(line);
        }
            break;
        case Circle:{
            QRect circle(m_startPoint, m_endPoint);
            m_circles.push_back(circle);
        }
            break;

        }
        update();

    }
}

void DrawingWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)

    QDialog::paintEvent(event);
    updatePixmap();

}

void DrawingWidget::setCircleMode(){
    m_currShape = Circle;
}

void DrawingWidget::setLineMode(){
    m_currShape = Line;
}

void DrawingWidget::setRectMode(){
    m_currShape = Rectangle;
}

void DrawingWidget::setNoneMode(){
    m_currShape = None;
    m_rectangles.clear();
    m_lines.clear();
    m_circles.clear();
    scaleX = 1;
    scaleY = 1;
    m_transform = QTransform::fromScale(1, 1);
    update();
}


void DrawingWidget::updatePixmap(){

    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), image);

    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::NoBrush);

    painter.setTransform(m_transform);


    for (const QRect &rect : m_rectangles) {
        painter.drawRect(rect);
    }
    for (const QLine &line : m_lines) {
        painter.drawLine(line);
    }

    for (const QRect &circle : m_circles) {
        painter.drawEllipse(circle);
    }

    if (m_isDrawing) {
        switch (m_currShape) {
        case None:{
        }
            break;
        case Rectangle:{
            QRect rect(m_startPoint, m_endPoint);
            painter.drawRect(rect);
        }
            break;
        case Line:{
            QLine line(m_startPoint, m_endPoint);
            painter.drawLine(line);
        }
            break;
        case Circle:{
            QRect circle(m_startPoint, m_endPoint);
            painter.drawEllipse(circle);
        }
            break;
        }
//        piclable.setPixmap(z_image);
        painter.end();

    }

}



void DrawingWidget::resizeEvent(QResizeEvent *event){
    int width = event->size().width();
    int heigh = event->size().height();

    qDebug() << "Dialog size" << width << "x" << heigh;
    z_image = m_image.scaled(width, heigh, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    image = z_image.toImage();

//    QSize newSize = event->size();
//    int newWidth = qMin(newSize.width(), static_cast<int>(newSize.height() * ratio));
//    int newHeight = qMin(newSize.height(), static_cast<int>(newSize.width() / ratio));


    scaleX = static_cast<qreal>(width) / (static_cast<qreal>(864) * ratio);
    scaleY = static_cast<qreal>(heigh) / 864;
    qDebug() << "imagesize" << z_image.width()<< z_image.height();

    qDebug() << "scalewidth" << static_cast<qreal>(width);
    qDebug() << "scalewidth2" << static_cast<qreal>(864) * ratio;
    qDebug() << "scaleX" << scaleX << "scaleY" << scaleY;
    m_transform = QTransform::fromScale(scaleX, scaleY);

    resize(static_cast<qreal>(event->size().height()) * ratio, event->size().height());

    QDialog::resizeEvent(event);
}
