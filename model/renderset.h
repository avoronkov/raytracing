#ifndef RENDERSET_H
#define RENDERSET_H

#include "model/camera.h"

#include <QColor>
#include <QSize>

namespace rt { namespace model {

enum class Quality { ROUGH = 0, NORMAL = 1, FINE = 2 };

class RenderSet
{
    Camera m_camera;
    QSize m_scroll_size;
    QColor m_background;
    double m_gamma;
    int m_tree;
    Quality m_quality;
public:
    RenderSet(): m_gamma{1.0}, m_tree{3} {}
    RenderSet(const RenderSet &) = default;
    ~RenderSet() = default;

    RenderSet& operator=(const RenderSet&) = default;

    void setCamera(const Camera & c) { m_camera = c; }
    void setScrollSize(int width, int height) { setScrollSize(QSize(width, height)); }
    void setScrollSize(const QSize & size) { m_scroll_size = size; }
    void setBackground(const QColor & c) { m_background = c; }
    void setGamma(const double & gamma) { m_gamma = gamma; }
    void setTreeDepth(int depth) { m_tree = depth; }
    void setQuality(Quality q) { m_quality = q; }

    const Camera & camera() const { return m_camera; }
    const QSize & scrollSize() const { return m_scroll_size; }
    const QColor & background() const { return m_background; }
    const double & gamma() const { return m_gamma; }
    int treeDepth() const { return m_tree; }
    Quality quality() const { return m_quality; }
};

}}

#endif // RENDERSET_H
