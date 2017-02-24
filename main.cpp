#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#include "model/point.h"
#include "model/segment.h"
#include "model/ray.h"
#include "model/color.h"
#include "model/wireframe.h"
#include "model/light.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    rt::model::Point s;
    rt::model::Point f(1.0, 1.0, 2.0);
    rt::model::Segment(s, f);

    rt::model::Ray r(s, f);
    rt::model::Color c;
    rt::model::WireFrame wf;
    rt::model::Light l;

    MainWindow w;
    w.show();

    return a.exec();
}
