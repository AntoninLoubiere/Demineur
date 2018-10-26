/*
 * Case.h
 *
 *  Created on: 25 oct. 2018
 *      Author: antonin
 */

#ifndef SRC_GAME_CASE_H_
#define SRC_GAME_CASE_H_

#include <iostream>

namespace ta {

enum CaseState {

	Hide, Show, MineHide, MayBe
};

enum Case {
	Void, One, Two, Three, Four, Mine
};

void printCaseEnum(Case caseToPrint);

} /* namespace ta */

#endif /* SRC_GAME_CASE_H_ */
