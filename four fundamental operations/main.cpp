#include <iostream>
#include "Student.hpp"
#include "Language.hpp"
#include <time.h>
#include <cstring>

using namespace std;

/*具体要求:
* 1.自动生成四则运算题目和答案
* 2.运算式至少有两个运算符
* 3.运算数字在1~100之内
* 4.答案不能是负数
*/

/*扩展要求:
* 1.分别实现小学三、四、五年级的四则运算难度	（部分完成：难度分别已实现，但区分不大)
* 2.使用面向对象的方法，运用基类和子类来管理各种不同的需求和实现的细节
*/

/*分别完成以下要求:
* 1.一次输出1000道题目，不允许重复，输出的题目写入一个文件中
* 2.最多10个运算符，括号数量不限
* 3.支持真分数的四则运算
* 4.程序给出题目，由用户输入答案，程序判断对错，最后给出对错总数
* 5.程序默认为中文，并加入3国语言
*/

int main(int argc, char** argv) {
	/*通过输入参数实现不同的功能
	* c、Chinese:中文（默认） e、English:英文 f、French:法语 g、German:德语
	* w:一次输出1000道不重复的题目，输出的题目写入一个文件中
	* q:用户输入答案,程序判断对错
	* 默认为程序在命令行同时输出题目和答案
	* 使用单个字母作为参数，应在参数前加上“-”；使用完整单词作为参数，应在参数前加上“--”
	*/

	char mode = '\0';
	bool setLang = true, setMode = true;		//防止多次输入同类参数，例如同时使用参数"c"和参数"e"，表示同时使用中文和英文
	bool setQues = true;	//当用户输入的参数为'w'，即将题目输出到文件中，则不需要用户输入题目数量，题目数量固定为1000
	string lang;
	for (int i = 1, j = 0; i < argc; i++, j = 0) {
		if (argv[i][0] == '-' && argv[i][1] != '-') {
			j = 1;
			while (argv[i][j] != '\0') {
				switch (argv[i][j])
				{
				case 'c':
					if (setLang) {
						lang = "Chinese";
						setLang = false;
					}
					else {
						cout << "请输入正确的参数" << endl;
						return 0;
					}
					break;
				case 'e':
					if (setLang) {
						lang = "English";
						setLang = false;
					}
					else {
						cout << "请输入正确的参数" << endl;
						return 0;
					}
					break;
				case 'f':
					if (setLang) {
						lang = "French";
						setLang = false;
					}
					else {
						cout << "请输入正确的参数" << endl;
						return 0;
					}
					break;
				case 'g':
					if (setLang) {
						lang = "German";
						setLang = false;
					}
					else {
						cout << "请输入正确的参数" << endl;
						return 0;
					}
					break;
				case 'w':
					if (setMode) {
						mode = 'w';
						setMode = false;
						setQues = false;
					}
					else {
						cout << "请输入正确的参数" << endl;
						return 0;
					}
					break;
				case 'q':
					if (setMode) {
						mode = 'q';
						setMode = false;
					}
					else {
						cout << "请输入正确的参数" << endl;
						return 0;
					}
					break;
				default:
					cout << "请输入正确的参数" << endl;
					return 0;
					break;
				}
				j++;
			}
		}
		else if (argv[i][0] == '-' && argv[i][1] == '-') {
			char* index = argv[i];
			index = index + 2;
			if (strcmp("Chinese", index) == 0 && setLang) {
				setLang = false;
				lang = "Chinese";
			}
			else if (strcmp("English", index) == 0 && setLang) {
				setLang = false;
				lang = "English";
			}
			else if (strcmp("French", index) == 0 && setLang) {
				setLang = false;
				lang = "French";
			}
			else if (strcmp("German", index) == 0 && setLang) {
				setLang = false;
				lang = "German";
			}
			else {
				cout << "请输入正确的参数" << endl;
				return 0;
			}
		}
	}
	int num;	//应输出的四则运算的数目
	int gra;	//输入年级
	e grade;
	Language Lang;
	if (lang == "English") {
		Lang.setLang(1);
	}
	else if (lang == "French") {
		Lang.setLang(2);
	}
	else if (lang == "German") {
		Lang.setLang(3);
	}
	else {
		Lang.setLang(0);
	}
	srand(unsigned(time(NULL)));		//随机数种子不能放在类的函数中，否则可能会导致获得相同的随机数
	cout << Lang.showLang(0) << endl;
	cin >> gra;
	while (gra != 3 && gra != 4 && gra != 5) {
		cout << Lang.showLang(1) << endl;
		cin >> gra;
	}
	switch (gra)
	{
	case 3:
		grade = GradeTh;
		break;
	case 4:
		grade = GradeFo;
		break;
	case 5:
		grade = GradeFi;
		break;
	}

	if (setQues) {
		cout << Lang.showLang(2) << endl;
		cin >> num;
		while (num <= 0) {
			cout << Lang.showLang(3) << endl;
			cin >> num;
		}
	}
	else {
		num = 1000;
	}
	
	Grade* student = nullptr;
	switch (grade)
	{
	case GradeTh:
		student = new GradeThree(Lang);		//上转型对象
		break;
	case GradeFo:
		student = new GradeFour(Lang);
		break;
	case GradeFi:
		student = new GradeFive(Lang);
		break;
	}
	

	student->Calculate(num, mode);

	getchar();
	delete student;
	return 0;
}