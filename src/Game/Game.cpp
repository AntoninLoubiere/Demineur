/*
 * Game.cpp
 *
 *  Created on: 25 oct. 2018
 *      Author: antonin
 */

#include "Game.h"

#include <cstdlib>
#include <ctime>
#include <iostream>



namespace ta {

Game::Game() :
		m_numberRow(10), m_numberColumn(10), m_numberMine(10) {
	generateCaseList();
}

Game::Game(int numberRow, int numberColumn, int numberMine) :
		m_numberRow(numberRow), m_numberColumn(numberColumn), m_numberMine(
				numberMine) {
	generateCaseList();
}

Game::~Game() {
	delete m_caseList; // delete all 
}

void Game::generateCaseList() {
	m_caseList = new std::vector<std::vector<Case>>(m_numberRow,
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
				std::cout << "Can't add one: " << *listCaseToAdd[i] << "(";
				printCaseEnum(*listCaseToAdd[i]);
				std::cout << ")" << std::endl;
				break;
			}; 
	}
	
	*getCase(x, y) = Case::Mine; // set the case to mine

	return true;
}

Case* Game::getCase(int x, int y) {
	// in vector is stock: {r0c0, r0c1, r1l0, r1l1}	
	if (x < 0 || x >= m_numberRow || y < 0 || y >= m_numberColumn) // test if x and y are in list
		return 0;
	
	return &(m_caseList->at(x).at(y));
}
	

std::vector<std::vector<Case>>* Game::caseList() {
	return m_caseList;
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
