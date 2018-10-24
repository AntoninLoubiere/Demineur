/*
 * Widget.cpp
 *
 *  Created on: 23 oct. 2018
 *      Author: PyJaC++
 */

#include "Widget.h"

#include <SFML/System/Vector2.hpp>

namespace ta {

Widget::Widget(Widget* parent) {
	if (parent != 0) {
		parent->addChild(this);

		m_parent = parent;

		m_window = parent->window();
	}
}

Widget::Widget(Dimention<int> dim, Widget* parent) :
		m_dimension(dim) {
	if (parent != 0) {
		parent->addChild(this);

		m_parent = parent;
		m_window = parent->window();
	}

}

Widget::Widget(sf::Vector2<int> pos, Dimention<int> dim, Widget *parent) :
		m_dimension(dim) {
	if (parent != 0) {
		parent->addChild(this);

		m_parent = parent;
	}
	
	setPosition(pos);
}

Widget::Widget(sf::RenderWindow *window) :
		m_parent(0) {
	m_window = window;
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

	for (std::list<Widget*>::iterator it = m_listChild.begin();
			it != m_listChild.end(); it++) {

		if (child == *it) {
			m_listChild.erase(it);
			return;
		}
		
	}
	
}

void Widget::deleteAllChilds() {
	
	for (Widget *currentChild : m_listChild) {
		delete currentChild;
	}
	
}

bool Widget::setPosition(int x, int y) {
	return setPosition(sf::Vector2i(x, y));
}

bool Widget::setPosition(sf::Vector2<int> pos) {
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
			m_position.x = m_parent->m_dimension.x - m_dimension.y
					+ m_parent->position().y;
		}
	}

	return returnBool;
}

bool Widget::move(int x, int y) {
	return setPosition(x + m_position.x, y + m_position.y);
}

sf::Vector2<int> Widget::position() const {
	return m_position;
}

Dimention<int> Widget::dimention() const {
	return m_dimension;
}

sf::RenderWindow* Widget::window() {
	return m_window;
}
} /* namespace Thanto */
