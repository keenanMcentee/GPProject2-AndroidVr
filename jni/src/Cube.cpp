#include <vector>
#include <cmath>

#include <SFML/Window/Touch.hpp>
#include <SFML/OpenGL.hpp>

#include "sft/VectorFunctions.hpp"
#include "Cube.hpp"

Cube::Cube(float size) :
    size{size},
    angle{},
    speed{},
    V{0,0,1},

    face1 {

        1,  1, -1,
        -1,  1, -1,
        -1,  1,  1,

        1,  1, -1,
        -1,  1,  1,
        1,  1,  1,

        1, -1, -1,
        -1, -1,  1,
        -1, -1, -1,

        1, -1, -1,
        1, -1,  1,
        -1, -1,  1,

    },

    face2{

        1, -1,  1,
        1,  1,  1,
        -1,  1,  1,

        1, -1,  1,
        -1,  1,  1,
        -1, -1,  1,

        1, -1, -1,
        -1,  1, -1,
        1,  1, -1,

        1, -1, -1,
        -1, -1, -1,
        -1,  1, -1,

    },

    face3 {

        1, -1, -1,
        1,  1, -1,
        1,  1,  1,

        1, -1, -1,
        1,  1,  1,
        1, -1,  1,

        -1, -1, -1,
        -1,  1,  1,
        -1,  1, -1,

        -1, -1, -1,
        -1, -1,  1,
        -1,  1,  1,

    }
		

{

}

void Cube::draw() const
{
    glPushMatrix();

	glRotatef(rotationAngle, 0, 1, 1);
		
    glScalef(size, size, size);

    glColor4f(1.0,1.0,1.0,1.0);

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

    glPopMatrix();

}

void Cube::update(float time)
{
rotationAngle += 0.5f;
if (rotationAngle <= 360)
		{
			rotationAngle -= 360;
		}
}
