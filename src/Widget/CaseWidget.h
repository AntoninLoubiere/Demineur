/*
 * CaseWidget.h
 *
 *  Created on: 26 oct. 2018
 *      Author: antonin
 */

#ifndef SRC_WIDGET_CASEWIDGET_H_
#define SRC_WIDGET_CASEWIDGET_H_

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include "../Game/Case.h"
#include "Widget.h"

#define CASE_SIZE 35

namespace ta {

class CaseWidget: public Widget {
public:
	CaseWidget(Case *c, sf::Vector2<float> pos, Widget *parent = 0);
	virtual ~CaseWidget();

	virtual void draw();
	virtual void update();

private:
	void loadTexture();
	void setCaseTexture(Case caseToShow);
	
	Case* m_case;

	sf::Texture m_caseTexture;
	sf::Sprite m_caseSprite;
};

} /* namespace ta */

#endif /* SRC_WIDGET_CASEWIDGET_H_ */
