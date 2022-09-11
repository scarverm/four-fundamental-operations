#include <iostream>
#include "Student.hpp"
#include "Language.hpp"
#include <time.h>
#include <cstring>

using namespace std;

/*����Ҫ��:
* 1.�Զ���������������Ŀ�ʹ�
* 2.����ʽ���������������
* 3.����������1~100֮��
* 4.�𰸲����Ǹ���
*/

/*��չҪ��:
* 1.�ֱ�ʵ��Сѧ�����ġ����꼶�����������Ѷ�	��������ɣ��Ѷȷֱ���ʵ�֣������ֲ���)
* 2.ʹ���������ķ��������û����������������ֲ�ͬ�������ʵ�ֵ�ϸ��
*/

/*�ֱ��������Ҫ��:
* 1.һ�����1000����Ŀ���������ظ����������Ŀд��һ���ļ���
* 2.���10���������������������
* 3.֧�����������������
* 4.���������Ŀ�����û�����𰸣������ж϶Դ��������Դ�����
* 5.����Ĭ��Ϊ���ģ�������3������
*/

int main(int argc, char** argv) {
	/*ͨ���������ʵ�ֲ�ͬ�Ĺ���
	* c��Chinese:���ģ�Ĭ�ϣ� e��English:Ӣ�� f��French:���� g��German:����
	* w:һ�����1000�����ظ�����Ŀ���������Ŀд��һ���ļ���
	* q:�û������,�����ж϶Դ�
	* Ĭ��Ϊ������������ͬʱ�����Ŀ�ʹ�
	* ʹ�õ�����ĸ��Ϊ������Ӧ�ڲ���ǰ���ϡ�-����ʹ������������Ϊ������Ӧ�ڲ���ǰ���ϡ�--��
	*/

	char mode = '\0';
	bool setLang = true, setMode = true;		//��ֹ�������ͬ�����������ͬʱʹ�ò���"c"�Ͳ���"e"����ʾͬʱʹ�����ĺ�Ӣ��
	bool setQues = true;	//���û�����Ĳ���Ϊ'w'��������Ŀ������ļ��У�����Ҫ�û�������Ŀ��������Ŀ�����̶�Ϊ1000
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
						cout << "��������ȷ�Ĳ���" << endl;
						return 0;
					}
					break;
				case 'e':
					if (setLang) {
						lang = "English";
						setLang = false;
					}
					else {
						cout << "��������ȷ�Ĳ���" << endl;
						return 0;
					}
					break;
				case 'f':
					if (setLang) {
						lang = "French";
						setLang = false;
					}
					else {
						cout << "��������ȷ�Ĳ���" << endl;
						return 0;
					}
					break;
				case 'g':
					if (setLang) {
						lang = "German";
						setLang = false;
					}
					else {
						cout << "��������ȷ�Ĳ���" << endl;
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
						cout << "��������ȷ�Ĳ���" << endl;
						return 0;
					}
					break;
				case 'q':
					if (setMode) {
						mode = 'q';
						setMode = false;
					}
					else {
						cout << "��������ȷ�Ĳ���" << endl;
						return 0;
					}
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
				cout << "��������ȷ�Ĳ���" << endl;
				return 0;
			}
		}
	}
	int num;	//Ӧ����������������Ŀ
	int gra;	//�����꼶
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
	srand(unsigned(time(NULL)));		//��������Ӳ��ܷ�����ĺ����У�������ܻᵼ�»����ͬ�������
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
		student = new GradeThree(Lang);		//��ת�Ͷ���
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