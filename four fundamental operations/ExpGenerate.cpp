#include <string>
#include <iostream>
#include <random>
#include <stack>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include "expression.hpp"

using namespace std;

//创建四则运算表达式

void Question::setLang(Language lang) {
	Lang.langType = lang.langType;
}

string Question :: GeneSymbol(int m) {	//随机生成运算符
	switch (m % 4)
	{
	case 0:
		return "+";
		break;
	case 1:
		return "-";
		break;
	case 2:
		return "*";
		break;
	case 3:
		return "/";		//设置为三、四年级使用'÷'，五年级使用'/'
		break;
	}
}

int priority(char c) {
	switch (c)
	{
	case '(':
		return 3;
	case '*':
		return 5;
	case '/':
		return 5;
	case '+':
		return 4;
	case '-':
		return 4;
	}
}

int Gcd(int large, int small) {		//欧几里得算法求最大公约数,large是被除数,small是除数
	if (large < 0) {
		large = -large;
	}
	if (small < 0) {
		small = -small;
	}
	if (large < small) {
		int t = large;
		large = small;
		small = t;
	}
	if (small == 0)
		return large;
	return Gcd(small, large % small);
}

Fraction operator+(const Fraction& F1, const Fraction& F2){
	Fraction result;
	result.denominator = F1.denominator * F2.denominator;
	result.molecule = F1.molecule * F2.denominator + F2.molecule * F1.denominator;
	int gcd = Gcd(result.denominator, result.molecule);		//约分
	result.denominator /= gcd;
	result.molecule /= gcd;
	if (result.denominator < 0) {	//分母如果小于0，就转化到分子上
		result.denominator = -result.denominator;
		result.molecule = -result.molecule;
	}
	return result;
}

Fraction operator-(const Fraction& F1, const Fraction& F2) {	//F1 - F2
	Fraction result;
	result.denominator = F1.denominator * F2.denominator;
	result.molecule = F1.molecule * F2.denominator - F2.molecule * F1.denominator;
	int gcd = Gcd(result.denominator, result.molecule);		//约分
	result.denominator /= gcd;
	result.molecule /= gcd;
	if (result.denominator < 0) {	//分母如果小于0，就转化到分子上
		result.denominator = -result.denominator;
		result.molecule = -result.molecule;
	}
	return result;
}

Fraction operator*(const Fraction& F1, const Fraction& F2) {
	Fraction result;
	result.denominator = F1.denominator * F2.denominator;
	result.molecule = F1.molecule * F2.molecule;
	int gcd = Gcd(result.denominator, result.molecule);		//约分
	result.denominator /= gcd;
	result.molecule /= gcd;
	if (result.denominator < 0) {	//分母如果小于0，就转化到分子上
		result.denominator = -result.denominator;
		result.molecule = -result.molecule;
	}
	return result;
}

Fraction operator/(const Fraction& F1, const Fraction& F2) {	//F1 / F2
	Fraction result;
	result.molecule = F1.molecule * F2.denominator;
	result.denominator = F1.denominator * F2.molecule;
	int gcd = Gcd(result.denominator, result.molecule);		//约分
	result.denominator /= gcd;
	result.molecule /= gcd;
	if (result.denominator < 0) {	//分母如果小于0，就转化到分子上
		result.denominator = -result.denominator;
		result.molecule = -result.molecule;
	}
	return result;
}

bool operator==(const Fraction & F1, const Fraction & F2) {
	return F1.denominator == F2.denominator && F1.molecule == F2.molecule;
}

bool operator!=(const Fraction& F1, const Fraction& F2) {
	return !(F1 == F2);
}



Fraction Question::GetAnswer(string expression) {
	//中缀表达式转为后缀表达式
	stack <char> sta;
	string postexp;
	char ch;
	for (int i = 0; expression[i] != '\0'; i++) {
		if (expression[i] == '(') {
			sta.push(expression[i]);
		}
		else if (expression[i] == ')') {
			while (!sta.empty() && sta.top() != '(') {
				postexp.push_back(sta.top());
				sta.pop();
			}
			sta.pop();
		}
		else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' ||
			expression[i] == '/') {
			while (!sta.empty() && priority(expression[i]) <= priority(sta.top())) {
				ch = sta.top();
				sta.pop();
				postexp.push_back(ch);
			}
			sta.push(expression[i]);
		}
		else {
			postexp.push_back(expression[i]);
			while (expression[i + 1] >= '0' && expression[i + 1] <= '9') {
				i++;
				postexp.push_back(expression[i]);
			}
			postexp.push_back('#');
		}
	}
	while (!sta.empty()) {
		postexp.push_back(sta.top());
		sta.pop();
	}
	//后缀表达式求值
	
	stack <Fraction> s;
	Fraction a, b, c, tmp;
	int d = 0;
	for (int i = 0; postexp[i] != '\0'; i++) {
		if (postexp[i] >= '0' && postexp[i] <= '9') {
			while (postexp[i] != '#') {
				d = d * 10 + (postexp[i] - '0');
				i++;
			}
			tmp.denominator = 1;
			tmp.molecule = d;
			s.push(tmp);
			d = 0;
		}
		else if (postexp[i] == '+') {
			a = s.top();
			s.pop();
			b = s.top();
			s.pop();
			c = a + b;
			s.push(c);
		}
		else if (postexp[i] == '-') {
			b = s.top();	//栈顶元素作减数，下一个元素作被减数
			s.pop();
			a = s.top();
			s.pop();
			c = a - b;
			s.push(c);
		}
		else if (postexp[i] == '*') {
			a = s.top();
			s.pop();
			b = s.top();
			s.pop();
			c = a * b;
			s.push(c);
		}
		else if (postexp[i] == '/') {
			b = s.top();
			s.pop();
			if (fabs(b.molecule) < 1e-6) {
				c.molecule = -1;
				return c;
			}
			a = s.top();
			s.pop();
			c = a / b;
			s.push(c);
		}
	}
	return s.top();
}


void QuestionFive :: ExpGenerate(char modeNum) {			//五年级难度
	string expression;						//表达式
	srand((unsigned)time(NULL));	//用系统时间初始化时钟,生成不同的随机数种子
	int operand;							//运算数
	int symbolNum;							//运算符个数

	int left = 0;			//左括号数量
	int right = 0;			//右括号数量
	int setRight = 0;	//当左、右括号数量相等时，或当括号内只包含了一个运算数时，不应添加右括号
						//setRight >= 2 时表示此时可以加上又括号
	bool firstWrite = true;		//第一次写入文件时覆盖原内容，后续写入则不覆盖
	int falseAnswer = 0, rightAnswer = 0;	//统计用户输入答案的对错
	vector<double> v;

	for (int i = 0; i < quesNum; i++) {
		symbolNum = rand() % (11 - 6 + 1) + 3;	//运算式长度: 6~11
		operand = rand() % 100 + 1;
		if (rand() % 2 == 1) {	//rand()返回0到最大随机数的任意整数，rand() % 2只有1和0两种取值 
			expression += "(";	// 以1/2的概率添加括号
			left++;
		}
		expression += to_string(operand);
		if (left > 0) {
			setRight++;
		}

		for (int j = 0; j < symbolNum; j++) {
			string tmp;
			//因为表达式中运算数和运算符是交叉排列的，因此可以采用交叉生成运算数和运算符的方法生成表达式
			expression += GeneSymbol(rand());
			if ((j < symbolNum - 1) && (rand() % 2 == 1)) {
				expression += "(";
				left++;
				setRight = 0;
			}
			operand = rand() % 100 + 1;
			expression += to_string(operand);
			if (right < left && (rand() % 2 == 1) && setRight >= 2) {
				expression += ")";
				right++;
			}
			if (left > right) {
				setRight++;
			}
		}
		while (right != left) {
			expression += ")";
			right++;
		}
		Fraction answer = GetAnswer(expression);
		double decimalFraction = (double)answer.molecule / answer.denominator;
		if (decimalFraction < 0) {
			quesNum++;
		}
		else {
			if (modeNum == 'w') {		//一次输出1000道题目，不允许重复，输出的题目写入一个文件中
				vector<double>::iterator fi = find(v.begin(), v.end(), decimalFraction);
				if (fi == v.end()) {
					v.push_back(decimalFraction);
					ofstream outfile;
					if (firstWrite) {
						outfile.open(".\\1000questions.txt");		//覆盖写入
						firstWrite = false;
					}
					else {
						outfile.open(".\\1000questions.txt", ios::app);		//不覆盖写入
					}
					outfile << expression << endl;
					outfile.close();
				}
				else {
					quesNum++;
				}
				expression = "";
				left = right = setRight = 0;
				continue;
			}
			else if (modeNum == 'q') {
				cout << expression << endl;
				cout << Lang.showLang(4) << endl;
				double userAnswer1 = 0;
				Fraction userAnswer2;
				string tmp;
				cin >> tmp;
				if (tmp.find('/') == tmp.npos) {
					userAnswer1 = stod(tmp);
				}
				else {
					userAnswer2.molecule = atoi(tmp.c_str());
					size_t len = tmp.length() - tmp.find('/');
					string subs = tmp.substr(tmp.find('/') + 1, len);
					userAnswer2.denominator = atoi(subs.c_str());
				}
				if ((abs(userAnswer1 - decimalFraction) < 1e-2) || (userAnswer2 == answer)) {
					cout << Lang.showLang(5) << endl;
					rightAnswer++;
					cout << Lang.showLang(6) << rightAnswer << "\t" << Lang.showLang(7) << falseAnswer << endl;
				}
				else {
					cout << Lang.showLang(8) << decimalFraction;
					if (answer.denominator != 1) {		//如果答案可以是分数，就输出分数
						cout << "  " << Lang.showLang(9) << "  " << answer.molecule << "/" << answer.denominator << endl;
						cout << endl;
					}
					else {
						cout << endl;
					}
					falseAnswer++;
					cout << Lang.showLang(6) << rightAnswer << "\t" << Lang.showLang(7) << falseAnswer << endl;
				}
				expression = "";
				left = right = setRight = 0;
				continue;
			}
			cout << expression << "\t" << decimalFraction;
			if (answer.denominator != 1) {		//如果答案可以是分数，就输出分数
				cout << "  " << Lang.showLang(9) << "  " << answer.molecule << "/" << answer.denominator << endl;
				cout << endl;
			}
			else {
				cout << endl;
			}
		}
		
		expression = "";
		left = right = setRight = 0;
	}
}

void QuestionFour::ExpGenerate(char modeNum) {			//四年级难度
	string expression;						//表达式
	srand((unsigned)time(NULL));	//用系统时间初始化时钟,生成不同的随机数种子
	int operand;							//运算数
	int symbolNum;							//运算符个数

	int left = 0;			//左括号数量
	int right = 0;			//右括号数量
	int setRight = 0;	//当左、右括号数量相等时，或当括号内只包含了一个运算数时，不应添加右括号
						//setRight >= 2 时表示此时可以加上又括号

	bool firstWrite = true;
	int falseAnswer = 0, rightAnswer = 0;
	vector<double> v;

	for (int i = 0; i < quesNum; i++) {
		symbolNum = rand() % (8 - 5 + 1) + 3;		//缩短运算式长度: 5~8
		operand = rand() % 100 + 1;
		if (rand() % 3 == 1) {	//rand()返回0到最大随机数的任意整数，rand() % 2只有1和0两种取值 
			expression += "(";	//以1/3的概率添加括号
			left++;
		}
		expression += to_string(operand);
		if (left > 0) {
			setRight++;
		}
		for (int j = 0; j < symbolNum; j++) {
			//因为表达式中运算数和运算符是交叉排列的，因此可以采用交叉生成运算数和运算符的方法生成表达式
			expression += GeneSymbol(rand());
			if ((j < symbolNum - 1) && (rand() % 3 == 1)) {
				expression += "(";
				left++;
				setRight = 0;
			}
			operand = rand() % 100 + 1;
			expression += to_string(operand);
			if (right < left && (rand() % 2 == 1) && setRight >= 2) {
				expression += ")";
				right++;
			}
			if (left > right) {
				setRight++;
			}
		}
		while (right != left) {
			expression += ")";
			right++;
		}
		Fraction answer = GetAnswer(expression);
		double decimalFraction = (double)answer.molecule / answer.denominator;
		
		if (decimalFraction < 0) {
			quesNum++;
		}
		else {
			if (modeNum == 'w') {		//一次输出1000道题目，不允许重复，输出的题目写入一个文件中
				auto fi = find(v.begin(), v.end(), decimalFraction);
				if (fi == v.end()) {
					v.push_back(decimalFraction);
					ofstream outfile;
					if (firstWrite) {
						outfile.open(".\\1000questions.txt");		//覆盖写入
						firstWrite = false;
					}
					else {
						outfile.open(".\\1000questions.txt", ios::app);		//不覆盖写入
					}
					outfile << expression << endl;
					outfile.close();
				}
				else {
					quesNum++;
				}
				expression = "";
				left = right = setRight = 0;
				continue;
			}
			else if (modeNum == 'q') {
				cout << expression << endl;
				cout << Lang.showLang(4) << endl;
				double userAnswer1 = 0;
				Fraction userAnswer2;
				string tmp;
				cin >> tmp;
				if (tmp.find('/') == tmp.npos) {
					userAnswer1 = stod(tmp);
				}
				else {
					userAnswer2.molecule = atoi(tmp.c_str());
					size_t len = tmp.length() - tmp.find('/');
					string subs = tmp.substr(tmp.find('/') + 1, len);
					userAnswer2.denominator = atoi(subs.c_str());
				}
				if (abs(userAnswer1 - decimalFraction) < 1e-2 || userAnswer2 == answer) {
					cout << Lang.showLang(5) << endl;
					rightAnswer++;
					cout << Lang.showLang(6) << rightAnswer << "\t" << Lang.showLang(7) << falseAnswer << endl;
				}
				else {
					cout << Lang.showLang(8) << decimalFraction;
					if (answer.denominator != 1) {		//如果答案可以是分数，就输出分数
						cout << "  " << Lang.showLang(9) << "  " << answer.molecule << "/" << answer.denominator << endl;
						cout << endl;
					}
					else {
						cout << endl;
					}
					falseAnswer++;
					cout << Lang.showLang(6) << rightAnswer << "\t" << Lang.showLang(7) << falseAnswer << endl;
				}
				expression = "";
				left = right = setRight = 0;
				continue;
			}
			cout << expression << "\t" << decimalFraction;
			if (answer.denominator != 1) {		//如果答案可以是分数，就输出分数
				cout << "  " << Lang.showLang(9) << "  " << answer.molecule << "/" << answer.denominator << endl;
				cout << endl;
			}
			else {
				cout << endl;
			}
		}
		expression = "";
		left = right = setRight = 0;
	}
}

void QuestionThree::ExpGenerate(char modeNum) {			//三年级难度
	string expression;						//表达式
	srand((unsigned)time(NULL));	//用系统时间初始化时钟,生成不同的随机数种子
	int operand;							//运算数
	int symbolNum;							//运算符个数

	int left = 0;			//左括号数量
	int right = 0;			//右括号数量
	int setRight = 0;	//当左、右括号数量相等时，或当括号内只包含了一个运算数时，不应添加右括号
						//setRight >= 2 时表示此时可以加上又括号

	bool firstWrite = true;
	int falseAnswer = 0, rightAnswer = 0;
	vector<double> v;

	for (int i = 0; i < quesNum; i++) {
		symbolNum = rand() % (5 - 3 + 1) + 3;		//缩短运算式长度: 3~5
		operand = rand() % 100 + 1;
		if (rand() % 4 == 1) {	//rand()返回0到最大随机数的任意整数，rand() % 2只有1和0两种取值 
			expression += "(";	//以1/4的概率添加括号
			left++;
		}
		expression += to_string(operand);
		if (left > 0) {
			setRight++;
		}
		for (int j = 0; j < symbolNum; j++) {
			//因为表达式中运算数和运算符是交叉排列的，因此可以采用交叉生成运算数和运算符的方法生成表达式
			expression += GeneSymbol(rand());
			if ((j < symbolNum - 1) && (rand() % 4 == 1)) {
				expression += "(";
				left++;
				setRight = 0;
			}
			operand = rand() % 100 + 1;
			expression += to_string(operand);
			if (right < left && (rand() % 2 == 1) && setRight >= 2) {
				expression += ")";
				right++;
			}
			if (left > right) {
				setRight++;
			}
		}
		while (right != left) {
			expression += ")";
			right++;
		}
		Fraction answer = GetAnswer(expression);
		double decimalFraction = (double)answer.molecule / answer.denominator;
		
		if (decimalFraction < 0) {
			quesNum++;
		}
		else {
			if (modeNum == 'w') {		//一次输出1000道题目，不允许重复，输出的题目写入一个文件中
				auto fi = find(v.begin(), v.end(), decimalFraction);
				if (fi == v.end()) {
					v.push_back(decimalFraction);
					ofstream outfile;
					if (firstWrite) {
						outfile.open(".\\1000questions.txt");		//覆盖写入
						firstWrite = false;
					}
					else {
						outfile.open(".\\1000questions.txt", ios::app);		//不覆盖写入
					}
					outfile << expression << endl;
					outfile.close();
				}
				else {
					quesNum++;
				}
				expression = "";
				left = right = setRight = 0;
				continue;
			}
			else if (modeNum == 'q') {
				cout << expression << endl;
				cout << Lang.showLang(4) << endl;
				double userAnswer1 = 0;
				Fraction userAnswer2;
				string tmp;
				cin >> tmp;
				if (tmp.find('/') == tmp.npos) {
					userAnswer1 = stod(tmp);
				}
				else {
					userAnswer2.molecule = atoi(tmp.c_str());
					size_t len = tmp.length() - tmp.find('/');
					string subs = tmp.substr(tmp.find('/') + 1, len);
					userAnswer2.denominator = atoi(subs.c_str());
				}
				if (abs(userAnswer1 - decimalFraction) < 1e-2 || userAnswer2 == answer) {
					cout << Lang.showLang(5) << endl;
					rightAnswer++;
					cout << Lang.showLang(6) << rightAnswer << "\t" << Lang.showLang(7) << falseAnswer << endl;
				}
				else {
					cout << Lang.showLang(8) << decimalFraction;
					if (answer.denominator != 1) {		//如果答案可以是分数，就输出分数
						cout << "  " << Lang.showLang(9) << "  " << answer.molecule << "/" << answer.denominator << endl;
						cout << endl;
					}
					else {
						cout << endl;
					}
					falseAnswer++;
					cout << Lang.showLang(6) << rightAnswer << "\t" << Lang.showLang(7) << falseAnswer << endl;
				}
				expression = "";
				left = right = setRight = 0;
				continue;
			}
			cout << expression << "\t" << decimalFraction;
			if (answer.denominator != 1) {		//如果答案可以是分数，就输出分数
				cout << "  " << Lang.showLang(9) << "  " << answer.molecule << "/" << answer.denominator << endl;
				cout << endl;
			}
			else {
				cout << endl;
			}
		}
		expression = "";
		left = right = setRight = 0;
	}
}

void Question :: SetQuesNum(int quesNum) {
	this->quesNum = quesNum;
}