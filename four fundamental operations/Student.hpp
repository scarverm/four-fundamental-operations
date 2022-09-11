#pragma once

#ifndef __Student_HPP__
#define __Student_HPP__

#include "expression.hpp"
#include "Language.hpp"

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
	Question *Ques;
	virtual void Calculate(int num, char modeNum) = 0;
};

class GradeFive : public Grade {
public :
	GradeFive(Language Lang);
	virtual void Calculate(int num, char modeNum) override;		//参数num是题目的数量
};

class GradeFour : public Grade {
public:
	GradeFour(Language Lang);
	virtual void Calculate(int num, char modeNum) override;
};

class GradeThree : public Grade {
public:
	GradeThree(Language Lang);
	virtual void Calculate(int num, char modeNum) override;
};

#endif