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


namespace ta {

CaseWidget::CaseWidget(Case *c, sf::Vector2<float> pos, Widget *parent) :
		Widget(parent), m_case(c) {
	setDimention(CASE_SIZE, CASE_SIZE);
	setPosition(pos);
	
	loadTexture();

	m_caseState = CaseState::Hide;
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
		m_caseSprite.setTextureRect(sf::IntRect(1 * 128, 2 * 128, 128, 128));
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
			showCase();
		}

		if (event.button == sf::Mouse::Right) {
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
	m_caseState = CaseState::Show;
	setCaseShowTexture();
}

} /* namespace ta */
