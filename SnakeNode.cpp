#include <SFML/Graphics.hpp>

#include "SnakeNode.h"

using namespace sfSnake;

const sf::Color SnakeNode::color[4] = { sf::Color::Red, sf::Color::Blue, sf::Color(255,255,0), sf::Color::Green };

SnakeNode::SnakeNode(sf::Vector2f position, int col, double angle, bool head)
: position_(position), angle_(angle)
{
	texture.loadFromFile("imgs/snake.png");
	Cshape.setPosition(position_);
	Cshape.setRadius(SnakeNode::radius_);
	
	auto bound = Cshape.getLocalBounds();
	Cshape.setOrigin(bound.left + bound.width / 2, bound.top + bound.height / 2);

	Rshape.setPosition({position.x - SnakeNode::dx, position.y - SnakeNode::dy});
	bound = Rshape.getLocalBounds();
	Rshape.setOrigin(bound.left + bound.width / 2, bound.top + bound.height / 2);

	if(head)
	{
		
		Cshape.setTexture(&texture);
		auto bound = Cshape.getLocalBounds();
		Cshape.setOrigin(bound.left + bound.width / 2, bound.top + bound.height / 2);

		Rshape.setSize({0.01, 0.01});
		Rshape.setFillColor(sf::Color::White);

		return;
	}
	
	Cshape.setFillColor(color[col]);
	Cshape.setOutlineColor(sf::Color::White);
	Cshape.setOutlineThickness(-thickness_);
	
	Rshape.setSize({SnakeNode::width_, SnakeNode::height_});
	Rshape.setFillColor(color[3-col]);
}


void SnakeNode::setPosition(sf::Vector2f position, double angle)
{
	position_ = position;
	angle_ = angle;
	Cshape.setPosition(position_);
	Rshape.setPosition(position_);
}

sf::FloatRect SnakeNode::getBounds() const
{
	return Cshape.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::render(sf::RenderWindow& window, bool head = false)
{
	if(head)
	{
		Cshape.setRotation(angle_);
		Cshape.setTexture(&texture);
		window.draw(Cshape);
	}
	else
	{
		Cshape.setRotation(angle_);
		Rshape.setRotation(angle_);
		window.draw(Cshape);
	}
	
}