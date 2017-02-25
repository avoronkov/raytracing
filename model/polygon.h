#ifndef POLYGON_H
#define POLYGON_H

#include "model/point.h"
#include "model/primitive.h"

#include <QList>

namespace rt { namespace model {

class Polygon : public Primitive
{
    QList<Point> m_vertexes;

    double m_A;
    double m_B;
    double m_C;
    double m_D;

    bool is_correct; // flag if correct

public:
    Polygon();
    Polygon(const Polygon &) = default;
    ~Polygon() = default;
    Polygon& operator=(const Polygon&) = default;

    bool checkPolygon();
    void addPoint(const Point & point);
    void insertPoint(int idx, const Point & point);
    void insertPoint(int idx, const double& x, const double& y, const double& z);
    void setVertexCount(int count);
    int count()const;
    const Point & getVertex(int idx)const;

//  const Point &  getNormal() const;
    double getD() const { return m_D; }
    bool isInside(const Point &) const;

    bool isCorrect() const override;

    enum PrimitiveType getType() const override {return PrimitiveType::PLG;}
    WireFrame getWireFrame() const override;
    double getMax(int coord) const override;
    double getMin(int coord) const override;

    virtual bool calculateIntersection() override;
    virtual bool calculateNormal() override;
};

}}

#endif // POLYGON_H
