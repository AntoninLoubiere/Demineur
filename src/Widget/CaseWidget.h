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
#include <SFML/Window/Event.hpp>

#include "../Game/Case.h"
#include "Widget.h"

namespace ta {
class Game;
} /* namespace ta */


#define CASE_SIZE 35

namespace ta {

class CaseWidget: public Widget {
public:
	CaseWidget(Case* c, int x, int y, Game* game, Widget *parent = 0);
	virtual ~CaseWidget();

	virtual void draw() override;
	virtual void update() override;

	virtual void onClick(const sf::Event::MouseButtonEvent& event) override;

	void showCase();

	void looseShow();

private:
	void loadTexture();
	void setCaseTexture(CaseState caseState);
	
	void setCaseShowTexture();
	
	Case* m_case;
	CaseState m_caseState;

	sf::Texture m_caseTexture;
	sf::Sprite m_caseSprite;

	ta::Game* m_game;

	int m_x;
	int m_y;
};

} /* namespace ta */

#endif /* SRC_WIDGET_CASEWIDGET_H_ */
