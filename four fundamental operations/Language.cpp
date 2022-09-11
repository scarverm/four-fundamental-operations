
#include "Language.hpp"

using namespace std;

Language::Language() {
	langType = ch;
}

void Language::setLang(int langType) {
	this->langType = langType;
}

string Language::showLang(int index) {
	if (langType == ch) {
		return Chinese[index];
	}
	else if (langType == en) {
		return English[index];
	}
	else if (langType == fr) {
		return French[index];
	}
	else if (langType == ge) {
		return German[index];
	}
}