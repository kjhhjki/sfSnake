#include <SFML/Graphics.hpp>

#include <random>
#include <memory>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"

using namespace sfSnake;

std::random_device engine;
std::mt19937 random(engine());

GameScreen::GameScreen() : snake_()
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 3; j++)
			generateFruit(i);
	for (int i = 2; i < 5; i++)
		for (int j = 0; j < 6; j++)
			generateFruit(i);

	if(Game::grid) 
	{
		for (int i = 0; i < Game::Width; i += SnakeNode::radius_*2) 
		{
			lines.push_back(sf::Vertex(sf::Vector2f(i, 0), Game::lineColor));
			lines.push_back(sf::Vertex(sf::Vector2f(i, Game::Height), Game::lineColor));
		}
		for (int i = 0; i < Game::Height; i += SnakeNode::radius_*2) 
		{
			lines.push_back(sf::Vertex(sf::Vector2f(0, i), Game::lineColor));
			lines.push_back(sf::Vertex(sf::Vector2f(Game::Width, i), Game::lineColor));
		}
	}
}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
	snake_.update(delta);
	int cnt = snake_.checkFruitCollisions(fruit_);
	if(cnt < 5) generateFruit(cnt);

	if(snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
}

void GameScreen::render(sf::RenderWindow& window)
{
	if(Game::grid) window.draw(&lines[0], lines.size(), sf::Lines);
	snake_.render(window);
	for (auto &fruit : fruit_) fruit.render(window);
}

void GameScreen::generateFruit(int col)
{
	static std::uniform_int_distribution<int> xDistribution(SnakeNode::radius_*2, Game::Width - SnakeNode::radius_*2);
	static std::uniform_int_distribution<int> yDistribution(SnakeNode::radius_*2, Game::Height - SnakeNode::radius_*2);
	double x = 0, y = 0;
	while(1)
	{
		x = xDistribution(random);
		y = yDistribution(random);
		sf::CircleShape tmp(Fruit::Radius);
		for(auto &node: snake_.getNodes())
			if(tmp.getGlobalBounds().intersects(node.getBounds())) 
				continue;
		fruit_.push_back(Fruit(sf::Vector2f(xDistribution(random), yDistribution(random)), col));
		return;
	}
}

