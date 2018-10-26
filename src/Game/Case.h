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

enum Case {
	Void, One, Two, Three, Four, Hide, Mine, Maybe
};

void printCaseEnum(Case caseToPrint);

} /* namespace ta */

#endif /* SRC_GAME_CASE_H_ */
