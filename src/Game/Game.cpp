/*
 * Game.cpp
 *
 *  Created on: 25 oct. 2018
 *      Author: antonin
 */

#include "Game.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>




namespace ta {

Game::Game() :
		m_numberRow(10), m_numberColumn(10), m_numberMine(10) {
	init();
}

Game::Game(int numberRow, int numberColumn, int numberMine) :
		m_numberRow(numberRow), m_numberColumn(numberColumn), m_numberMine(
		numberMine),
m_listCaseWidget(m_numberRow,
				std::vector<CaseWidget*>(m_numberColumn, 0)) {
	init();
}

Game::~Game() {
	delete m_windowWidget;
	delete m_listCase; // delete all 
	delete m_window;
}

void Game::init() {
	m_isInGame = true;
	
	m_window = new sf::RenderWindow(sf::VideoMode(800, 800), "Demineur");
	
	m_windowWidget = new Widget(m_window);

	// config window
	m_windowWidget->setDimention(800, 800);
	m_window->setFramerateLimit(60);
	
	
	// create case widget
	generateCaseList();
	
	for (int x = 0; x < m_numberRow; x++) {
		for (int y = 0; y < m_numberColumn; y++) {
			CaseWidget *caseWidget = new CaseWidget(getCase(x, y),
					x, y, this,
					m_windowWidget
			); // it is auto delete
			m_listCaseWidget.at(x).at(y) = caseWidget;
		}
	} 
}

void Game::generateCaseList() {
	m_listCase = new std::vector<std::vector<Case>>(m_numberRow,
			std::vector<Case>(m_numberColumn, Case::Void));
	
	srand(time(NULL));
	
	int mineRemainingToPlace = m_numberMine;
	
	while (mineRemainingToPlace > 0) {
		int x(rand() % m_numberRow);
		int y(rand() % m_numberColumn);
		
		if (placeMine(x, y)) // if can place bomb at random coord 
							 // then remove one mine remaining
			mineRemainingToPlace--;
	}
}

bool Game::placeMine(int x, int y) {
	if (*getCase(x, y) == Case::Mine)
		return false;
	
	Case* listCaseToAdd[8];
	
	/*  x - 1 y - 1 | x - 1 y | x - 1 y + 1
	 *  x     y - 1 |x y bomb | x     y + 1
	 *  x + 1 y - 1 | x + 1 y | x + 1 y + 1 
	 */
	
	listCaseToAdd[0] = getCase(x - 1, y - 1);
	listCaseToAdd[1] = getCase(x - 1, y);
	listCaseToAdd[2] = getCase(x - 1, y + 1);

	listCaseToAdd[3] = getCase(x, y - 1);
	listCaseToAdd[4] = getCase(x, y + 1);

	listCaseToAdd[5] = getCase(x + 1, y - 1);
	listCaseToAdd[6] = getCase(x + 1, y);
	listCaseToAdd[7] = getCase(x + 1, y + 1);

	for (short int i = 0; i < 8; i++) {
		if (listCaseToAdd[i] != 0 && *listCaseToAdd[i] == Case::Four) // if case around bomb is 4 (max) return
			return false;
	}

	for (short int i = 0; i < 8; i++) { // add 1 tp all case aroud
		if (listCaseToAdd[i] != 0)

			// add 1 in listCaseToAdd
			
			switch (*listCaseToAdd[i]) {
			case Void:
				*listCaseToAdd[i] = Case::One;
				break;
				
			case One:
				*listCaseToAdd[i] = Case::Two;
				break;

			case Two:
				*listCaseToAdd[i] = Case::Three;
				break;

			case Three:
				*listCaseToAdd[i] = Case::Four;
				break;

			default:
				//std::cout << "Can't add one: " << *listCaseToAdd[i] << "(";
				//printCaseEnum(*listCaseToAdd[i]);
				//std::cout << ")" << std::endl;
				break;
			}; 
	}
	
	*getCase(x, y) = Case::Mine; // set the case to mine

	return true;
}

void Game::run() {
	while (m_window->isOpen()) {
		sf::Event event;

		while (m_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {

				m_window->close();
			}

			if (m_isInGame && event.type == sf::Event::MouseButtonPressed) {
				m_windowWidget->onClick(event.mouseButton);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

			for (int x = 0; x < m_numberRow; x++) {
				for (int y = 0; y < m_numberColumn; y++) {
					ta::printCaseEnum(*getCase(x, y));
					std::cout << " ";
				}
				std::cout << std::endl;
			}

			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			}
		}

		m_window->clear();
		m_windowWidget->drawAllChild();
		m_window->display();

	}
}

Case* Game::getCase(int x, int y) {
	// in vector is stock: {r0c0, r0c1, r1l0, r1l1}	
	if (x < 0 || x >= m_numberRow || y < 0 || y >= m_numberColumn) // test if x and y are in list
		return 0;
	
	return &(m_listCase->at(x).at(y));
}

CaseWidget* Game::getCaseWidget(int x, int y) {
	if (x < 0 || x >= m_numberRow || y < 0 || y >= m_numberColumn) // test if x and y are in list
		return 0;
	 
	return m_listCaseWidget.at(x).at(y);
}

std::vector<std::vector<Case>>* Game::listCase() {
	return m_listCase;
}

void Game::loose() {
	m_isInGame = false;
	
	for (int x = 0; x < m_numberRow; x++) {
		for (int y = 0; y < m_numberColumn; y++) {
			getCaseWidget(x, y)->looseShow();
		}
	}
}

int Game::numberRow() {
	return m_numberRow;
}

int Game::numberColumn() {
	return m_numberColumn;
}

int Game::numberMine() {
	return m_numberMine;
}

} /* namespace ta */
