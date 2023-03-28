#include "drawingwidget.h"

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
    z_image = m_image.scaled(1919, 1116, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    mainLayout->addWidget(&piclable);


    setLayout(mainLayout);
    piclable.setPixmap(z_image);
    painter.setPen(QPen(Qt::black, 5));
    painter.setBrush(Qt::NoBrush);

}


void DrawingWidget::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton){
        m_startPoint = event->pos();
        m_isDrawing = true;
    }
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
    update();
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
}


void DrawingWidget::updatePixmap(){

    QPainter painter(&z_image);
//    painter.begin(&z_image);

    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::NoBrush);

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
   // painter.end();

//    piclable.setPixmap(z_image);
}



void DrawingWidget::resizeEvent(QResizeEvent *event){
    int width = event->size().width();
    int heigh = event->size().height();

    qDebug() << "Dialog size" << width << "x" << heigh;


    QDialog::resizeEvent(event);
}
