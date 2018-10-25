/*
 * Rect.cpp
 *
 *  Created on: 23 oct. 2018
 *      Author: antonin
 */

#include "Rect.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>


namespace ta {

Rect::Rect(Widget *parent) :
		Widget(parent) {
	init();
}

Rect::Rect(Dimention<int> dim, Widget *parent) :
		Widget(dim, parent) {
	init();
}

Rect::Rect(sf::Vector2<float> pos, Dimention<int> dim, Widget* parent) :
		Widget(pos, dim, parent) {
	init();
}

Rect::~Rect() {
	this->~Widget();
}

void Rect::init() {
	m_position = sf::Vector2f(10, 10);
	m_dimension.x = 10;
	m_dimension.y = 10;
	m_rect = sf::RectangleShape(m_position);
}

bool Rect::setPosition(float x, float y) {
	bool returnBool = this->Widget::setPosition(sf::Vector2f(x, y));
	
	m_rect.setPosition(x, y);

	return returnBool;
}

bool Rect::move(int x, int y) {
	bool returnBool = Widget::move(x, y);

	m_rect.setPosition(m_position);

	return returnBool;
}

void Rect::draw() {
	m_window->draw(m_rect);
}

void Rect::update() {

}

} /* namespace ta */
