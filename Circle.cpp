#include "Circle.h"

struct Coordonnees
{
    double x;
    double y;
    double z;
};
struct Coordonnees vertices[50],couleur[50];

Circle::Circle(float taille, std::string const vertexShader, std::string const fragmentShader)
{
   // Chargement du shader
    m_shader.charger();

    // Division de la taille
    taille /= 2;
    int nbre =5;



    vertices[0].x = 0.0;
    vertices[0].y = 0.0;
    vertices[0].z = 0.0;

    for(int i(1);i<nbre;i++)
    {
        vertices[i].x = taille*cos(3.14*12*i/nbre);
        vertices[i].y = taille*sin(3.14*2*i/nbre);
        vertices[i].z = 0;

        couleur[i].x  = 1.0;
        couleur[i].y  = 0.0;
        couleur[i].z  = 1.0;
    }

}

Circle::~Circle()
{
    //dtor
}

void Circle::afficher(glm::mat4 &projection, glm::mat4 &modelview)
{
    // Activation du shader

    glUseProgram(m_shader.getProgramID());


        // Envoi des vertices

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
        glEnableVertexAttribArray(0);


        // Envoi de la couleur
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, couleur);
        glEnableVertexAttribArray(1);


        // Envoi des matrices
        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));


        // Rendu
        glDrawArrays(GL_TRIANGLE_FAN, 0, 18);


        // Désactivation des tableaux

        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);


    // Désactivation du shader

    glUseProgram(0);
}
