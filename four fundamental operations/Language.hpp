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
	{"请输入年级(3、4或5):", "请输入正确的年级(3、4或5):",
	"请输入题目的数量:", "请输入正确的题目数量:", "请输入答案:",
	"回答正确", "正确:", "错误:",
	"回答错误，正确答案为:", "或" 
	};
	const vector <string> English =
	{ 
		"Please enter grade(3、4 or 5):",
		"Please enter the correct grade(3、4 or 5):", "Please enter the number of questions:",
		"Please enter the correct number of questions:", "Please enter the answer:",
		"Correct", "Correct", "Wrong", "Wrong. the correct answer is:", "or" 
	};
	const vector <string> French =
	{
		"Veuillez entrer un grade(3, 4 ou 5):",
		"Veuillez entrer le grade correct:", "Veuillez entrer le nombre de sujets:",
		"Veuillez entrer le nombre correct de sujets:", "Veuillez entrer une réponse:", 
		"Répondez correctement", "La bonne:", "Les erreurs:",
		"Réponse incorrecte. La bonne réponse est:", "ou"
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