#include <iostream>
#include "Student.hpp"

using namespace std;


void GradeFive::Calculate(int num, char modeNum) {
	ques.SetQuesNum(num);
	ques.ExpGenerate(modeNum);
}

void GradeFour::Calculate(int num, char modeNum) {
	ques.SetQuesNum(num);
	ques.ExpGenerate(modeNum);
}

void GradeThree::Calculate(int num, char modeNum) {
	ques.SetQuesNum(num);
	ques.ExpGenerate(modeNum);
}

Grade::Grade() { this->modeNum = '\0'; }

Grade::Grade(e grade) {
	this->grade = grade;
	
}