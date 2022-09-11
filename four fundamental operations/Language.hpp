#pragma once
#ifndef __Language_HPP__
#define __Language_HPP__

#include <vector>
#include <string>

using namespace std;

class Language {
public :
	const int ch = 0;
	const int en = 1;
	const int fr = 2;
	const int ge = 3;
	int langType;
	const vector <string> Chinese =
	{"�������꼶(3��4��5):", "��������ȷ���꼶(3��4��5):",
	"��������Ŀ������:", "��������ȷ����Ŀ����:", "�������:",
	"�ش���ȷ", "��ȷ:", "����:",
	"�ش������ȷ��Ϊ:", "��" 
	};
	const vector <string> English =
	{ 
		"Please enter grade(3��4 or 5):",
		"Please enter the correct grade(3��4 or 5):", "Please enter the number of questions:",
		"Please enter the correct number of questions:", "Please enter the answer:",
		"Correct", "Correct", "Wrong", "Wrong. the correct answer is:", "or" 
	};
	const vector <string> French =
	{
		"Veuillez entrer un grade(3, 4 ou 5):",
		"Veuillez entrer le grade correct:", "Veuillez entrer le nombre de sujets:",
		"Veuillez entrer le nombre correct de sujets:", "Veuillez entrer une r��ponse:", 
		"R��pondez correctement", "La bonne:", "Les erreurs:",
		"R��ponse incorrecte. La bonne r��ponse est:", "ou"
	};
	const vector <string> German =
	{
		"Beginnen sie die klassen(3, 4 Oder 5):",
		"Bitte geben sie die richtige klasse ein(3, 4 Oder 5):", "Bitte geben sie die anzahl der titel ein:",
		"Bitte geben sie die richtige projektnummer ein:", "Bitte geben sie die antwort ein:",
		"Diese preise sind frevelhaft", "Korrekt:", "Falsch:", 
		"Die korrekte antwort lautet:","oder"
	};

	Language();
	void setLang(int langType);
	string showLang(int index);

};

#endif