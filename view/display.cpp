#include "display.h"

#include <QPoint>
#include <QPainter>
#include <QtMath>
#include <QMessageBox>

namespace rt { namespace view {

using rt::model::Segment;
using rt::model::Point;

Display::Display(QWidget *parent):
    QWidget(parent),
    doc{nullptr},
    offset{10}
{

}

void Display::setDocument(rt::ctrl::Doc * d) {
    doc = d;
}

void Display::paintEvent(QPaintEvent *)
{
    if (!doc) return;


    if (doc->params.flag_raster_modified || true)
    {
        raster_size =  QSize(doc->params.scrollX(), doc->params.scrollY());
        // SetScrollSizes(MM_TEXT, raster_size);
        if (raster_size.width() > 0 && raster_size.height() > 0){
            int w = raster_size.width() - 2 * (offset + 1);
            w = w > 0 ? w : 0;
            int h = raster_size.height() - 2 * (offset + 1);
            h = h > 0 ? h : 0;
            view_port = QSize(w, h);
        }
        // delete memDC;
        // delete memBitmap;
        // memDC = new CDC();
        // memDC->CreateCompatibleDC(pDC);
        // memBitmap = new CBitmap();
        // memBitmap->DeleteObject();
        // memBitmap->CreateCompatibleBitmap (pDC,raster_size.cx,raster_size.cy);
        // memDC->SelectObject(memBitmap);

        // memDC->FillSolidRect(0, 0, raster_size.cx, raster_size.cy, pDC->GetBkColor());
        // pDC->BitBlt(0,0,rect.right,rect.bottom,memDC,0,0,SRCCOPY);
        doc->params.flag_raster_modified = false;
    }

    //memDC->FillSolidRect(0, 0, raster_size.cx, raster_size.cy, pDC->GetBkColor());
    if (doc->params.flag_doc_opeded)
    {
        if (doc->params.flag_render_in_process)
        {
            /* TODO
            CString str;
            str.Format("Render in progress...");
            memDC->TextOut(offset, offset, str);
            */
        }
        else if (!doc->params.flag_render_ready)
        {
            drawBorder();
            drawArena(doc->getFinalSceneWireframe(), doc->params.flag_colorful);
        }
        else
        {
            // show rendered picture TODO
            // COLORREF back = doc->render_set.background();
            // drawRenderedImage(memDC, doc->m_render_image, back);
        }
    }

    // pDC->BitBlt(scroll_pos.x,scroll_pos.y,rect.right,rect.bottom,memDC,
            // scroll_pos.x,scroll_pos.y,SRCCOPY);
    // drawWhiteSpace(pDC);
}

void Display::drawArena(const rt::model::WireFrame & arena, bool colorful)
{
    qInfo() << "drawArena size = " <<arena.content().length();
    for (const Segment & seg : arena.content()) {
        drawSegment(seg, colorful);
    }
}

void Display::drawSegment(const rt::model::Segment & segment, bool colorful)
{
    QPainter painter(this);
    Segment s1 = segment;
    if (s1.start().get(3) < 0 && s1.finish().get(3) < 0){
        return;
    }
    qInfo() << "drawSegment(" << s1 << ")";
    s1.normalizeW();
    qInfo() << "s1.normalizeW = " << s1;
    Segment s;
    if (! clipSegment(s1, &s) ) {
        return;
    }
    qInfo() << "clipSegment s1 " << s;
    // TODO initialize view_port
    int start_x = (int)((s.start().x() + 1.0) * view_port.width() / 2.0 + offset + 1.5);
//  start.y = (int)((s.start().y() + 1.0) * view_port.cy / 2.0 + offset + 1.5);
    int start_y = (int)(view_port.height() + offset - (s.start().y() + 1.0) * view_port.height() / 2.0 + 1.5);
    int finish_x = (int)((s.finish().x() + 1.0) * view_port.width() / 2.0 + offset + 1.5);
//  finish.y = (int)((s.finish().y() + 1.0) * view_port.cy / 2.0 + offset + 1.5);
    int finish_y = (int)(view_port.height() + offset - (s.finish().y() + 1.0) * view_port.height() / 2.0 + 1.5);

    QPoint start(start_x, start_y);
    QPoint finish(finish_x, finish_y);

    QColor c = segment.color();
    if (c == QColor(0, 0, 0) && colorful)
    {
        double dist = 0.5 *(s.start().z() + s.finish().z());
        c = colorByDistance(dist);
    }
    int w = segment.width();
    QPen pen(Qt::SolidLine);
    pen.setColor(c);
    pen.setWidth(w);
    painter.setPen(pen);
    qInfo() << "draw line [" << start << ", " << finish << "]";
    painter.drawLine(start, finish);
}

QColor Display::colorByDistance(double z)
{
    int r, g, b;
    Q_ASSERT(z >= 0 && z <=1);
    r = (z >= 0.5)?((int)(510 * (z - 0.5) +0.5)):0;
    g = (z <= 0.5)?((int)(510 * (0.5 - z) +0.5)):0;
    b = 255 - (int)(510 * qAbs(z - 0.5) + 0.5);
    r = (r < 0)?0:r;
    g = (g < 0)?0:g;
    b = (b < 0)?0:b;
    r = (r > 255)?255:r;
    g = (g > 255)?255:g;
    b = (b > 255)?255:b;
    return QColor(r, g, b);
}

bool Display::clipSegment(const Segment & src, Segment * dest)
{
    Segment res = src;
    double sx = res.start().x();
    double fx = res.finish().x();
    Point ptmp;
    Point vec;
    if (sx < -1 && fx < -1) return false;
    // clip right
    if ((sx + 1)*(fx + 1) < 0)
    {
        if (sx > -1)
        {
            vec = Point(res.finish().x() - res.start().x(), res.finish().y() - res.start().y(),
                res.finish().z() - res.start().z());
            double tau = (sx + 1) / (sx - fx);
            ptmp.setX(res.start().x() + tau * vec.x());
            ptmp.setY(res.start().y() + tau * vec.y());
            ptmp.setZ(res.start().z() + tau * vec.z());
            res.setFinish(ptmp);
        }
        else // fx > -1
        {
            vec = Point(- res.finish().x() + res.start().x(), - res.finish().y() + res.start().y(),
                - res.finish().z() + res.start().z());
            double tau = (fx + 1) / (fx - sx);
            ptmp.setX(res.finish().x() + tau * vec.x());
            ptmp.setY(res.finish().y() + tau * vec.y());
            ptmp.setZ(res.finish().z() + tau * vec.z());
            res.setStart(ptmp);
        }
    }
    sx = res.start().x();
    fx = res.finish().x();
    // clip left
    if (sx > 1 && fx > 1) return false;
    if ((sx - 1)*(fx - 1) < 0)
    {
        if (sx < 1)
        {
            vec = Point(res.finish().x() - res.start().x(), res.finish().y() - res.start().y(),
                res.finish().z() - res.start().z());
            double tau = (1 - sx) / (fx - sx);
            ptmp.setX(res.start().x() + tau * vec.x());
            ptmp.setY(res.start().y() + tau * vec.y());
            ptmp.setZ(res.start().z() + tau * vec.z());
            res.setFinish(ptmp);
        }
        else // fx < 1
        {
            vec = Point(- res.finish().x() + res.start().x(), - res.finish().y() + res.start().y(),
                - res.finish().z() + res.start().z());
            double tau = (1 - fx) / (sx - fx);
            ptmp.setX(res.finish().x() + tau * vec.x());
            ptmp.setY(res.finish().y() + tau * vec.y());
            ptmp.setZ(res.finish().z() + tau * vec.z());
            res.setStart(ptmp);
        }
    }
    double sy = res.start().y();
    double fy = res.finish().y();
    // clip top
    if (sy < -1 && fy < -1) return false;
    if ((sy + 1)*(fy + 1) < 0)
    {
        if (sy > -1)
        {
            vec = Point(res.finish().x() - res.start().x(), res.finish().y() - res.start().y(),
                res.finish().z() - res.start().z());
            double tau = (sy + 1) / (sy - fy);
            ptmp.setX(res.start().x() + tau * vec.x());
            ptmp.setY(res.start().y() + tau * vec.y());
            ptmp.setZ(res.start().z() + tau * vec.z());
            res.setFinish(ptmp);
        }
        else // fy > -1
        {
            vec = Point(- res.finish().x() + res.start().x(), - res.finish().y() + res.start().y(),
                - res.finish().z() + res.start().z());
            double tau = (fy + 1) / (fy - sy);
            ptmp.setX(res.finish().x() + tau * vec.x());
            ptmp.setY(res.finish().y() + tau * vec.y());
            ptmp.setZ(res.finish().z() + tau * vec.z());
            res.setStart(ptmp);
        }
    }
    sy = res.start().y();
    fy = res.finish().y();
    if (sy > 1 && fy > 1) return false;
    // clip bottom
    if ((sy - 1)*(fy - 1) < 0)
    {
        if (sy < 1)
        {
            vec = Point(res.finish().x() - res.start().x(), res.finish().y() - res.start().y(),
                res.finish().z() - res.start().z());
            double tau = (1 - sy) / (fy - sy);
            ptmp.setX(res.start().x() + tau * vec.x());
            ptmp.setY(res.start().y() + tau * vec.y());
            ptmp.setZ(res.start().z() + tau * vec.z());
            res.setFinish(ptmp);
        }
        else // fy < 1
        {
            vec = Point(- res.finish().x() + res.start().x(), - res.finish().y() + res.start().y(),
                - res.finish().z() + res.start().z());
            double tau = (1 - fy) / (sy - fy);
            ptmp.setX(res.finish().x() + tau * vec.x());
            ptmp.setY(res.finish().y() + tau * vec.y());
            ptmp.setZ(res.finish().z() + tau * vec.z());
            res.setStart(ptmp);
        }
    }
    double sz = res.start().z();
    double fz = res.finish().z();
    if (sz < 0 && fz < 0) return false;
    if ( sz * fz < 0)
    {
        if (sz > 0)
        {
            vec = Point(res.finish().x() - res.start().x(), res.finish().y() - res.start().y(),
                res.finish().z() - res.start().z());
            double tau = sz  / (sz - fz);
            ptmp.setX(res.start().x() + tau * vec.x());
            ptmp.setY(res.start().y() + tau * vec.y());
            ptmp.setZ(res.start().z() + tau * vec.z());
            res.setFinish(ptmp);
        }
        else // fz > 0
        {
            vec = Point(- res.finish().x() + res.start().x(), - res.finish().y() + res.start().y(),
                - res.finish().z() + res.start().z());
            double tau = fz / (fz - sz);
            ptmp.setX(res.finish().x() + tau * vec.x());
            ptmp.setY(res.finish().y() + tau * vec.y());
            ptmp.setZ(res.finish().z() + tau * vec.z());
            res.setStart(ptmp);
        }
    }
    sz = res.start().z();
    fz = res.finish().z();
    if (sz > 1 && fz > 1) return false;
    if ((sz - 1)*(fz - 1) < 0)
    {
        if (sz < 1)
        {
            vec = Point(res.finish().x() - res.start().x(), res.finish().y() - res.start().y(),
                res.finish().z() - res.start().z());
            double tau = (1 - sz) / (fz - sz);
            ptmp.setX(res.start().x() + tau * vec.x());
            ptmp.setY(res.start().y() + tau * vec.y());
            ptmp.setZ(res.start().z() + tau * vec.z());
            res.setFinish(ptmp);
        }
        else // fz < 1
        {
            vec = Point(- res.finish().x() + res.start().x(), - res.finish().y() + res.start().y(),
                - res.finish().z() + res.start().z());
            double tau = (1 - fz) / (sz - fz);
            ptmp.setX(res.finish().x() + tau * vec.x());
            ptmp.setY(res.finish().y() + tau * vec.y());
            ptmp.setZ(res.finish().z() + tau * vec.z());
            res.setStart(ptmp);
        }
    }
    *dest = res;
    return true;
}

void Display::drawBorder()
{
    QPainter painter(this);
    painter.setPen(Qt::blue);
    painter.drawRect(offset, offset, raster_size.width() - 2*offset, raster_size.height() - 2*offset);
}


}}
