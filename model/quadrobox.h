#ifndef QUADROBOX_H
#define QUADROBOX_H

#include "model/primitive.h"
#include "model/box.h"
#include "model/quadric.h"

namespace rt { namespace model {

class QuadroBox : public Primitive
{
    Box m_box;
    Quadric m_quadric;
public:
    QuadroBox() = default;
    QuadroBox(const Quadric & q, const Box & b);
    QuadroBox(const QuadroBox &) = default;
    ~QuadroBox() = default;
    QuadroBox& operator=(const QuadroBox &) = default;

    enum PrimitiveType getType() const override {return PrimitiveType::QDR;}
    WireFrame getWireFrame() const override;
    double getMax(int coord) const override;
    double getMin(int coord) const override;
    bool isCorrect() const override;

    virtual bool calculateIntersection() override;
    virtual bool calculateNormal() override;
};

}}

#endif // QUADROBOX_H
