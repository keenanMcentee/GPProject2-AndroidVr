#include <vector>
#include <algorithm>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window/Sensor.hpp>
#include <SFML/OpenGL.hpp>
#include "Cube.hpp"
#include "glm/glm/glm.hpp"
sf::Text a;
sf::Font b;
float startingRotation;
float rotationAngle;
float lookingAngle;
int main(int argc, char *argv[])
{
	sf::Sensor::setEnabled(sf::Sensor::Orientation,true);
	startingRotation = sf::Sensor::getValue(sf::Sensor::Orientation).x;
	b.loadFromFile("sansation.ttf");
	a.setFont(b);
	a.setString("Hi"); 
	a.setPosition(100, 100);
	a.setCharacterSize(50);

    sf::ContextSettings settings{24, 8, 0, 1, 1};
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);
    double near = 0.03;
    double far = 3000;

    sf::Vector2i lastTouch;

    Cube cube(0.2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();

    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    while (window.isOpen())
    {
        glEnable(GL_DEPTH_TEST);

        sf::Event event;

        while (window.pollEvent(event))
        {

            sf::Vector2i move;
            float aspect;
			
            switch (event.type) {

                case sf::Event::TouchBegan:

                    lastTouch.x = event.touch.x;
                    lastTouch.y = event.touch.y;
                    break;

                case sf::Event::TouchMoved:

                    break;

                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::LostFocus:
                    break;

                case sf::Event::GainedFocus:
                    break;

                case sf::Event::MouseLeft:
                    break;

                case sf::Event::MouseEntered:
                    break;


                case sf::Event::Resized:
                    glMatrixMode(GL_PROJECTION);
                    glLoadIdentity();

                    aspect =  (float) std::max(event.size.height, event.size.width) / std::min(event.size.height, event.size.width);

                    window.setSize(sf::Vector2u{event.size.height, event.size.width});
                    glFrustumf( -0.5 * near,0.5 * near,0.5 * (aspect) * near, - 0.5 * (aspect) * near, near, far);
					//glTranslatef(0,0.5f,0);
                    glScalef(1,1,-1);

                    break;

                case sf::Event::KeyPressed:

                    if (event.key.code == sf::Keyboard::Escape)
                        window.close();

                    break;

                default:
                    break;

            }

        }
		lookingAngle = -sf::Sensor::getValue(sf::Sensor::Orientation).x + startingRotation;
		
		if (lookingAngle < 0)
		{
			lookingAngle += 360;
		}
		else if (lookingAngle > 360)
		{
			lookingAngle -= 360;
		}
        // Update
        cube.update(20);
		rotationAngle += 0.5f;
        // Draw
        window.clear(sf::Color::Black);
		
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glMatrixMode(GL_MODELVIEW);

		
        glLoadIdentity();
		glRotatef(lookingAngle, 0, 1, 0);
		glTranslatef(0,0,2);
		glRotatef(rotationAngle, 0, 1, 1);
		if (rotationAngle <= 360)
		{
			rotationAngle -= 360;
		}
		glViewport(0, 0, window.getSize().y/2, window.getSize().x);

        cube.draw();
		glFlush();
		glViewport(window.getSize().y/2, 0, window.getSize().y/2, window.getSize().x);
        //glTranslatef(0,0,1);
        cube.draw();
        glFlush();
        window.display();
    }
}
