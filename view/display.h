#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include <QSize>
#include <QPaintEvent>

#include "model/wireframe.h"
#include "ctrl/doc.h"

namespace rt { namespace view {

class Display : public QWidget
{
    Q_OBJECT
private:
    rt::ctrl::Doc * doc;

    QSize view_port;
    QSize raster_size;
    const int offset;


public:
    explicit Display(QWidget *parent = 0);

    void setDocument(rt::ctrl::Doc *);

    virtual void paintEvent(QPaintEvent *) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
signals:

public slots:

private:
    void drawArena(const rt::model::WireFrame &, bool colorful=false);
    void drawSegment(const rt::model::Segment &, bool colorful=false);
    void drawBorder();

    QColor colorByDistance(double z);
    bool clipSegment(const rt::model::Segment & src, rt::model::Segment * dest);
};

}}

#endif // DISPLAY_H
