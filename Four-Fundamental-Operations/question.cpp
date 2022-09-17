#include "question.hpp"
#include <iostream>
#include <algorithm>

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
	if (ratio <= prob) {
		expression += "(";
		return true;
	}
	return false;
}

bool Question::SetRightBracket(string& expression, double prob) {
	double ratio = (double)rand() / RAND_MAX;
	if (ratio <= prob) {
		expression += ")";
		return true;
	}
	return false;
}

void Question::GeneNum(string& expression) {
	int num = rand() % maxOperand + 1;
	expression += to_string(num);
}

void Question::RemoveExcessBracket(string& expression, bool firstRemove) {

	//÷超出了ASCII码，不能正常显示，应先转换为a，否则在后面会报错“读取字符串字符时出错”
	if (firstRemove) {
		int change = 0;
		for (int i = 0; i < expression.length(); i++) {
			if (
				(expression[i] < '0' || expression[i] > '9')
				&& expression[i] != '+' && expression[i] != '-' && expression[i] != '*' && expression[i] != '/' &&
				expression[i] != '(' && expression[i] != ')'
				) {
				change++;		//在用/替换了不能正常显示的÷后，会多出来一个不能显示的字符，因此要用“”再替换一次
				if (change % 2 == 1) {
					expression.replace(i, 1, "a");	//用一个可以正常显示但又与表达式中其他符号相区别的符号代替
				}
				else {
					expression.replace(i, 1, "");
				}
			}
		}
		firstRemove = false;
	}

	size_t leftBracket, rightBracket;	//左右括号位置
	char leftSymbol = '\0', rightSymbol = '\0';	//括号左右符号
	leftBracket = expression.find_last_of('(');				//最内层左括号
	rightBracket = expression.find(')', leftBracket + 1);	//最内层右括号

	//如果表达式中没有括号，则将中括号替换会小括号，再return
	if (leftBracket == expression.npos) {
		replace(expression.begin(), expression.end(), '[', '(');
		replace(expression.begin(), expression.end(), ']', ')');
		
		//不能用replace函数将a替换为÷，因为编译器将÷识别为int类型
		for (int i = 0; expression[i] != '\0'; i++) {
			if (expression[i] == 'a') {
				expression = expression.substr(0, i) + "÷" + expression.substr(i + 1);
			}
		}
		return;
	}

	if (leftBracket != 0) {
		leftSymbol = expression[leftBracket - 1];
	}
	if (rightBracket != expression.length() - 1) {
		rightSymbol = expression[rightBracket + 1];
	}

	string expWithBracket;
	expWithBracket = expression.substr(leftBracket, rightBracket - leftBracket + 1);
	string subExp;
	subExp = expression.substr(leftBracket + 1, rightBracket - leftBracket - 1);
	//如果括号两边也是括号，可以直接去括号
	if (leftSymbol == '(' && rightSymbol == ')') {
		expression.replace(leftBracket - 1, rightBracket - leftBracket + 3, subExp);
	}

	//+(expression)+ 、+(expression)-、 ((expression)+ 、((expression)- 和 +(expression))形式的都可以直接去括号
	//另外 '\0'(expression)+ 、'\0'(expression)- 和 +(expression)'\0' 的形式也可以直接去括号
	else if (
		(leftSymbol == '+' && (rightSymbol != '/' && rightSymbol != 'a')) ||
		(leftSymbol == '(' && (rightSymbol == '+' || rightSymbol == '-')) ||	//((expression)+ 、((expression)-
		(leftSymbol == '+' && rightSymbol == ')') ||	//+(expression))
		(leftSymbol == '\0' && (rightSymbol == '+' || rightSymbol == '-'))
		) {
		expression.replace(leftBracket, rightBracket - leftBracket + 1, subExp);
	}

	//*(expression) 、((expression)* 、+(expression)* 、-(expression) 、(expression)/ 、(expression)÷形式只有在expression中只有乘和除时才能直接去括号
	//同理'\0'(expression)* 、'\0'(expression)/ 和 '\0'(expression)÷ 也应先判断表达式内符号
	else if (
		(leftSymbol == '-') ||
		(leftSymbol == '*') ||		//*(expression)
		(rightSymbol == '*' && (leftSymbol != '/' && leftSymbol != 'a')) ||
		//((expression)* 、+(expression)* 、-(expression)*
		(rightSymbol == '/') ||		//(expression)/
		(rightSymbol == 'a')		//(expression)÷
		) {
		bool remove = true;
		int squareBracket = 0;				//中途可能遇见[和]此时即使[和]之间有+或-也可以根据情况去括号
		for (int i = 0; i < subExp.length(); i++) {
			if (subExp[i] == '[') {
				squareBracket++;
			}
			else if (subExp[i] == ']') {
				squareBracket--;
			}
			if (squareBracket == 0 && (subExp[i] == '+' || subExp[i] == '-')) {
				remove = false;
				break;
			}
		}
		if (remove) {
			expression.replace(leftBracket, rightBracket - leftBracket + 1, subExp);
		}
		else {		//如果不能直接去括号，则将小括号转为中括号，以便接下来的递归中依旧能找到未处理的最内层括号
			expression.replace(leftBracket, 1, "[");
			expression.replace(rightBracket, 1, "]");
		}
	}

	//如果只剩表达式两边的括号，则取消括号
	else if (leftSymbol == '\0' && rightSymbol == '\0') {
		expression = expression.substr(1, expression.length() - 2);
	}

	//其他情况均不能去括号，将小括号转为中括号
	else {
		expression.replace(leftBracket, 1, "[");
		expression.replace(rightBracket, 1, "]");
	}

	RemoveExcessBracket(expression, firstRemove);
	return;
}

//void Question::RemoveAllBracket(string& expression) {
//	int leftBracket = -1, rightBracket = -1;
//	char leftSymbol = '\0', rightSymbol = '\0';
//	leftBracket = expression.find_last_of('(');
//	rightBracket = expression.find(')', leftBracket + 1);
//	if (leftBracket != 0) {
//		leftSymbol = expression[leftBracket - 1];
//	}
//	if (rightBracket != expression.length() - 1) {
//		rightSymbol = expression[rightBracket + 1];
//	}
//	string frontExp, fullExp;	//frontExp：括号前的表达式，fullExp：带括号的表达式，需要被替换
//
//	//如果表达式中没有括号，就把所有可以改变顺序的数进行排序
//	if (leftBracket == expression.npos) {
//
//	}
//	
//}

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
		if (answer.find('/') == answer.npos) {	//如果答案不是分数形式的，就转为浮点数，这样用cout输出时不会输出多余的0
			double decimalAnswer;
			decimalAnswer = stod(answer);
			outfile << expression << "\t" << Lang.showLang(10) << decimalAnswer << endl;
		}
		else {
			outfile << expression << "\t" << Lang.showLang(10) << answer << endl;
		}
		firstWrite = false;
	}
	else {
		outfile.open(".\\1000questions.txt", ios::app);	//不覆盖写入
		if (answer.find('/') == answer.npos) {
			double decimalAnswer;
			decimalAnswer = stod(answer);
			outfile << expression << "\t" << Lang.showLang(10) << decimalAnswer << endl;
		}
		else {
			outfile << expression << "\t" << Lang.showLang(10) << answer << endl;
		}
	}
	outfile.close();
}

void Question::DefaultShow(string expression, string answer) {
	if (answer.find('/') == answer.npos) {	//如果答案不是分数形式的，就转为浮点数，这样用cout输出时不会输出多余的0
		double decimalAnswer;
		decimalAnswer = stod(answer);
		cout << expression << "\t" << Lang.showLang(10) << decimalAnswer << endl;
	}
	else {
		cout << expression << "\t" << Lang.showLang(10) << answer << endl;
	}
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
	randomFraString ="(" + to_string(randomFra.molecule) + "/" + to_string(randomFra.denominator) + ")";
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
	int change = 0;
	for (int i = 0; i < expression.length(); i++) {		//÷超出了ASCII码，不能正常显示，应先转换为/，否则在后面会报错“读取字符串字符时出错”
		if (
			(expression[i] <'0' || expression[i] > '9') 
			&& expression[i] != '+' && expression[i] != '-' && expression[i] != '*' && expression[i] != '/' &&
			expression[i] != '(' && expression[i] != ')'
			) {
			change++;		//在用/替换了不能正常显示的÷后，会多出来一个不能显示的字符，因此要用“”再替换一次
			if (change % 2 == 1) {
				expression.replace(i, 1, "/");
			}
			else {
				expression.replace(i, 1, "");
			}
		}
	}

	//中缀表达式转为后缀表达式
	stack <char> sta;
	string postexp;
	char ch;
	for (size_t i = 0; expression[i] != '\0'; i++) {
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
			maxOperand = 99;
			break;
		}

		//在表达式的开头以一定概率添加括号
		while (SetLeftBracket(expression, leftProb)) {
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
				while (SetLeftBracket(expression, leftProb)) {
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
				while (right < left && SetRightBracket(expression, rightProb)) {
					right++;
				}
			}
		}
		while (right != left) {		//补全右括号
			expression += ")";
			right++;
		}
		//cout << endl << expression << endl;

		//获得表达式后，应去除多余的括号，因为括号的生成是随机的
		RemoveExcessBracket(expression);
		//cout << expression << endl;

		//计算表达式，获得答案
		Fraction answer = GetAnswer(expression);
		double decimalAnswer = (double)answer.molecule / answer.denominator;	//小数形式的答案
		if (decimalAnswer < 0) {	//跳过答案小于0的题目
			quesNum++;
			expression = "";
			left = right = setRight = 0;
			continue;
		}

		//如果在真分数模式下，表达式答案不是真分数则跳过
		if (fractionMode && answer.molecule >= answer.denominator) {
			quesNum++;
			expression = "";
			left = right = setRight = 0;
			continue;
		}

		//跳过重复的题目
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
