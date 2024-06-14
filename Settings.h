#ifndef _SETTING_
#define _SETTING_

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "MenuScreen.h"

namespace sfSnake
{
    class SettingScreen : public Screen
    {
        private:
            sf::Font font_;
            sf::Text problems_;
            sf::Text answers_[8];
            int score_;
        public:
            SettingScreen()
            {
                font_.loadFromFile("Fonts/game_over.ttf");
                problems_.setFont(font_);
                problems_.setString(
                    "Background color\n\n\n\n"
                    "Grid lines\n\n\n\n"
                    "Grid lines's color\n\n\n\n"
                    "[Enter] Save");
                problems_.setColor(sf::Color::Red);

                answers_[0].setString("[Q]Black");
                answers_[1].setString("[W]White");
                answers_[2].setString("[E]Brown");
                answers_[3].setString("[A]Yes");
                answers_[4].setString("[S]No");
                answers_[5].setString("[Z]Black");
                answers_[6].setString("[X]White");
                answers_[7].setString("[C]Brown");
                answers_[0].setPosition(sf::Vector2f(0,60));
                answers_[1].setPosition(sf::Vector2f(210,60));
                answers_[2].setPosition(sf::Vector2f(420,60));
                answers_[3].setPosition(sf::Vector2f(0,180));
                answers_[4].setPosition(sf::Vector2f(210,180));
                answers_[5].setPosition(sf::Vector2f(0,300));
                answers_[6].setPosition(sf::Vector2f(210,300));
                answers_[7].setPosition(sf::Vector2f(420,300));

                for(auto &it: answers_) it.setFont(font_), it.setColor(sf::Color::Blue);
            }
            void handleInput(sf::RenderWindow& window) override
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                {
                    Game::Screen = std::make_shared<MenuScreen>();
                    int i = 0;
                    while(i < 3 && answers_[i].getColor() != sf::Color::Green) ++i;
                    switch (i)
                    {
                        case 0: Game::backgrondColor = sf::Color::Black;     break;
                        case 1: Game::backgrondColor = sf::Color::White;     break;
                        case 2: Game::backgrondColor = sf::Color(128,64,0);  break;
                    }
                    for(i = 3; i < 5 && answers_[i].getColor() != sf::Color::Green; ++i);
                    switch (i)
                    {
                        case 3: Game::grid = true;    break;
                        case 4: Game::grid = false;   return;
                    }
                    for(i = 5; i < 8 && answers_[i].getColor() != sf::Color::Green; ++i);
                    switch (i)
                    {
                        case 6: Game::lineColor = sf::Color(255,255,255,64);  break;
                        case 5: Game::lineColor = sf::Color(0,0,0,64);        break;
                        case 7: Game::lineColor = sf::Color(128,64,0,64);     break;
                    }
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                {
                    answers_[0].setColor(sf::Color::Green);
                    answers_[1].setColor(sf::Color::Blue);
                    answers_[2].setColor(sf::Color::Blue);
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    answers_[1].setColor(sf::Color::Green);
                    answers_[0].setColor(sf::Color::Blue);
                    answers_[2].setColor(sf::Color::Blue);
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                {
                    answers_[2].setColor(sf::Color::Green);
                    answers_[1].setColor(sf::Color::Blue);
                    answers_[0].setColor(sf::Color::Blue);
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                {
                    answers_[3].setColor(sf::Color::Green);
                    answers_[4].setColor(sf::Color::Blue);
                    for (int i = 5; i < 8; i++) answers_[i].setColor(sf::Color::Blue);
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    answers_[4].setColor(sf::Color::Green);
                    answers_[3].setColor(sf::Color::Blue);
                    for (int i = 5; i < 8; i++) answers_[i].setColor(sf::Color(192,192,192));
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                {
                    if(answers_[5].getColor() == sf::Color(192,192,192)) return;
                    answers_[5].setColor(sf::Color::Green);
                    answers_[6].setColor(sf::Color::Blue);
                    answers_[7].setColor(sf::Color::Blue);
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
                {
                    if(answers_[5].getColor() == sf::Color(192,192,192)) return;
                    answers_[6].setColor(sf::Color::Green);
                    answers_[5].setColor(sf::Color::Blue);
                    answers_[7].setColor(sf::Color::Blue);
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
                {
                    if(answers_[5].getColor() == sf::Color(192,192,192)) return;
                    answers_[7].setColor(sf::Color::Green);
                    answers_[6].setColor(sf::Color::Blue);
                    answers_[5].setColor(sf::Color::Blue);
                }
            }
            void update(sf::Time delta) override {}
            void render(sf::RenderWindow& window) override
            {
                window.draw(problems_);
                for(auto &it: answers_)
                    window.draw(it);
            }
    };
}

#endif