#pragma once

#ifndef __Student_HPP__
#define __Student_HPP__

#include "expression.hpp"

enum e
{
	GradeTh = 3,
	GradeFo,
	GradeFi
};

class Grade {
public:
	e grade;
	char modeNum;
	Grade();
	Grade(e grade);
	virtual void Calculate(int num, char modeNum) = 0;
};

class GradeFive : public Grade {
public :
	QuestionFive ques;
	virtual void Calculate(int num, char modeNum) override;		//����num����Ŀ������
};

class GradeFour : public Grade {
public:
	QuestionFour ques;
	virtual void Calculate(int num, char modeNum) override;
};

class GradeThree : public Grade {
public:
	QuestionThree ques;
	virtual void Calculate(int num, char modeNum) override;
};

#endif