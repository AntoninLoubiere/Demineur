/*
 * Widget.h
 *
 *  Created on: 23 oct. 2018
 *      Author: PyJaC++
 */
#ifndef WIDGET_H_
#define WIDGET_H_

#include <list>

#include "Dimension.h"
#include <SFML/Graphics.hpp>

namespace ta {

class Widget {
public:
	Widget(Widget *parent = 0);
	Widget(sf::RenderWindow);
	Widget(Dimention<int> dim, Widget *parent = 0);
	Widget(sf::Vector2<int> pos, Dimention<int> dim, Widget* parent = 0);
	virtual ~Widget();
	
	virtual void draw() = 0;
	virtual void update() = 0;

	
	virtual bool setPosition(int x, int y);
	virtual bool setPosition(sf::Vector2<int>);
	virtual bool move(int x, int y);

	sf::Vector2<int> position() const;
	Dimention<int> dimention() const;

protected:
	
	void addChild(Widget*child);
	void removeChild(Widget *child);
	void deleteAllChilds();
	
	Widget * m_parent;
	std::list<Widget*> m_listChild;
	
	sf::Vector2<int> m_position;	
	Dimention<int> m_dimension;
};

} /* namespace Thanto */

#endif /* WIDGET_H_ */
