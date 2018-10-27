/*
 * Game.h
 *
 *  Created on: 25 oct. 2018
 *      Author: antonin
 */

#ifndef SRC_GAME_GAME_H_
#define SRC_GAME_GAME_H_

#include <vector>

#include "../Widget/CaseWidget.h"
#include "Case.h"

namespace ta {

class Game {
public:
	Game();
	Game(int numberRow, int numberColumn, int numberMine);
	virtual ~Game();

	Case* getCase(int x, int y);
	ta::CaseWidget* getCaseWidget(int x, int y);
	
	// getter
	std::vector<std::vector<Case>>* listCase();
	std::vector<std::vector<ta::CaseWidget *>> listCaseWidget();
	
	int numberRow();
	int numberColumn();
	int numberMine();

	void run();

	void loose();

private:
	const int m_numberRow;
	const int m_numberColumn;
	const int m_numberMine;

	bool placeMine(int x, int y);

	void init();
	void generateCaseList();

	bool m_isInGame;
	
	sf::RenderWindow* m_window;

	Widget *m_windowWidget;
	
	std::vector<std::vector<Case>>* m_listCase;
	std::vector<std::vector<ta::CaseWidget *>> m_listCaseWidget;
};

} /* namespace ta */

#endif /* SRC_GAME_GAME_H_ */
