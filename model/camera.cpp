#include "camera.h"

#include <QDebug>

namespace rt { namespace model {

Camera::Camera(): Camera{0, Matrix::identity()}
{

}

Camera::Camera(const double & z, const Matrix & rotate):
    m_center_z(z), m_rotate(rotate)
{
}

void Camera::setCenterZ(const double & value)
{
    m_center_z = value;
}
void Camera::setMatrixRotate(const Matrix & rotate)
{
    m_rotate = rotate;
}

const double & Camera::centerZ() const
{
    return m_center_z;
}
const Matrix & Camera::matrixRotate() const
{
    return m_rotate;
}

}}
