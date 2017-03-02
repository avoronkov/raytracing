#ifndef SCENE_H
#define SCENE_H

#include "model/primitive.h"
#include "model/light.h"

#include <QList>
#include <QSharedPointer>

namespace rt { namespace model {

class Scene
{
    Color m_ambient;    // рассеянный свет
    QList<Light> m_lights;  // источники света
    QList<QSharedPointer<Primitive>> m_prims; // примитивы
    double m_max_coords[3]; // координаты габаритного бокса сцены
    double m_min_coords[3];
public:
    Scene();
    Scene(const Scene &) = default;
    ~Scene() = default;
    Scene& operator=(const Scene&) = default;

    void setAmbientColor(const Color & color);
    void addLight(const Light & light);
    void addPrimitive(QSharedPointer<Primitive> p);
    void addPrimitive(Primitive* p);

    int countPrimitives() const; // количество примитивов
    int countLights() const; // количество источников света

    const Color & ambientColor() const;
    const Light & light(int i) const;
    QSharedPointer<Primitive> primitive(int i) const;

    WireFrame getWireFrame() const;

    double getMax(int coord) const;
    double getMin(int coord) const;

    bool intersect(const Ray & ray, Ray * reflecred, Ray * normal, Primitive ** pprim);

//  Color countTotalDiffuseLight(const Ray & normal, const Color & factor)const;
    Color countDiffuseLight(const Ray & normal, const Color & factor, int light_idx)const;
    Color countSpecularLight(const Ray & normal, Point to_eye, const Color & factor, int light_idx, double power)const;
    bool pointIsVisible(const Point & point, const Point & light)const;
    bool lightIsVisible(const Point & point, int light_idx)const;
};

}}

#endif // SCENE_H
