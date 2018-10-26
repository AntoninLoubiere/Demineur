/*
 * CaseWidget.cpp
 *
 *  Created on: 26 oct. 2018
 *      Author: antonin
 */

#include "CaseWidget.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

#include "Dimension.h"

namespace ta {

CaseWidget::CaseWidget(Case *c, sf::Vector2<float> pos, Widget *parent) :
		Widget(parent), m_case(c) {
	setDimention(CASE_SIZE, CASE_SIZE);
	setPosition(pos);
	
	loadTexture();
}

CaseWidget::~CaseWidget() {
	this->~Widget();
}

void CaseWidget::loadTexture() {
	if (!m_caseTexture.loadFromFile(
			"/home/antonin/git/Démineur/Debug/tiles/cases.png")) {
		std::cout << "Error can't open tiles/cases.png";
	}

	m_caseTexture.setSmooth(true);

	m_caseSprite.setTexture(m_caseTexture);
	setCaseTexture(Case::Hide);

	// 128 10
	// 128 10

	m_caseSprite.setScale(
			(float) CASE_SIZE / m_caseSprite.getGlobalBounds().width,
			(float) CASE_SIZE / m_caseSprite.getGlobalBounds().height);
	m_caseSprite.setPosition(m_position);
}

void CaseWidget::setCaseTexture(Case caseToShow) {
	switch (caseToShow) {
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

	case Hide:
		m_caseSprite.setTextureRect(sf::IntRect(2 * 128, 1 * 128, 128, 128));
		break;

	case Mine:
		m_caseSprite.setTextureRect(sf::IntRect(0 * 128, 2 * 128, 128, 128));
		break;

	case Maybe:
		m_caseSprite.setTextureRect(sf::IntRect(1 * 128, 2 * 128, 128, 128));
		break;
	}
}

void CaseWidget::draw() {
	m_window->draw(m_caseSprite);
}

void CaseWidget::update() {

}

} /* namespace ta */
