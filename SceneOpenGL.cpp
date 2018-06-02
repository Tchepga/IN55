#include "SceneOpenGL.h"


// Permet d'éviter la ré-écriture du namespace glm::

using namespace glm;


// Constructeur de Destucteur

SceneOpenGL::SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre) : m_titreFenetre(titreFenetre), m_largeurFenetre(largeurFenetre),
                                                                                             m_hauteurFenetre(hauteurFenetre), m_fenetre(0), m_contexteOpenGL(0),
                                                                                             m_input()
{

}


SceneOpenGL::~SceneOpenGL()
{
    SDL_GL_DeleteContext(m_contexteOpenGL);
    SDL_DestroyWindow(m_fenetre);
    SDL_Quit();
}


// Méthodes

bool SceneOpenGL::initialiserFenetre()
{
    // Initialisation de la SDL

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }


    // Version d'OpenGL

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


    // Double Buffer

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


    // Création de la fenêtre
    m_fenetre = SDL_CreateWindow(m_titreFenetre.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_largeurFenetre, m_hauteurFenetre, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(m_fenetre == 0)
    {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }


    // Création du contexte OpenGL

    m_contexteOpenGL = SDL_GL_CreateContext(m_fenetre);

    if(m_contexteOpenGL == 0)
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_fenetre);
        SDL_Quit();

        return false;
    }

    return true;
}


bool SceneOpenGL::initGL()
{
    #ifdef WIN32

        // On initialise GLEW

        GLenum initialisationGLEW( glewInit() );


        // Si l'initialisation a échoué :

        if(initialisationGLEW != GLEW_OK)
        {
            // On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)

            std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;


            // On quitte la SDL

            SDL_GL_DeleteContext(m_contexteOpenGL);
            SDL_DestroyWindow(m_fenetre);
            SDL_Quit();

            return false;
        }

    #endif


    // Activation du Depth Buffer

    glEnable(GL_DEPTH_TEST);


    // Tout s'est bien passé, on retourne true

    return true;
}


void SceneOpenGL::bouclePrincipale()
{
    // Variables

    unsigned int frameRate (1000 / 50);
    Uint32 debutBoucle(0), finBoucle(0), tempsEcoule(0);


    // Matrices

    mat4 projection;
    mat4 modelview;

    projection = perspective(70.0, (double) m_largeurFenetre / m_hauteurFenetre, 1.0, 100.0);
    modelview = mat4(1.0);


    // Vertices

    float vertices[] = {-10, 0, -10,   10, 0, -10,   10, 0, 10,    // Triangle 1
                        -10, 0, -10,   -10, 0, 10,   10, 0, 10};   // Triangle 2



    // Coordonnées de texture

    float coordTexture[] = {0, 0,   7, 0,   7, 7,     // Triangle 1
                            0, 0,   0, 7,   7, 7};    // Triangle 2


    // Texture

    Texture texture("../photorealistic/photorealistic_terra/terra1_1.jpg");
    texture.charger();


    // Shader

    Shader shaderTexture("Shaders/texture.vert", "Shaders/texture.frag");
    shaderTexture.charger();


    // Objet Caisse
   // Caisse caisse(2.0, "Shaders/texture.vert", "Shaders/texture.frag", "Textures/Caisse2.jpg");

    // Object cube
    //Cube cube(2.0, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag");
    //Cube cube1(2.0, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag");
    //Circle circle(2.0, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag");




    // Boucle principale

    while(!m_input.terminer())
    {
        // On définit le temps de début de boucle
        debutBoucle = SDL_GetTicks();


        // Gestion des évènements
        m_input.updateEvenements();
        if(m_input.getTouche(SDL_SCANCODE_ESCAPE))
           break;


        // Nettoyage de l'écran
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // Placement de la caméra
        modelview = lookAt(vec3(12, 12, 12), vec3(0, 0, 0), vec3(0, 1, 0));


        // Sauvegarde de la matrice modelview
        mat4 sauvegardeModelview = modelview;


        // Translation pour positionner le cube
        //modelview = translate(modelview, vec3(0, 1, 0));
        //modelview = scale(modelview,vec3(0.5,2.5,0.5));


        // Affichage du pied 1
        //cube.afficher(projection, modelview);
        // Affichage du pied 2
        /*modelview = sauvegardeModelview;
        modelview = translate(modelview, vec3(2, 1, 0));
        modelview = scale(modelview,vec3(0.5,2.5,0.5));*/

        //cube.afficher(projection, modelview);


       // Affichage du tronc
      /*  modelview = sauvegardeModelview;
        modelview = translate(modelview, vec3(0.5,5, 0));
        modelview = scale(modelview,vec3(1.5,2.5,1.5));

        cube.afficher(projection, modelview);

        // Affichage du tête
        modelview = sauvegardeModelview;
        modelview = translate(modelview, vec3(0.5,8,0));
        modelview = scale(modelview,vec3(0.7,0.7,0.7));

        cube.afficher(projection, modelview);

         // Affichage du bras 1
        modelview = sauvegardeModelview;
        modelview = translate(modelview, vec3(3,5,0));
        modelview = rotate(modelview, 40.f, vec3(0,0,1));
        modelview = scale(modelview,vec3(0.5,2,0.5));

        cube.afficher(projection, modelview);

         // Affichage du bras 2
        modelview = sauvegardeModelview;
        modelview = translate(modelview, vec3(-3,5,0));
        modelview = rotate(modelview,-40.f,vec3(0,0,1));
        modelview = scale(modelview,vec3(0.5,2,0.5));

        cube.afficher(projection, modelview);*/



        modelview = translate(modelview, vec3(1, 1, 1));
       // modelview = scale(modelview,vec3(2,1,1));

        //circle.afficher(projection,modelview);


         // Restauration de la matrice
         modelview = sauvegardeModelview;
        // Activation du shader
        glUseProgram(shaderTexture.getProgramID());


        // Envoi des vertices
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
        glEnableVertexAttribArray(0);


        // Envoi des coordonnées de texture
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, coordTexture);
        glEnableVertexAttribArray(2);


        // Envoi des matrices
        glUniformMatrix4fv(glGetUniformLocation(shaderTexture.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shaderTexture.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));


        // Verrouillage de la texture
        glBindTexture(GL_TEXTURE_2D, texture.getID());


        // Rendu
        glDrawArrays(GL_TRIANGLES, 0, 6);


        // Déverrouillage de la texture
        glBindTexture(GL_TEXTURE_2D, 0);


        // Désactivation des tableaux
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(0);


        // Désactivation du shader
        glUseProgram(0);


        // Actualisation de la fenêtre
        SDL_GL_SwapWindow(m_fenetre);


        // Calcul du temps écoulé
        finBoucle = SDL_GetTicks();
        tempsEcoule = finBoucle - debutBoucle;


        // Si nécessaire, on met en pause le programme
        if(tempsEcoule < frameRate)
            SDL_Delay(frameRate - tempsEcoule);
    }
}

