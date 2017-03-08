#ifndef DOC_H
#define DOC_H

#include "model/scene.h"
#include "model/renderset.h"
#include "model/color.h"
#include "ctrl/params.h"

#include <QObject>

namespace rt { namespace ctrl {

class Doc : public QObject
{
    Q_OBJECT

    bool m_scene_loaded;
    bool m_wire_frame_loaded;

    rt::model::Scene m_scene;
    rt::model::Matrix m_trans_forward; // перемещение назад по оси Z
    rt::model::Matrix m_trans_backwards; // перемещение вперед по оси Z
    rt::model::Matrix m_trans_to_center; // перемещение центра бокса в начало координат
    rt::model::Matrix m_trans_from_center; // перемещение центра бокса в первоначальную позицию
//  Matrix m_scale;
    rt::model::Matrix m_rotate_x;
    rt::model::Matrix m_rotate_y;
    rt::model::Matrix m_final;
    rt::model::Matrix m_pre_final;
    rt::model::Matrix m_proj;

    // Attributes

public:
    Params params;
private:
    rt::model::RenderSet render_set;
    rt::model::WireFrame m_wire_frame_start; // первоначальное состояние сцены
    rt::model::WireFrame m_wire_frame_finish; // финальное состояние сцены

    rt::model::Eye m_render_eye; // "глаз" рендеринга
    // TODO Image m_render_image; // результат рендеринга
    // TODO Image m_render_pre_image;
public:
    Doc();
    ~Doc() = default;

public:
    bool prepareWireFrame(const rt::model::RenderSet & set);
    bool initRenderSet();

    void prepareRendering();
    void render();
    rt::model::Color renderRay(const rt::model::Ray &, int depth, double * distance_out);

    void moveZoom(int gradation);

    const rt::model::WireFrame & getFinalSceneWireframe() const { return m_wire_frame_finish; }

public slots:
    void loadSceneFromFile(QString filename);

signals:
    void changed();

    void warning(QString);
    void information(QString);
    void error(QString);
};

}}

#endif // DOC_H
