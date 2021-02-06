#include <SFML/Graphics.hpp>
#include <iostream>

#include "global.h"
#include "states/operation.h"
#include "objects/mousetext.h"
#include "objects/fpstext.h"
#include "objects/pointer.h"

// g++ *.cpp objects/*.cpp states/*.cpp states/tools/*.cpp -I C:\SFML-2.5.1\include -L C:\SFML-2.5.1\lib -lsfml-graphics -lsfml-window -lsfml-system -O2 -o shared.exe
// g++ *.cpp objects/*.cpp states/*.cpp states/tools/*.cpp -DSFML_STATIC -I C:\SFML-2.5.1\include -L C:\SFML-2.5.1\lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lgdi32 -lwinmm -O2 -o static.exe

void out(double data) {
  std::cout << data << std::endl;
}

void out(std::string data) {
  std::cout << data << std::endl;
}

int main() {
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;
  int style = (sf::Style::Titlebar | sf::Style::Close);
  sf::VideoMode video = sf::VideoMode(1280, 720);
  sf::RenderWindow window(video, "SFML works!", style, settings);
  window.setMouseCursorVisible(false);
  window.setFramerateLimit(60);
  window.setKeyRepeatEnabled(false);

  GlobalValues *global = new GlobalValues();

  OperationState *operationState = new OperationState(global);

  MouseTextObject *mouseDebug = new MouseTextObject(global);
  FPSTextObject *fpsDebug = new FPSTextObject(global);
  PointerObject *pointer = new PointerObject(global);

  while (window.isOpen()) {
    sf::Time time = global->restartTime();
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::LostFocus:
          global->setFocus(false);
          break;
        case sf::Event::GainedFocus:
          global->setFocus(true);
          global->restartTime();
          break;
        case sf::Event::KeyPressed:
          break;
        case sf::Event::KeyReleased:
          break;
        case sf::Event::MouseButtonPressed:
          break;
        case sf::Event::MouseButtonReleased:
          break;
        case sf::Event::MouseMoved:
          break;
        case sf::Event::MouseEntered:
          global->setUpdateMouse(true);
          break;
        case sf::Event::MouseLeft:
          global->setUpdateMouse(false);
          break;
      }
    }

    window.clear(sf::Color::Black);

    // Update inputs, but only if focused
    if (global->hasFocus()) {
      // Do not update mouse if cursor is out of window boundary
      if (global->updateMouse()) {
        global->setMousePos(sf::Mouse::getPosition(window));
        global->setMouseActive(sf::Mouse::isButtonPressed(sf::Mouse::Left));
      }
      global->setKeyUp(sf::Keyboard::isKeyPressed(sf::Keyboard::W));
      global->setKeyLeft(sf::Keyboard::isKeyPressed(sf::Keyboard::A));
      global->setKeyDown(sf::Keyboard::isKeyPressed(sf::Keyboard::S));
      global->setKeyRight(sf::Keyboard::isKeyPressed(sf::Keyboard::D));
      global->setKeySpecial(sf::Keyboard::isKeyPressed(sf::Keyboard::F));
    }

    // Update states and objects
    operationState->update(time);
    pointer->update(time);
    mouseDebug->update(time);
    fpsDebug->update(time);

    // Render view
    operationState->draw(&window);
    pointer->draw(&window);
    mouseDebug->draw(&window);
    fpsDebug->draw(&window);

    window.display();
  }

  delete global;
  delete mouseDebug;
  delete fpsDebug;
  delete pointer;
  delete operationState;

  return 0;
}
