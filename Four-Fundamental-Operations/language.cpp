#include "language.hpp"

Language::Language(){
	langType = CHINESE;
}

void Language::setLang(LangType langType){
	this->langType = langType;
}

string Language::showLang(int index){
	if (langType == CHINESE) {
		return Chinese[index];
	}
	else if (langType == ENGLISH) {
		return English[index];
	}
	else if (langType == FRENCH) {
		return French[index];
	}
	else if (langType == GERMAN) {
		return German[index];
	}
}
