#include "photolibrary.h"
#include "drawingwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PhotoLibrary w;
//    DrawingWidget widget;
//    widget.show();
    w.show();
    return a.exec();
}
