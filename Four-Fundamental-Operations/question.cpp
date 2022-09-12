#include "question.hpp"
#include <iostream>

void Question::SetGrade(grade eGrade){
	this->eGrade = eGrade;
}

void Question::GetSymbolNum(int randomNum, bool fractionMode){
	if (fractionMode) {			//����������ģʽ�����������������
		randomNum /= 2;
	}
	symbolNum = randomNum;
}

void Question::SetQuesNum(int quesNum){
	this->quesNum = quesNum;
}

bool Question::SetLeftBracket(string& expression, double prob) {
	double ratio = (double) rand() / RAND_MAX;		//��ȡ0~1��С��
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
	if (abs(userAnswer - rightAnswer) < 1e-2) {		//������С�������λ
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
		outfile.open(".\\1000questions.txt");			//����д��
		outfile << expression << "\t" << Lang.showLang(10) << answer << endl;
		firstWrite = false;
	}
	else {
		outfile.open(".\\1000questions.txt", ios::app);	//������д��
		outfile << expression << "\t" << Lang.showLang(10) << answer << endl;
	}
	outfile.close();
}

void Question::DefaultShow(string expression, string answer) {
	cout << expression << "\t" << Lang.showLang(10) << answer << endl;
}

string Question::randomFraction(int random1, int random2)
{
	if (random1 > random2) {		//��֤���ӱȷ�ĸС
		int t = random1;
		random1 = random2;
		random2 = t;
	}
	if (random1 == random2) {		//��֤�������ĸ�����
		random2 += 1;
	}
	Fraction randomFra;
	randomFra.molecule = random1;
	randomFra.denominator = random2;
	int gcd = Gcd::Gcd(randomFra.denominator, randomFra.molecule);		//Լ��
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
	case '��':
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
	//��׺���ʽתΪ��׺���ʽ
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
			expression[i] == '/' || expression[i] == '��') {
			if (expression[i] == '��') {
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
	//��׺���ʽ��ֵ

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
			b = s.top();	//ջ��Ԫ������������һ��Ԫ����������
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

string Question::GeneSymbol(int randomNum, bool fractionMode) {	//������������
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
			return "��";		//������¡���Ϊ��ʹ���ʽ�еķ�������������
		}
		else {
			return "/";
		}
	}
}

void Question::ExpGenerate(Mode mode[], int modeNum){
	//���ñ�־λ
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

	//�������
	string expression;			//���ʽ
	int left = 0, right = 0;	//������������
	int setRight = 0;			//�������������ʱ����������ֻ������һ��������ʱ����Ӧ���������
								//setRight >= 2 ʱ��ʾ��ʱ���Լ���������
	bool firstWrite = true;		//��һ��д���ļ�ʱ����ԭ���ݣ�����д���򲻸���
	int falseCount = 0, rightCount = 0;	//ͳ���û�����𰸵ĶԴ�
	double leftProb = 0, rightProb = 0;	//����������ŵĸ���
	vector<double> noRepetition;//���1000����Ŀ���ļ�Ҫ����Ŀ���ظ�

	for (int i = 0; i < quesNum; i++) {
		//���������������������ŵĸ���
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

		//�ڱ��ʽ�Ŀ�ͷ��һ�������������
		if (SetLeftBracket(expression, leftProb)) {
			left++;
			setRight = 0;
		}

		//���ɵ�һ�������������ݲ�ͬģʽ�������������������ʽ��������
		if (fractionMode) {
			expression += randomFraction(rand() % maxOperand + 1, rand() % maxOperand + 1);
		}
		else {
			GeneNum(expression);
		}
		setRight++;

		//��Ϊ���ʽ����������������ǽ������еģ���˲��ý���������������������ķ������ɱ��ʽ
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
		while (right != left) {		//��ȫ������
			expression += ")";
			right++;
		}

		//������ʽ����ô�
		Fraction answer = GetAnswer(expression);
		double decimalAnswer = (double)answer.molecule / answer.denominator;	//С����ʽ�Ĵ�
		if (decimalAnswer < 0) {	//������С��0����Ŀ
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

		//���ݲ�ͬģʽ���в�ͬ����
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
