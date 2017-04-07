#include <vector>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Circle.h"
#include <SFML/OpenGL.hpp>

int main(int argc, char *argv[])
{
    // Create window
    sf::ContextSettings settings(24, 8, 0, 1, 1);
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "", sf::Style::Default, settings);
    // Angle of rotation
    double angle = 0;

    // Size of cube
    const GLfloat size = 0.1;

    // GL parameters
    const double near = 0.02;
    const double far = 3000;
    Circle a;
    // Init faces array
    // Faces : Left and right
    std::vector<GLfloat> face1 {

        size,  size, -size,
        -size,  size, -size,
        -size,  size,  size,

        size,  size, -size,
        -size,  size,  size,
        size,  size,  size,

        size, -size, -size,
        -size, -size,  size,
        -size, -size, -size,

        size, -size, -size,
        size, -size,  size,
        -size, -size,  size,


    };

    // Faces : Top and bottom
    std::vector<GLfloat> face2 {

        size, -size,  size,
        size,  size,  size,
        -size,  size,  size,

        size, -size,  size,
        -size,  size,  size,
        -size, -size,  size,

        size, -size, -size,
        -size,  size, -size,
        size,  size, -size,

        size, -size, -size,
        -size, -size, -size,
        -size,  size, -size,

    };

    // Faces Background and foreground
    std::vector<GLfloat> face3 {

        size, -size, -size,
        size,  size, -size,
        size,  size,  size,

        size, -size, -size,
        size,  size,  size,
        size, -size,  size,

        -size, -size, -size,
        -size,  size,  size,
        -size,  size, -size,

        -size, -size, -size,
        -size, -size,  size,
        -size,  size,  size,

    };

    // Init OpenGL
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustumf(-0.5 * near, 0.5 * near, 0.5 * ((double) 1920 / 1080) * near,  - 0.5 * ((double) 1920 / 1080) * near, near, far);
    glScalef(1,1,-1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();

    glMatrixMode(GL_MODELVIEW);

    // Enable GL_DEPTH_TEST : doesn't seem to work
    glEnable(GL_DEPTH_TEST);


	/*Enable back face culling*/
glEnable(GL_CULL_FACE);
glCullFace(GL_BACK);
glFrontFace(GL_CCW);
/* Depth buffer setup */
glClearDepthf( 1.0f );
/* Enables Depth Testing */
glEnable( GL_DEPTH_TEST );
/* The Type Of Depth Test To Do */
glDepthFunc( GL_LEQUAL );
    while (window.isOpen())
    {
        // By enable GL_DEPTH_TEST at each frame, the z-buffer works correctly
        // glEnable(GL_DEPTH_TEST);

        sf::Event event;

        while (window.pollEvent(event))
        {

            switch (event.type) {

                case sf::Event::Resized:

                    glMatrixMode(GL_PROJECTION);
                    glLoadIdentity();

                    glFrustumf(
                        -0.5 * near,
                        0.5 * near,
                        0.5 * ((double) event.size.height / event.size.width) * near,
                        - 0.5 * ((double) event.size.height / event.size.width) * near,
                        near,
                        far
                    );

                    glScalef(1,1,-1);

                    break;

            }

        }

        window.clear(sf::Color::Black);

        // Clear OpenGL context
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Increase angle to rotate the cube
        angle++;

        // Get out of the cube and apply rotation
        glTranslatef(0,0,1);
        glRotatef(angle, 1, 0, 0);
        glRotatef(angle, 0, 1, 0);

        glEnableClientState(GL_VERTEX_ARRAY);

        // Face1
        glColor4f(1.0,0.0,0.0,1.0);
        glVertexPointer(3, GL_FLOAT, 0, &face1[0]);
        glDrawArrays(GL_TRIANGLES, 0, face1.size() / 3);

        // Face2
        glColor4f(0.0,1.0,0.0,1.0);
        glVertexPointer(3, GL_FLOAT, 0, &face2[0]);
        glDrawArrays(GL_TRIANGLES, 0, face2.size() / 3);

        // Face3
        glColor4f(0.0,0.0,1.0,1.0);
        glVertexPointer(3, GL_FLOAT, 0, &face3[0]);
        glDrawArrays(GL_TRIANGLES, 0, face3.size() / 3);

        glDisableClientState(GL_VERTEX_ARRAY);

        glFlush();
        window.display();
    }

}
