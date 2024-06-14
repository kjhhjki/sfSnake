#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
	class SnakeNode
	{
		public:
			SnakeNode(sf::Vector2f position, int col, double angle = 0., bool head = false);

			void setPosition(sf::Vector2f position, double angle);
			void setPosition(float x, float y)
			{
				position_ = {x, y};
				setPosition(position_, angle_);
			}

			void move(float xOffset, float yOffset, double angle)
			{
				position_.x += xOffset;
				position_.y += yOffset;
				setPosition(position_, angle_);
			}

			void render(sf::RenderWindow& window, bool head);

			sf::Vector2f getPosition() const;
			sf::FloatRect getBounds() const;
			double getAngle() const { return angle_; }

			static constexpr float radius_ = 10.;
			static constexpr float width_ = 16., height_ = 7.5;
			static constexpr float dx = 2, dy = 5;
			static constexpr float thickness_ = 1.;

		private:
			sf::CircleShape Cshape;
			sf::RectangleShape Rshape;
			sf::Texture texture;
			static const sf::Color color[4];
			sf::Vector2f position_;
			double angle_;
	};
}

#endif