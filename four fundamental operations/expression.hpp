#pragma once
#ifndef __expression_HPP__
#define __expression_HPP__

#include <iostream>
#include "Language.hpp"
using namespace std;

class Fraction {
public :
	Fraction() { molecule = 0; denominator = 0; }
	Fraction(int molecule, int denominator) :molecule(molecule), denominator(denominator) {}
	int molecule;		//����
	int denominator;	//��ĸ
	friend Fraction operator+(const Fraction& F1, const Fraction& F2);
	friend Fraction operator-(const Fraction& F1, const Fraction& F2);
	friend Fraction operator*(const Fraction& F1, const Fraction& F2);
	friend Fraction operator/(const Fraction& F1, const Fraction& F2);
	friend bool operator==(const Fraction & F1, const Fraction & F2);
	friend bool operator!=(const Fraction & F1, const Fraction & F2);
};

class Question {
public :
	int quesNum;	//��Ŀ����
	int symbolNum;	//���������������ȷ�����ʽ����
	Language Lang;
	string GeneSymbol(int m);
	void SetQuesNum(int quesNum);
	Fraction GetAnswer(string expression);
	void setLang(Language lang);
	virtual void ExpGenerate(char modeNum) = 0;
};

class QuestionFive : public Question {		//���꼶����Ŀ
public :
	virtual void ExpGenerate(char modeNum) override;
};

class QuestionFour : public Question {
public :
	virtual void ExpGenerate(char modeNum) override;
};

class QuestionThree : public Question {
public:
	virtual void ExpGenerate(char modeNum) override;
};

#endif