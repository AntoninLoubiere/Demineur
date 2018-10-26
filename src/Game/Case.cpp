#include "Case.h"

void ta::printCaseEnum(ta::Case caseToPrint) {
	switch (caseToPrint) {
	case Void:
		std::cout << "V";
		break;

	case One:
		std::cout << "1";
		break;

	case Two:
		std::cout << "2";
		break;

	case Three:
		std::cout << "3";
		break;

	case Four:
		std::cout << "4";
		break;

	case Hide:
		std::cout << "H";
		break;

	case Mine:
		std::cout << "M";
		break;

	case Maybe:
		std::cout << "?";
	}
}
