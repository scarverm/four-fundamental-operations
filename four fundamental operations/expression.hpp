#pragma once
#ifndef __expression_HPP__
#define __expression_HPP__

#include<iostream>
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

	string GeneSymbol(int m);
	void SetQuesNum(int quesNum);
	Fraction GetAnswer(string expression);
};

class QuestionFive : public Question {		//���꼶����Ŀ
public :
	void ExpGenerate(char modeNum);
};

class QuestionFour : public Question {
public :
	void ExpGenerate(char modeNum);
};

class QuestionThree : public Question {
public:
	void ExpGenerate(char modeNum);
};

#endif