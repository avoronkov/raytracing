#include "io.h"
#include "model/sphere.h"
#include "model/box.h"
#include "model/polygon.h"
#include "model/quadrobox.h"

#include <QString>
#include <QFile>
#include <QTextStream>

namespace rt { namespace io {

using rt::model::Primitive;
using rt::model::Point;
using rt::model::Sphere;
using rt::model::Box;
using rt::model::Polygon;
using rt::model::Quadric;
using rt::model::QuadroBox;

bool ok(const QTextStream & stream) {
    return stream.status() == QTextStream::Ok;
}

bool bad(const QTextStream & stream) {
    return !ok(stream);
}

bool uncommentString(QString * str)
{
    int com_index;
    if ((com_index = str->indexOf("//")) >= 0)
    {
        (*str) = str->left(com_index);
        if (str->size() == 0){
            return true;
        }
    }
    (*str) = str->trimmed();
    return true;
}


// private
bool readUString(QTextStream *in, QString *str)
{
    while(!in->atEnd()) {
        *str = in->readLine();
        if (!uncommentString(str)) return false;
        if (str->size() > 0) return true;
    }
    str->resize(0);
    return true;
}

bool readOptics(QTextStream *in, rt::model::Primitive * p)
{
    QString str;
    double kar, kag, kab; // ambient factor
    double kdr, kdg, kdb; // deffuse factor
    double ksr, ksg, ksb; // specular factor
    double power;
    double kt;
    double n1, n2;

    if (!readUString(in, &str)) return false;
    QTextStream(&str) >> kar >> kag >> kab >> kdr >> kdg >> kdb >> ksr >> ksg >> ksb >> power >> kt >> n1 >> n2;
    p->setOptics(kar, kag, kab, kdr, kdg, kdb, ksr, ksg, ksb, power, kt, n1, n2);
    return true;
}

bool readSphere(QTextStream *in, Sphere *s)
{
    QString buf;
    double x0, y0, z0;
    readUString(in, &buf);
    if (bad(QTextStream(&buf) >> x0 >> y0 >> z0)) {
        return false;
    }
    double r;
    readUString(in, &buf);
    if (bad(QTextStream(&buf) >> r)) return false;
    s->setCenter(x0, y0, z0);
    s->setRadius(r);
    return true;
}

bool readBox(QTextStream *in, Box * box)
{
    QString buf;
    double x_min, y_min, z_min;
    double x_max, y_max, z_max;
    readUString(in, &buf);
    if (bad(QTextStream(&buf) >> x_min >> y_min >> z_min)) return false;
    readUString(in, &buf);
    if (bad(QTextStream(&buf) >> x_max >> y_max >> z_max)) return false;
    box->setMin(x_min, y_min, z_min);
    box->setMax(x_max, y_max, z_max);
    return true;
}

bool readPolygon(QTextStream *in, Polygon * polygon)
{
    QString buf;
    int count = 0;
    readUString(in, &buf);
    if (bad(QTextStream(&buf) >> count)) return false;
    double x, y, z;
    for (int i=0; i<count; i++)
    {
        readUString(in, &buf);
        if (bad(QTextStream(&buf) >> x >> y >> z)) return false;
        polygon->addPoint(Point(x, y, z));
    }
    return polygon->checkPolygon();
}

bool readQuadroBox(QTextStream *in, QuadroBox * quadro_box)
{
    QString buf;
    double A, E, H, B, C, F, D, G, I, J;
    readUString(in, &buf);
    if (bad(QTextStream(&buf) >> A >> E >> H >> B >> C >> F >> D >> G >> I >> J)) {
        return false;
    }
    Quadric quadric = Quadric(A, E, H, B, C, F, D, G, I, J);

    double hx, hy, hz, lx, ly, lz;
    readUString(in, &buf);
    if (bad(QTextStream(&buf) >> hx >> hy >> hz)) {
        return false;
    }
    readUString(in, &buf);
    if (bad(QTextStream(&buf) >> lx >> ly >> lz)) {
        return false;
    }
    // normalize
    if (hx < lx){
        double tmp = lx;
        lx = hx;
        hx = tmp;
    }
    if (hy < ly){
        double tmp = ly;
        ly = hy;
        hy = tmp;
    }
    if (hz < lz){
        double tmp = lz;
        lz = hz;
        hz = tmp;
    }
    Box box = Box(lx, ly, lz, hx, hy, hz);
    (*quadro_box) = QuadroBox(quadric, box);
    return true;
}



bool loadSceneFile(QFile *in, rt::model::Scene *scene)
{
    QTextStream stream(in);
    return loadSceneStream(&stream, scene);
}

bool loadSceneStream(QTextStream *in, rt::model::Scene *scene)
{
    bool flag_no_warning = true;
    QString str;

    /// read scene header
    // read ambient light
    double ar, ag, ab;
    if (!readUString(in, &str)) return false;
    if (bad(QTextStream(&str) >> ar >> ag >> ab)) return false;
    scene->setAmbientColor(rt::model::Color(ar, ag, ab));

    // read lights
    // read number of lights
    int countLights;
    readUString(in, &str);
    if (bad(QTextStream(&str) >> countLights)) return false;
    for (int i=0; i<countLights; i++)
    {
        double lx, ly, lz, cr, cg, cb;
        if (!readUString(in, &str)) return false;
        if (bad(QTextStream(&str) >> lx >> ly >> lz >> cr >> cg >> cb)) return false;
        scene->addLight(rt::model::Light(Point(lx, ly, lz), rt::model::Color(cr, cg, cb)));
    }

    /// read scene sections
    while (true) {
        if (!readUString(in, &str)) return false;
        if (str.isEmpty()) break;

        QSharedPointer<Primitive> prim;

        if (str == "SPH") {
            auto s = QSharedPointer<Sphere>::create();
            readSphere(in, s.data());
            prim = qSharedPointerCast<Primitive>(s);
        } else if (str == "BOX") {
            auto b = QSharedPointer<Box>::create();
            readBox(in, b.data());
            prim = qSharedPointerCast<Primitive>(b);
        } else if (str == "PLG") {
            auto p = QSharedPointer<Polygon>::create();
            readPolygon(in, p.data());
            prim = qSharedPointerCast<Primitive>(p);
        } else if (str == "QDR") {
            auto q = QSharedPointer<QuadroBox>::create();
            readQuadroBox(in, q.data());
            prim = qSharedPointerCast<Primitive>(q);
        } else {
            qDebug() << "Not implemented yet: " << str;
            continue;
        }
        readOptics(in, prim.data());
        if (!prim->isCorrect()){
            flag_no_warning = false;
            continue;
        }
        scene->addPrimitive(prim);
    }

    return flag_no_warning;
}

}}
