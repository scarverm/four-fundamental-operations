#include "question.hpp"
#include <iostream>

void Question::SetGrade(grade eGrade){
	this->eGrade = eGrade;
}

void Question::GetSymbolNum(int randomNum, bool fractionMode){
	if (fractionMode) {			//如果是真分数模式，则运算符数量减半
		randomNum /= 2;
	}
	symbolNum = randomNum;
}

void Question::SetQuesNum(int quesNum){
	this->quesNum = quesNum;
}

bool Question::SetLeftBracket(string& expression, double prob) {
	double ratio = (double) rand() / RAND_MAX;		//获取0~1的小数
	if (abs(ratio) <= prob) {
		expression += "(";
		return true;
	}
	return false;
}

bool Question::SetRightBracket(string& expression, double prob) {
	double ratio = (double)rand() / RAND_MAX;
	if (abs(ratio) <= prob) {
		expression += ")";
		return true;
	}
	return false;
}

void Question::GeneNum(string& expression) {
	int num = rand() % maxOperand + 1;
	expression += to_string(num);
}

void Question::QuestionAndAnswer(string expression, string rightAnswer, int& rightCount, int& falseCount){
	cout << expression << endl;
	string userAnswer;
	cout << Lang.showLang(4) << endl;
	cin >> userAnswer;
	if (rightAnswer == userAnswer) {
		cout << Lang.showLang(5) << endl;
		rightCount++;
	}
	else {
		cout << Lang.showLang(8) << rightAnswer << endl;
		falseCount++;
	}
	cout << Lang.showLang(6) << rightCount << "\t" << Lang.showLang(7) << falseCount << endl << endl;
}

void Question::QuestionAndAnswer(string expression, double rightAnswer, int& rightCount, int& falseCount) {
	cout << expression << endl;
	double userAnswer;
	cout << Lang.showLang(4) << endl;
	cin >> userAnswer;
	if (abs(userAnswer - rightAnswer) < 1e-2) {		//精度在小数点后两位
		cout << Lang.showLang(5) << endl;
		rightCount++;
	}
	else {
		cout << Lang.showLang(8) << rightAnswer << endl;
		falseCount++;
	}
	cout << Lang.showLang(6) << rightCount << "\t" << Lang.showLang(7) << falseCount << endl << endl;
}

void Question::OutputExpresstion(string expression, string answer, bool& firstWrite){
	ofstream outfile;
	if (firstWrite) {
		outfile.open(".\\1000questions.txt");			//覆盖写入
		outfile << expression << "\t" << Lang.showLang(10) << answer << endl;
		firstWrite = false;
	}
	else {
		outfile.open(".\\1000questions.txt", ios::app);	//不覆盖写入
		outfile << expression << "\t" << Lang.showLang(10) << answer << endl;
	}
	outfile.close();
}

void Question::DefaultShow(string expression, string answer) {
	cout << expression << "\t" << Lang.showLang(10) << answer << endl;
}

string Question::randomFraction(int random1, int random2)
{
	if (random1 > random2) {		//保证分子比分母小
		int t = random1;
		random1 = random2;
		random2 = t;
	}
	if (random1 == random2) {		//保证分子与分母不相等
		random2 += 1;
	}
	Fraction randomFra;
	randomFra.molecule = random1;
	randomFra.denominator = random2;
	int gcd = Gcd::Gcd(randomFra.denominator, randomFra.molecule);		//约分
	randomFra.denominator /= gcd;
	randomFra.molecule /= gcd;
	string randomFraString;
	randomFraString = to_string(random1) + "/" + to_string(random2);
	return randomFraString;
}

int priority(char c) {
	switch (c)
	{
	case '(':
		return 3;
	case '*':
		return 5;
	case '÷':
		return 5;
	case '/':
		return 5;
	case '+':
		return 4;
	case '-':
		return 4;
	}
}

Fraction Question::GetAnswer(string expression)
{
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
			expression[i] == '/' || expression[i] == '÷') {
			if (expression[i] == '÷') {
				expression[i] = '/';
			}
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

string Question::GeneSymbol(int randomNum, bool fractionMode) {	//随机生成运算符
	switch (randomNum % 4)
	{
	case 0:
		return "+";
	case 1:
		return "-";
	case 2:
		return "*";
	case 3:
		if (fractionMode) {
			return "÷";		//输出“÷”是为了使表达式中的分数看起来明显
		}
		else {
			return "/";
		}
	}
}

void Question::ExpGenerate(Mode mode[], int modeNum){
	//设置标志位
	bool queryMode, outputMode, fractionMode;
	queryMode = outputMode = fractionMode = false;
	for (int i = 0; i < modeNum; i++) {
		switch (mode[i])
		{
		case QUERY:
			queryMode = true;
			break;
		case OUTPUT:
			outputMode = true;
			break;
		case FRACTION:
			fractionMode = true;
			break;
		}
	}

	//定义变量
	string expression;			//表达式
	int left = 0, right = 0;	//左、右括号数量
	int setRight = 0;			//当左、右数量相等时，或当括号内只包含了一个运算数时，不应添加右括号
								//setRight >= 2 时表示此时可以加上右括号
	bool firstWrite = true;		//第一次写入文件时覆盖原内容，后续写入则不覆盖
	int falseCount = 0, rightCount = 0;	//统计用户输入答案的对错
	double leftProb = 0, rightProb = 0;	//添加左、右括号的概率
	vector<double> noRepetition;//输出1000道题目到文件要求题目不重复

	for (int i = 0; i < quesNum; i++) {
		//获得运算符数量和生成括号的概率
		switch (eGrade)
		{
		case THREE:
			GetSymbolNum(rand() % (6 - 3 + 1) + 3, fractionMode);		//3~6
			leftProb = rightProb = 0.25;
			maxOperand = 20;
			break;
		case FOUR:
			GetSymbolNum(rand() % (8 - 5 + 1) + 5, fractionMode);		//5~8
			leftProb = rightProb = 0.33;
			maxOperand = 50;
			break;
		case FIVE:
			GetSymbolNum(rand() % (10 - 7 + 1) + 7, fractionMode);		//7~10
			leftProb = rightProb = 0.5;
			maxOperand = 100;
			break;
		}

		//在表达式的开头以一定概率添加括号
		if (SetLeftBracket(expression, leftProb)) {
			left++;
			setRight = 0;
		}

		//生成第一个运算数，根据不同模式，生成整数或真分数形式的运算数
		if (fractionMode) {
			expression += randomFraction(rand() % maxOperand + 1, rand() % maxOperand + 1);
		}
		else {
			GeneNum(expression);
		}
		setRight++;

		//因为表达式中运算数和运算符是交叉排列的，因此采用交叉生成运算数和运算符的方法生成表达式
		for (int j = 0; j < symbolNum; j++) {
			expression += GeneSymbol(rand(), fractionMode);
			if (j < symbolNum - 1) {
				if (SetLeftBracket(expression, leftProb)) {
					left++;
					setRight = 0;
				}
			}
			if (fractionMode) {
				expression += randomFraction(rand() % maxOperand + 1, rand() % maxOperand + 1);
			}
			else {
				GeneNum(expression);
			}
			setRight++;
			if (right < left && setRight >= 2) {
				if (SetRightBracket(expression, rightProb)) {
					right++;
				}
			}
		}
		while (right != left) {		//补全右括号
			expression += ")";
			right++;
		}

		//计算表达式，获得答案
		Fraction answer = GetAnswer(expression);
		double decimalAnswer = (double)answer.molecule / answer.denominator;	//小数形式的答案
		if (decimalAnswer < 0) {	//跳过答案小于0的题目
			quesNum++;
			expression = "";
			left = right = setRight = 0;
			continue;
		}
		auto fi = find(noRepetition.begin(), noRepetition.end(), decimalAnswer);
		if (fi != noRepetition.end()) {
			quesNum++;
			expression = "";
			left = right = setRight = 0;
			continue;
		}

		//根据不同模式进行不同处理
		if (fractionMode) {
			string tmp;
			tmp = to_string(answer.molecule) + "/" + to_string(answer.denominator);
			if (outputMode) {
				OutputExpresstion(expression, tmp, firstWrite);
			}
			if (queryMode) {
				QuestionAndAnswer(expression, tmp, rightCount, falseCount);
			}
			else if (!queryMode) {
				DefaultShow(expression, tmp);
			}
		}
		else {
			if (outputMode) {
				OutputExpresstion(expression, to_string(decimalAnswer), firstWrite);
			}
			if (queryMode) {
				QuestionAndAnswer(expression, decimalAnswer, rightCount, falseCount);
			}
			else if (!queryMode) {
				DefaultShow(expression, to_string(decimalAnswer));
			}
		}
		expression = "";
		left = right = setRight = 0;
	}
}
