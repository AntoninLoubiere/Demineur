//============================================================================
// Name        : Démineur.cpp
// Author      : PyJaC++
// Version     :
// Copyright   : GNU
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

#include "Game/Case.h"
#include "Game/Game.h"
#include "Widget/Rect.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(200, 200), "Test");
	
	ta::Widget *windowWidget = new ta::Widget(&window);
	windowWidget->setDimention(200, 200);

	ta::Rect *rect = new ta::Rect(windowWidget);

	window.setFramerateLimit(60);

	rect->setPosition(10, 10);

	while (window.isOpen()) {
		sf::Event event;
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				
				window.close();
			}
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			ta::Game game;
			
			for (int x = 0; x < game.numberRow(); x++) {
				for (int y = 0; y < game.numberColumn(); y++) {
					if (*(game.getCase(x, y)) == ta::Case::Void) {
						std::cout << x << ", " << y << ": V ";
					}

					//std::cout << *game.getCase(x, y);
				}
				std::cout << std::endl;
			}

			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			}
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			rect->move(0, 2);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			rect->move(0, -2);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			rect->move(2, 0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			rect->move(-2, 0);
		}
		
		window.clear();
		windowWidget->drawAllChild();
		window.display();

	}

	delete windowWidget;
	return 0;
}
