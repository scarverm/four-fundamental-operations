#pragma once
#ifndef _QUESTION_HPP_
#define _QUESTION_HPP_

#include <fstream>
#include <stack>
#include "grade.hpp"
#include "mode.hpp"
#include "language.hpp"
#include "fraction.hpp"

class Question {
public :
	int quesNum;		//题目数量
	int symbolNum;		//运算符数量，可以看作表达式长度
	int maxOperand;		//最大运算数的值，根据年级的不同有所变化
	int maxSymbolNum;	//最大运算符数量，即最大表达式长度
	grade eGrade;
	Language Lang;

	void SetGrade(grade eGrade);
	void GetSymbolNum(int randomNum, bool fractionMode);			//通过传入一个随机数生成不定的运算符数量
	string GeneSymbol(int randomNum, bool fractionMode);//通过判断mode是否为FRACTION选择输出“÷”还是“/”
	void SetQuesNum(int quesNum);
	bool SetLeftBracket(string& expression, double prob);			//以某一概率生成左括号
	bool SetRightBracket(string& expression, double prob);			//以某一概率生成右括号
	void GeneNum(string& expression);			//随机生成运算数

	void QuestionAndAnswer(string expression, string rightAnswer, int& rightCount, int& falseCount);	//模式1
	void QuestionAndAnswer(string expression, double rightAnswer, int& rightCount, int& falseCount);
	void OutputExpresstion(string expression, string answer, bool& firstWrite);		//模式2
	string randomFraction(int random1, int random2);								//模式3
	void DefaultShow(string expression, string answer);								//默认模式
	void ExpGenerate(Mode mode[], int modeNum = 3);	//三种模式(不包括默认模式)
	Fraction GetAnswer(string expression);
};

#endif // !_QUESTION_HPP_
