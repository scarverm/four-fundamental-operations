#pragma once
#ifndef _LANGUAGE_HPP_
#define _LANGUAGE_HPP_

#include <vector>
#include <string>
using namespace std;

enum LangType
{
	CHINESE,
	ENGLISH,
	FRENCH,
	GERMAN
};

class Language {
public:
	LangType langType;
	const vector <string> Chinese =
	{ "�������꼶(3��4��5):", "��������ȷ���꼶(3��4��5):",
	"��������Ŀ������:", "��������ȷ����Ŀ����:", "�������:",
	"�ش���ȷ", "��ȷ:", "����:",
	"�ش������ȷ��Ϊ:", "��", "��:"
	};
	const vector <string> English =
	{
		"Please enter grade(3��4 or 5):",
		"Please enter the correct grade(3��4 or 5):", "Please enter the number of questions:",
		"Please enter the correct number of questions:", "Please enter the answer:",
		"Correct", "Correct", "Wrong", "Wrong. the correct answer is:", "or", "answer:"
	};
	const vector <string> French =
	{
		"Veuillez entrer un grade(3, 4 ou 5):",
		"Veuillez entrer le grade correct:", "Veuillez entrer le nombre de sujets:",
		"Veuillez entrer le nombre correct de sujets:", "Veuillez entrer une r��ponse:",
		"R��pondez correctement", "La bonne:", "Les erreurs:",
		"R��ponse incorrecte. La bonne r��ponse est:", "ou", "r��ponse:"
	};
	const vector <string> German =
	{
		"Beginnen sie die klassen(3, 4 Oder 5):",
		"Bitte geben sie die richtige klasse ein(3, 4 Oder 5):", "Bitte geben sie die anzahl der titel ein:",
		"Bitte geben sie die richtige projektnummer ein:", "Bitte geben sie die antwort ein:",
		"Diese preise sind frevelhaft", "Korrekt:", "Falsch:",
		"Die korrekte antwort lautet:","oder", "Die antworten:"
	};

	Language();
	void setLang(LangType langType);
	string showLang(int index);
};

#endif // !_LANGUAGE_HPP_
