/*
 * Game.cpp
 *
 *  Created on: 25 oct. 2018
 *      Author: antonin
 */

#include "Game.h"

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
	for (int i = 0; i < m_numberRow * m_numberColumn; i++) {
		delete m_caseList++; // delete all 
}
}

void Game::generateCaseList() {
	m_caseList = new Case[m_numberRow * m_numberColumn];
	
	for (int x = 0; x < m_numberRow * m_numberColumn; x++) {
		m_caseList[x] = Case::Void;
	}
}

Case *Game::getCase(int x, int y) {
	// in vector is stock: {r0c0, r0c1, r1l0, r1l1}
	return &m_caseList[x * m_numberColumn + y];
}

Case* Game::caseList() {
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
