#include <iostream>
#include "question.hpp"

using namespace std;

int main(int argc, char** argv) {
	//��ȡ�����в���
	//��ȷ�Ĳ�����:o��q��f��Chinese��English��French��German������ĸ����ǰӦ��һ����-�������ʲ���ǰӦ��������-��
	Mode mode[3]{DEFAULT};
	int modeIndex = 0;
	bool setLang = true;	//����Ӧֻѡһ��
	LangType langType = CHINESE;
	for (int i = 1, j = 0; i < argc; i++, j = 0) {
		if (argv[i][0] == '-' && argv[i][1] != '-') {
			j = 1;
			while (argv[i][j] != '\0') {
				switch (argv[i][j])
				{
				case 'o':
					mode[0] = OUTPUT;
					break;
				case 'q':
					mode[1] = QUERY;
					break;
				case 'f':
					mode[2] = FRACTION;
					break;
				default:
					cout << "��������ȷ�Ĳ���" << endl;
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
				langType = CHINESE;
			}
			else if (strcmp("English", index) == 0 && setLang) {
				setLang = false;
				langType = ENGLISH;
			}
			else if (strcmp("French", index) == 0 && setLang) {
				setLang = false;
				langType = FRENCH;
			}
			else if (strcmp("German", index) == 0 && setLang) {
				setLang = false;
				langType = GERMAN;
			}
			else {
				cout << "��������ȷ�Ĳ���" << endl;
				return 0;
			}
		}
	}

	//��������
	Question ques;
	ques.Lang.setLang(langType);

	//�����꼶���Ѷȣ�
	int gradeNum;
	bool setGrade = true;		//ȷ���������꼶
	cout << ques.Lang.showLang(0) << endl;
	while (setGrade) {
		cin >> gradeNum;
		switch (gradeNum)
		{
		case 3:
			ques.SetGrade(THREE);
			setGrade = false;
			break;
		case 4:
			ques.SetGrade(FOUR);
			setGrade = false;
			break;
		case 5:
			ques.SetGrade(FIVE);
			setGrade = false;
			break;
		default:
			cout << ques.Lang.showLang(1) << endl;
			break;
		}
	}

	//������Ŀ����
	if (mode[0] == OUTPUT) {
		ques.SetQuesNum(1000);
	}
	else {
		bool setQuesNum = true;
		cout << ques.Lang.showLang(2) << endl;
		while (setQuesNum) {
			int quesNum;
			cin >> quesNum;
			if (quesNum > 0) {
				ques.SetQuesNum(quesNum);
				setQuesNum = false;
			}
			else {
				cout << ques.Lang.showLang(3) << endl;
			}
		}
	}

	//���г���
	srand(unsigned(time(NULL)));	//��ȡ��������ӣ���������������������ĳ�Ա�������ֹ���ɵ��������ͬ
	ques.ExpGenerate(mode, 3);

	system("pause");
	return 0;
}