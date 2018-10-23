/*
 * Widget.cpp
 *
 *  Created on: 23 oct. 2018
 *      Author: PyJaC++
 */

#include "Widget.h"

namespace ta {

Widget::Widget(Widget* parent) {
	if (parent != 0) {
		parent->addChild(this);

		m_parent = parent;
	}
}

Widget::~Widget() {
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
} /* namespace Thanto */
