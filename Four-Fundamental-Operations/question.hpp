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
	int quesNum;		//��Ŀ����
	int symbolNum;		//��������������Կ������ʽ����
	int maxOperand;		//�����������ֵ�������꼶�Ĳ�ͬ�����仯
	int maxSymbolNum;	//���������������������ʽ����
	grade eGrade;
	Language Lang;

	void SetGrade(grade eGrade);
	void GetSymbolNum(int randomNum, bool fractionMode);			//ͨ������һ����������ɲ��������������
	string GeneSymbol(int randomNum, bool fractionMode);//ͨ���ж�mode�Ƿ�ΪFRACTIONѡ��������¡����ǡ�/��
	void SetQuesNum(int quesNum);
	bool SetLeftBracket(string& expression, double prob);			//��ĳһ��������������
	bool SetRightBracket(string& expression, double prob);			//��ĳһ��������������
	void GeneNum(string& expression);			//�������������

	void QuestionAndAnswer(string expression, string rightAnswer, int& rightCount, int& falseCount);	//ģʽ1
	void QuestionAndAnswer(string expression, double rightAnswer, int& rightCount, int& falseCount);
	void OutputExpresstion(string expression, string answer, bool& firstWrite);		//ģʽ2
	string randomFraction(int random1, int random2);								//ģʽ3
	void DefaultShow(string expression, string answer);								//Ĭ��ģʽ
	void ExpGenerate(Mode mode[], int modeNum = 3);	//����ģʽ(������Ĭ��ģʽ)
	Fraction GetAnswer(string expression);
};

#endif // !_QUESTION_HPP_
