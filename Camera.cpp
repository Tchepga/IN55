#include "Camera.h"

Camera::Camera() : m_phi(0.0), m_theta(0.0), m_orientation(), m_axeVertical(0, 0, 1), m_deplacementLateral(), m_position(), m_pointCible()
{

}
Camera::Camera(glm::vec3 position, glm::vec3 pointCible, glm::vec3 axeVertical) : m_phi(0.0), m_theta(0.0), m_orientation(), m_axeVertical(axeVertical),
                                                                          m_deplacementLateral(), m_position(position), m_pointCible(pointCible)
{

}

Camera::~Camera()
{
    //dtor
}
