#include "Game.h"

Game::Game() : window(sf::VideoMode::getDesktopMode(),
	"Introduction to OpenGL Texturing",
	sf::Style::Default,
	sf::ContextSettings(24,2,0,1,1))
{
}

Game::~Game()
{
}
void Game::initialise()
{
	//glClearColor(0.0f,0.0f,0.0f,1.0f);
	texture.loadFromFile("image.png");
	image.setTexture(texture);
	image.setPosition(0, 0);
	image.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);


	music.openFromFile("canary.wav");

	font.loadFromFile("sansation.ttf");

	text.setFont(font);
	text.setCharacterSize(64);
	text.setPosition(10, 100);

	music.play();
	view = window.getDefaultView();

}
void Game::run()
{
	initialise();

	while (window.isOpen())
	{
		processEvents();
		update();
		draw();
	}
}
void Game::processEvents()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::Resized:
			view.setSize(event.size.width, event.size.height);
			view.setCenter(event.size.width / 2, event.size.height / 2);
			window.setView(view);
			break;
		case sf::Event::TouchBegan:
			if (event.touch.finger == 0)
			{
				image.setPosition(event.touch.x, event.touch.y);
#if defined(USE_JNI)
				vibrate(sf::milliseconds(10));
#endif
			}
			break;
		}
	}
}
void Game::update()
{
	text.setString("DepthBits: " + std::to_string(window.getSettings().depthBits));
}
void Game::draw()
{
	window.clear(sf::Color::Black);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//window.draw(image);
	window.draw(text);
	////a.draw(&window);
	window.display();
}
