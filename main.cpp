#include "hero.h"
#include "map.h"
#include "game.h"

Hero hero;
Map map;

int main()
{
  Game game;
  srand(time(0));
  sf::RenderWindow window(sf::VideoMode(game.getWidth(), game.getHeight()), "SFML works!", sf::Style::Fullscreen);
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(game.FPS);

  while (window.isOpen()){

    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
      if (event.type == event.KeyReleased && press_flag == 0)
        press_flag = 1;
    }
    hero.logic(window);

    window.clear(game.getColor());
    map.drawMap(window);
    game.counterGame(hero, window);
    window.draw(hero.getSprite());
    window.display();
  }

  return 0;
}
