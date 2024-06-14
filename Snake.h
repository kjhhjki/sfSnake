#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "SnakeNode.h"
#include "Fruit.h"

namespace sfSnake
{
	struct Direction
	{
		double x, y;
		Direction(double x, double y): x(x), y(y) {}
	};

	class Snake
	{
		private:

			sf::Vector2f position_;
			Direction direction_;

			sf::SoundBuffer pickupBuffer_;
			sf::Sound pickupSound_;

			sf::SoundBuffer dieBuffer_;
			sf::Sound dieSound_;

			std::vector<SnakeNode> nodes_;

			static const int InitialSize;
			unsigned score = 0;
			bool hitSelf_;

			void move();
			void grow();
			void checkEdgeCollisions();
			void checkSelfCollisions();
			void initNodes();
			
		public:
			Snake();

			void handleInput(const sf::RenderWindow &);
			void update(sf::Time delta);
			void render(sf::RenderWindow &window);

			int checkFruitCollisions(std::vector<Fruit>& fruits);

			bool hitSelf() const;

			unsigned getScore() const { return score; }
			unsigned getSize() const;
	};
}

#endif