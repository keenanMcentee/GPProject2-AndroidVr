#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <math.h>
#include <jni.h>
#include <android/native_activity.h>
#include <SFML/Window/GlResource.hpp>
// Since we want to get the native activity from SFML, we'll have to use an
// extra header here:
#include <SFML/System/NativeActivity.hpp>

#include "Cube.h"
class Game
{
public:
	Game();
	~Game();
	void initialise();
	void processEvents();
	void run();
	void update();
	void draw();

private:
	
	sf::RenderWindow window;
	sf::Texture texture;
	sf::Sprite image;
	sf::Text text;
	sf::Font font;
	sf::View view;
	sf::Music music;
};
