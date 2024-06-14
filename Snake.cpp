#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include <cmath>
#include <random>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;

std::random_device rd;
std::mt19937 gen(rd());

Snake::Snake() : direction_{0, -1}, hitSelf_(false)
{
	initNodes();
	score = InitialSize;

	pickupBuffer_.loadFromFile("Sounds/pickup.wav");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);
}

void Snake::initNodes()
{
	static std::uniform_int_distribution<int> distrib(0, 3);
	nodes_.push_back(SnakeNode({ Game::Width / 2 - SnakeNode::radius_, Game::Height / 2 - SnakeNode::radius_}, 0, 0, true));
	for (int i = 1; i < Snake::InitialSize; ++i)
		nodes_.push_back(SnakeNode({ Game::Width / 2 - SnakeNode::radius_, Game::Height / 2 + ((2 * i - 1) * SnakeNode::radius_)}, distrib(gen)));
}

void Snake::handleInput(const sf::RenderWindow &window)
{
	Direction direction(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		direction = {0, -1};
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		direction = {0, 1};
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		direction = {-1, 0};
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		direction = {1, 0};
	else if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		auto [hX, hY] = nodes_[0].getPosition(); auto [gX, gY] = sf::Mouse::getPosition(window);
		if(gY < 0 || gY > Game::Height || gX < 0 || gX > Game::Width) return;
		double d = std::sqrt((gX - hX) * (gX - hX) + (gY - hY) * (gY - hY));
		direction = { (gX - hX) / d, (gY - hY) / d };
	}
	if(direction.x == 0 && direction.y == 0) return;
	if(direction.x * direction_.x + direction.y * direction_.y >= -0.5)
		direction_ = direction;
}

void Snake::update(sf::Time delta)
{
	move();
	checkEdgeCollisions();
	checkSelfCollisions();
}

int Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(nodes_[0].getBounds()))
		{
			// std::cout << "Collision detected" << std::endl;
			pickupSound_.play();
			int col = it->getColor();
			// std::cout << col << " Grows needed" << std::endl;
			for(int i = 0; i < col; ++i) grow(); //, std::cout << "Snake grown" << std::endl;
			++score;
			// std::cout << "Score: " << score << std::endl;
			fruits.erase(it);
			// std::cout << "Fruit erased" << std::endl;
			return col;
		}
	}
	return 6;
}

void Snake::grow()
{
	static std::uniform_int_distribution<int> distrib(0, 3);
	nodes_.push_back(SnakeNode(nodes_.back().getPosition(), distrib(gen), nodes_.back().getAngle()));
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

void Snake::checkSelfCollisions()
{
	SnakeNode& headNode = nodes_[0];

	for (decltype(nodes_.size()) i = 3; i < nodes_.size(); ++i)
	{
		if (headNode.getBounds().intersects(nodes_[i].getBounds()))
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
			break;
		}
	}
}

void Snake::checkEdgeCollisions()
{
	SnakeNode& headNode = nodes_[0];

	if (headNode.getPosition().x <= 0)
		headNode.setPosition(Game::Width, headNode.getPosition().y);
	else if (headNode.getPosition().x >= Game::Width)
		headNode.setPosition(0, headNode.getPosition().y);
	else if (headNode.getPosition().y <= 0)
		headNode.setPosition(headNode.getPosition().x, Game::Height);
	else if (headNode.getPosition().y >= Game::Height)
		headNode.setPosition(headNode.getPosition().x, 0);
}

const double Pi = std::acos(-1);

void Snake::move()
{
	for(decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
		nodes_[i].setPosition(nodes_[i-1].getPosition(), nodes_[i-1].getAngle());

	double angle;
	if(direction_.y == 0) angle = direction_.x < 0? 90: -90;
	else angle = std::atan(-direction_.x / direction_.y) * 180 / Pi + 180 * (direction_.y >= 0);
	nodes_[0].move(2 * SnakeNode::radius_ * direction_.x, 2 * SnakeNode::radius_ * direction_.y, angle);
}

void Snake::render(sf::RenderWindow& window)
{
	for(decltype(nodes_.size()) i = 0; i < nodes_.size(); ++i)
		nodes_[i].render(window, !i);
}