#include "acldisplay.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    acldisplay w;
    w.show();

    return a.exec();
}
