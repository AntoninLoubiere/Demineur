/*
 * Widget.cpp
 *
 *  Created on: 23 oct. 2018
 *      Author: PyJaC++
 */

#include "Widget.h"

#include <cstdint>
#include <iostream>
#include <iterator>

namespace ta {

Widget::Widget(Widget* parent) {
	if (parent != 0) {
		parent->addChild(this);

		m_parent = parent;

		m_window = parent->window();
	}

	m_dimension.x = 0;
	m_dimension.y = 0;

	m_position = sf::Vector2f(0, 0);
}

Widget::Widget(Dimention<int> dim, Widget* parent) :
		m_dimension(dim) {
	if (parent != 0) {
		parent->addChild(this);

		m_parent = parent;
		m_window = parent->window();
	}

	m_position = sf::Vector2f(0, 0);

}

Widget::Widget(sf::Vector2<float> pos, Dimention<int> dim, Widget *parent) :
		m_parent(parent) {
	if (parent != 0) {
		parent->addChild(this);
	}
	setPosition(pos);
}

Widget::Widget(sf::RenderWindow *window) :
		m_window(window), m_parent(0) {

	m_dimension.x = INT16_MAX;
	m_dimension.y = INT16_MAX;

	m_position = sf::Vector2f(0, 0);
}

Widget::~Widget() {
	if (m_parent != 0)
		m_parent->removeChild(this);
	
	deleteAllChilds();
}

void Widget::addChild(Widget *child) {
	m_listChild.push_back(child);
}

void Widget::removeChild(Widget *child) {

	for (std::vector<Widget*>::iterator it = m_listChild.begin();
			it != m_listChild.end(); it++) {

		if (child == *it) {
			m_listChild.erase(it);
			return;
		}
		
	}
	
}

void Widget::deleteAllChilds() {	
	while (m_listChild.size() > 0) {
		delete m_listChild.at(0);
	}
}

void Widget::draw() {

}

void Widget::update() {

}

void Widget::onClick(const sf::Event::MouseButtonEvent &event) {
	if (event.x >= m_position.x && event.x <= m_position.x + m_dimension.x
			&& event.y >= m_position.y
			&& event.y <= m_position.y + m_dimension.y)
	{
		
		for (Widget* currentWidget : m_listChild) {
			currentWidget->onClick(event);
		}
		
	}
}

void Widget::drawAllChild() {
	draw();

	for (Widget* currentWidget : m_listChild) {
		currentWidget->drawAllChild();
	}
}

void Widget::updateAllChild() {
	update();

	for (Widget* currentWidget : m_listChild) {
		currentWidget->updateAllChild();
	}
}

bool Widget::setPosition(float x, float y) {
	return setPosition(sf::Vector2f(x, y));
}

bool Widget::setPosition(sf::Vector2<float> pos) {
	bool returnBool = true;
	
	m_position = pos;
	
	if (m_parent != 0) {
		// test if x pis too small or to big
		if (pos.x < m_parent->position().x) {
			returnBool = false;
			m_position.x = m_parent->position().x;
		} else if (pos.x + m_dimension.x
				> m_parent->position().x + m_parent->dimention().x) {
			returnBool = false;
			m_position.x = m_parent->m_dimension.x - m_dimension.x
					+ m_parent->position().x;
		}

		// idem but for y
		if (pos.y < m_parent->position().y) {
			returnBool = false;
			m_position.y = m_parent->position().y;
		} else if (pos.y + m_dimension.y
				> m_parent->position().y + m_parent->dimention().y) {
			returnBool = false;
			m_position.y = m_parent->m_dimension.y - m_dimension.y
					+ m_parent->position().y;
		}
	}

	return returnBool;
}

bool Widget::move(int x, int y) {
	return setPosition(x + m_position.x, y + m_position.y);
}

void Widget::setDimention(int x, int y) {
	Dimention<int> dim;
	
	dim.x = x;
	dim.y = y;
	
	setDimention(dim);
}

void Widget::setDimention(Dimention<int> dim) {
	m_dimension = dim;
}

sf::Vector2<float> Widget::position() const {
	return m_position;
}

Dimention<int> Widget::dimention() const {
	return m_dimension;
}

sf::RenderWindow* Widget::window() const {
	return m_window;
}
} /* namespace Thanto */
