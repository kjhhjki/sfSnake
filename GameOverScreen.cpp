#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

#include "Game.h"
#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Settings.h"

using namespace sfSnake;

GameOverScreen::GameOverScreen(std::size_t score) : score_(score)
{
	font_.loadFromFile("Fonts/game_over.ttf");
	text_.setFont(font_);
	text_.setString("Your score: " + std::to_string(score) + "!"
		"\n\n[SPACE] Retry"
		"\n\n[ESC] Quit"
		"\n\n[Tab] Settings");
	text_.setColor(sf::Color::Red);

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height / 2);
}

void GameOverScreen::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		Game::Screen = std::make_shared<GameScreen>();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
		Game::Screen = std::make_shared<SettingScreen>();
}

void GameOverScreen::update(sf::Time delta)
{

}

void GameOverScreen::render(sf::RenderWindow& window)
{
	window.draw(text_);
}