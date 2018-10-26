/*
 * Game.h
 *
 *  Created on: 25 oct. 2018
 *      Author: antonin
 */

#ifndef SRC_GAME_GAME_H_
#define SRC_GAME_GAME_H_

#include <vector>

#include "Case.h"

namespace ta {

class Game {
public:
	Game();
	Game(int numberRow, int numberColumn, int numberMine);
	virtual ~Game();

	Case* getCase(int x, int y);
	
	// getter
	std::vector<std::vector<Case>>* caseList();	
	int numberRow();
	int numberColumn();
	int numberMine();

private:
	const int m_numberRow;
	const int m_numberColumn;
	const int m_numberMine;

	bool placeMine(int x, int y);

	void generateCaseList();

	std::vector<std::vector<Case>>* m_caseList;
};

} /* namespace ta */

#endif /* SRC_GAME_GAME_H_ */
