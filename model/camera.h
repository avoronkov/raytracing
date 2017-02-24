#ifndef CAMERA_H
#define CAMERA_H

#include "model/matrix.h"

namespace rt { namespace model {

class Camera
{
    double m_center_z;
    Matrix m_rotate;
public:
    Camera();
    Camera(const Camera &) = default;
    Camera(const double & z, const Matrix & rotate);
    ~Camera(void) = default;
    Camera & operator=(const Camera &) = default;

    void setCenterZ(const double &);
    void setMatrixRotate(const Matrix &);

    const double & centerZ()const;
    const Matrix & matrixRotate() const;
};

}}

#endif // CAMERA_H
