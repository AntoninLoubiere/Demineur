/*
 * Rect.cpp
 *
 *  Created on: 23 oct. 2018
 *      Author: antonin
 */

#include "Rect.h"

#include "Dimension.h"

namespace ta {

Rect::Rect(Widget *parent) :
		Widget(parent) {
}

Rect::Rect(Dimention<int> dim, Widget *parent) :
		Widget(dim, parent) {

}

Rect::Rect(sf::Vector2<int> pos, Dimention<int> dim, Widget* parent) :
		Widget(pos, dim, parent) {

}

Rect::~Rect() {
	this->~Widget();
}

void Rect::draw() {

}

void Rect::update() {

}

} /* namespace ta */
