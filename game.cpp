#include "game.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <sstream>
#include <string>

Game::Game(){
  createColors();
  setParameters();
}

void Game::createColors(){
  array_colors.push_back(sf::Color::Magenta);
  array_colors.push_back(sf::Color(255, 105, 180)); //Hot pink
  array_colors.push_back(sf::Color(255, 140, 0)); //Dark orange
  array_colors.push_back(sf::Color(0, 255, 127)); //Spring green
  array_colors.push_back(sf::Color(210, 105, 30)); //Chocolate
  randColor()                                                   ;
}

float shift_coef = 13.0;

void Game::setParameters(){
  circle.setRadius(150);
  circle.setFillColor(sf::Color::White);
  circle.setPosition((width_ - circle.getRadius()*2) / 2, (height_ - circle.getRadius()*2) / 2); //centered
                                                                                         
  font.loadFromFile("fonts/Lilita.ttf");
  hero_score_text.setFillColor(getColor());
  hero_score_text.setFont(font);
  hero_score_text.setCharacterSize(120);
  hero_score_text.setPosition(circle.getPosition().x + circle.getRadius() - hero_score_text.getCharacterSize()/2 + shift_coef * 2, circle.getPosition().y + circle.getRadius() - hero_score_text.getCharacterSize()/2 - shift_coef);
}

sf::Color Game::getColor(){
  return cur_color;
}

void Game::randColor(){
  srand(time(0));
  cur_color = array_colors[rand() % array_colors.size() ];
}

void Game::counterGame(Hero& hero, sf::RenderWindow& window){
  std::ostringstream hero_score_string;
  if (hero.getScore() == 10)
    hero_score_text.setPosition(circle.getPosition().x + circle.getRadius() - hero_score_text.getCharacterSize()/2, circle.getPosition().y + circle.getRadius() - hero_score_text.getCharacterSize()/2 - shift_coef);
  hero_score_string << hero.getScore();
  hero_score_text.setString(hero_score_string.str());
  window.draw(circle);
  window.draw(hero_score_text);
}
