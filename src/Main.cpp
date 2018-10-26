//============================================================================
// Name        : Démineur.cpp
// Author      : PyJaC++
// Version     : 0.1
// Copyright   : GNU
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

#include "Game/Case.h"
#include "Game/Game.h"
#include "Widget/CaseWidget.h"


int main() {
	sf::RenderWindow window(sf::VideoMode(800, 800), "Demineur");
	
	ta::Widget *windowWidget = new ta::Widget(&window);
	windowWidget->setDimention(800, 800);

	window.setFramerateLimit(60);

	ta::Game
	game(21, 23, 95);
	
	// create all caseWidget
	
	
	for (int x = 0; x < game.numberRow(); x++) {
		for (int y = 0; y < game.numberColumn(); y++) {
			new ta::CaseWidget(game.getCase(x, y),
					sf::Vector2f(y * CASE_SIZE, x * CASE_SIZE),
					windowWidget); // it is auto delet(e
		}
	} 

	while (window.isOpen()) {
		sf::Event event;
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				windowWidget->onClick(event.mouseButton);
			}
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
						
			for (int x = 0; x < game.numberRow(); x++) {
				for (int y = 0; y < game.numberColumn(); y++) {
					ta::printCaseEnum(*game.getCase(x, y));
					std::cout << " ";
				}
				std::cout << std::endl;
			}

			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			}
		}
		
		window.clear();
		windowWidget->drawAllChild();
		window.display();

	}

	delete windowWidget;
	return 0;
}
