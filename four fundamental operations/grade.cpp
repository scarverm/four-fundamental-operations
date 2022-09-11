#include <iostream>
#include "Student.hpp"

using namespace std;


void GradeFive::Calculate(int num, char modeNum) {
	Ques->SetQuesNum(num);
	Ques->ExpGenerate(modeNum);
}

void GradeFour::Calculate(int num, char modeNum) {
	Ques->SetQuesNum(num);
	Ques->ExpGenerate(modeNum);
}

void GradeThree::Calculate(int num, char modeNum) {
	Ques->SetQuesNum(num);
	Ques->ExpGenerate(modeNum);
}

Grade::Grade() { this->modeNum = '\0'; }

Grade::Grade(e grade) {
	this->grade = grade;
	
}

GradeFive::GradeFive(Language Lang) {
	Ques = new QuestionFive();
	Ques->setLang(Lang);
}

GradeFour::GradeFour(Language Lang) {
	Ques = new QuestionFour();
	Ques->setLang(Lang);
}

GradeThree::GradeThree(Language Lang) {
	Ques = new QuestionFour();
	Ques->setLang(Lang);
}