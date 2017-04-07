#include "Circle.h"

Circle::Circle()
{
	circle.setFillColor(sf::Color::Green);
	circle.setRadius(60);
	circle.setPosition(400, 400);
}

Circle::~Circle()
{
}
void Circle::draw(sf::RenderWindow *window)
{
	window->draw(circle);
}