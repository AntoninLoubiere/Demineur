/*
 * Rect.h
 *
 *  Created on: 23 oct. 2018
 *      Author: antonin
 */

#ifndef SRC_WIDGET_RECT_H_
#define SRC_WIDGET_RECT_H_

#include <SFML/Graphics/Rect.hpp>

#include "Dimension.h"
#include "Widget.h"

namespace ta {

class Rect: public Widget {
public:
	Rect(Widget *parent = 0);
	Rect(Dimention<int> dim, Widget *parent = 0);
	Rect(sf::Vector2<int> pos, Dimention<int> dim, Widget* parent = 0);
	
	virtual ~Rect();

	virtual void draw() override;
	virtual void update() override;

private:
	void init();

	sf::Rect<int> rect;
};

} /* namespace ta */

#endif /* SRC_WIDGET_RECT_H_ */
