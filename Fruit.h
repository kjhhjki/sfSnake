#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>
#include <iostream>

namespace sfSnake
{
	class Fruit
	{
		private:
			sf::CircleShape shape_;
			sf::Texture texture;
			int col;
			static constexpr float Radius = 7.3;

		public:
			Fruit(sf::Vector2f position = sf::Vector2f(0, 0), int col = 0): col(col)
			{
				shape_.setPosition(position);
				shape_.setRadius(Fruit::Radius);
				texture.loadFromFile("imgs/" + std::to_string(col) + ".png");
				shape_.setTexture(&texture);
				// std::cout << col << ' ' << position.x << ' ' << position.y << '\n';
			}

			void render(sf::RenderWindow& window)
			{
				shape_.setTexture(&texture);
				window.draw(shape_);
			}

			sf::FloatRect getBounds() const { return shape_.getGlobalBounds(); }

			int getColor() const { return col; }
	};
}

#endif