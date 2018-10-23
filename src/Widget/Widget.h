/*
 * Widget.h
 *
 *  Created on: 23 oct. 2018
 *      Author: PyJaC++
 */

#include <list>

#ifndef WIDGET_H_
#define WIDGET_H_

namespace ta {

class Widget {
public:
	Widget(Widget *parent = 0);
	virtual ~Widget();
	
	virtual void draw() = 0;
	virtual void update() = 0;

protected:
	
	virtual void addChild(Widget*child);
	virtual void removeChild(Widget *child);
	virtual void deleteAllChilds();
	
	Widget * m_parent;
	std::list<Widget*> m_listChild;
};

} /* namespace Thanto */

#endif /* WIDGET_H_ */
