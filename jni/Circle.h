#include <SFML/Graphics.hpp>

class Circle
{
public:
	Circle();
	~Circle();
	sf::CircleShape circle;
	void draw(sf::RenderWindow* window);
private:

};
