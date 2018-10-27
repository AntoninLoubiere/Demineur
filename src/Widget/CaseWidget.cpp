/*
 * CaseWidget.cpp
 *
 *  Created on: 26 oct. 2018
 *      Author: antonin
 */

#include "CaseWidget.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

#include "../Game/Game.h"


namespace ta {

CaseWidget::CaseWidget(Case *c, int x, int y, Game * game, Widget *parent) :
		Widget(parent), m_case(c), m_x(x), m_y(y), m_game(game) {
	setDimention(CASE_SIZE, CASE_SIZE);
	setPosition(y * CASE_SIZE, x * CASE_SIZE);
	
	loadTexture();

	m_caseState = CaseState::Hide;

	std::cout << "Create: " << m_x << ", " << m_y << std::endl;
}

CaseWidget::~CaseWidget() {
	std::cout << "Coretly delete: " << m_x << ", " << m_y << std::endl;
	
	this->~Widget();
}

void CaseWidget::loadTexture() {
	if (!m_caseTexture.loadFromFile(
			"/home/antonin/git/Démineur/Debug/tiles/cases.png")) {
		std::cout << "Error can't open tiles/cases.png";
	}

	m_caseTexture.setSmooth(true);

	m_caseSprite.setTexture(m_caseTexture);
	setCaseTexture(CaseState::Hide);

	m_caseSprite.setScale(
			(float) CASE_SIZE / m_caseSprite.getGlobalBounds().width,
			(float) CASE_SIZE / m_caseSprite.getGlobalBounds().height);
	m_caseSprite.setPosition(m_position);
}

void CaseWidget::setCaseTexture(CaseState caseState) {
	switch (caseState) {
	case Show:
		setCaseShowTexture();
		break;
		
	case Hide:
		m_caseSprite.setTextureRect(sf::IntRect(2 * 128, 1 * 128, 128, 128));
		break;

	case MayBe: 
		m_caseSprite.setTextureRect(sf::IntRect(1 * 128, 2 * 128, 128, 128));
		break;

	case MineHide:
		m_caseSprite.setTextureRect(sf::IntRect(0 * 128, 2 * 128, 128, 128));
	}
}
void CaseWidget::setCaseShowTexture() {
	switch (*m_case) {
	case Void:
		m_caseSprite.setTextureRect(sf::IntRect(0 * 128, 0 * 128, 128, 128));
		break;

	case One:
		m_caseSprite.setTextureRect(sf::IntRect(1 * 128, 0 * 128, 128, 128));
		break;

	case Two:
		m_caseSprite.setTextureRect(sf::IntRect(2 * 128, 0 * 128, 128, 128));
		break;

	case Three:
		m_caseSprite.setTextureRect(sf::IntRect(0 * 128, 1 * 128, 128, 128));
		break;

	case Four:
		m_caseSprite.setTextureRect(sf::IntRect(1 * 128, 1 * 128, 128, 128));
		break;
		
	case Mine:
		m_caseSprite.setTextureRect(sf::IntRect(2 * 128, 2 * 128, 128, 128));
		break;
	}
}

void CaseWidget::draw() {
	m_window->draw(m_caseSprite);
}

void CaseWidget::update() {

}

void CaseWidget::onClick(const sf::Event::MouseButtonEvent &event) {
	if (event.x >= m_position.x
			&& event.x <= m_position.x + m_dimension.x
			&& event.y >= m_position.y
			&& event.y <= m_position.y + m_dimension.y) {

		if (event.button == sf::Mouse::Left && m_caseState == CaseState::Hide) {
			// left click

			if (*m_case == Case::Mine) {
				m_game->loose();
				return;
			}
			showCase();
		}

		if (event.button == sf::Mouse::Right) {
			// right click
			
			switch (m_caseState) {
			case Hide:
				m_caseState = CaseState::MineHide;
				break;
			case MineHide:
				m_caseState = CaseState::MayBe;
				break;
			case MayBe:
				m_caseState = CaseState::Hide;
				break;
			default:
				break;
			} /* sitch */

			setCaseTexture(m_caseState);
		}
	}

	this->Widget::onClick(event); // repet click
}

void CaseWidget::showCase() {
	if (m_caseState == CaseState::Hide) {		
		m_caseState = CaseState::Show;
		setCaseShowTexture();

		if (*m_case == Case::Void) {
			// if there are blank show all cases around
			CaseWidget *listToShow[8];
			listToShow[0] = m_game->getCaseWidget(m_x - 1, m_y - 1);
			listToShow[1] = m_game->getCaseWidget(m_x - 1, m_y);
			listToShow[2] = m_game->getCaseWidget(m_x - 1, m_y + 1);

			listToShow[3] = m_game->getCaseWidget(m_x, m_y - 1);
			listToShow[4] = m_game->getCaseWidget(m_x, m_y + 1);

			listToShow[5] = m_game->getCaseWidget(m_x + 1, m_y - 1);
			listToShow[6] = m_game->getCaseWidget(m_x + 1, m_y);
			listToShow[7] = m_game->getCaseWidget(m_x + 1, m_y + 1);

			for (CaseWidget* toShow : listToShow) {
				if (toShow != 0)
					toShow->showCase();
			}

		}
	}
}

void CaseWidget::looseShow() {
	if (m_caseState != CaseState::MineHide && *m_case == Case::Mine) {
		// if is a mine hide
		m_caseState = CaseState::Show;
		
		m_caseSprite.setTextureRect(sf::IntRect(2 * 128, 2 * 128, 128, 128));
	} else if (m_caseState == CaseState::MineHide && *m_case != Case::Mine) {
		// if isn't a mine but it click mine
		m_caseState = CaseState::Show;
		
		m_caseSprite.setTextureRect(sf::IntRect(0 * 128, 3 * 128, 128, 128));
	}
}

} /* namespace ta */
