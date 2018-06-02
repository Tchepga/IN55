#ifndef CIRCLE_H
#define CIRCLE_H

#ifdef WIN32
#include <GL/glew.h>

#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#endif


// Includes GLM

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Includes

#include "Shader.h"
#include <math.h>

using namespace glm;
// Classe Cube

class Circle
{
    public:
        Circle(float taille, std::string const vertexShader, std::string const fragmentShader);
        virtual ~Circle();
       void afficher(glm::mat4 &projection, glm::mat4 &modelview);


    protected:

    Shader m_shader;
    float m_vertices[108];
    float m_couleurs[108];
};

#endif // CIRCLE_H
