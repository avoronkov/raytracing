#include "doc.h"

#include <QColor>
#include <QFile>
#include <QIODevice>

#include "io/io.h"

#define MOUSE_ZOOM 20

namespace rt { namespace ctrl {

using rt::model::RenderSet;
using rt::model::Quality;
using rt::model::Point;
using rt::model::WireFrame;
using rt::model::Camera;
using rt::model::Matrix;

Doc::Doc():
    m_scene_loaded{false},
    m_wire_frame_loaded{false},
    m_rotate_x{Matrix::identity()},
    m_rotate_y{Matrix::identity()}
{

}

bool Doc::initRenderSet()
{
    render_set = RenderSet();
    render_set.setScrollSize(params.getWidth(), params.getHeight());
    return true;
}

void Doc::loadSceneFromFile(QString filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit warning(QString("Cannot load file: ") + filename);
        return;
    }

    bool no_warning = rt::io::loadSceneFile(&file, &m_scene);
    if (!no_warning) {
        emit warning(QString("Some primitives are incorrect"));
    }
    m_scene_loaded = true;
    m_wire_frame_start = m_scene.getWireFrame();
    m_wire_frame_loaded = true;

    // TODO load camera file
    initRenderSet();
    prepareWireFrame(render_set);

    emit changed();
    emit information(QString("Scene is loaded from ") + filename);
}

bool Doc::prepareWireFrame(const RenderSet & set)
{
    double xss = m_wire_frame_start.getOuterBoxMin(0);
    double xff = m_wire_frame_start.getOuterBoxMax(0);
    double yss = m_wire_frame_start.getOuterBoxMin(1);
    double yff = m_wire_frame_start.getOuterBoxMax(1);
    double zss = m_wire_frame_start.getOuterBoxMin(2);
    double zff = m_wire_frame_start.getOuterBoxMax(2);

    Point center((xss+xff)/2.0, (yss+yff)/2.0, (zss+zff)/2.0);
    Point ort_sizes(qAbs(xss-xff)/1.8, qAbs(yss-yff)/1.8, qAbs(yss-yff)/1.8);

    m_wire_frame_start += WireFrame::orts(center, ort_sizes);
    m_wire_frame_start += WireFrame::cube(xss, yss, zss, xff, yff, zff);

    params.flag_doc_opeded = true;
    params.flag_raster_modified = true;
    const QSize & scroll_size = set.scrollSize();
    params.setWidth(scroll_size.width());
    params.setHeight(scroll_size.height());

    params.d = (qAbs(xss-xff) + qAbs(yss-yff) + qAbs(yss-yff)) / MOUSE_ZOOM;

    // translating
    params.s_w = qAbs(xss-xff);
    params.s_h = ((double) params.s_w) * params.getHeight() / params.getWidth();
//	params.s_h = qAbs(yss-yff);


    params.z_near = 0.5 * params.s_w / params.TG_15;
    params.z_far = params.z_near + 1.5 * qAbs(zss-zff);
    m_trans_to_center.createTranslate(- center.x(), - center.y(), - center.z());
    m_trans_from_center.createTranslate(center.x(), center.y(), center.z());

    const Camera & camera = set.camera();
    params.distance = camera.centerZ();

    m_trans_forward.createTranslate(0, 0, params.distance);
    m_trans_backwards.createTranslate(0, 0, -params.distance);

    const Matrix & rotate = camera.matrixRotate();

    m_proj.createMproj(params.s_w, params.s_h, params.z_near, params.z_far);
    m_pre_final = m_trans_forward * rotate * m_rotate_x * m_rotate_y * m_trans_to_center;
    m_final = m_proj * m_pre_final;

    m_wire_frame_finish = m_final * m_wire_frame_start;

    return true;
}

void Doc::rotateScene(double dx, double dy)
{
    m_rotate_x *= Matrix::rotateX(dx);
    m_rotate_y *= Matrix::rotateY(dy);
    prepareWireFrame(render_set);
    emit changed();
}

void Doc::moveSceneForward(double dz)
{


}

}}
