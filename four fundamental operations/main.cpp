#include <iostream>
#include "Student.hpp"
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
	for (int i = 1, j = 0; i < argc; i++, j = 0) {
		if (argv[i][0] == '-' && argv[i][1] != '-') {
			j = 1;
			while (argv[i][j] != '\0') {
				switch (argv[i][j])
				{
				case 'c':
					if (setLang) {

						setLang = false;
					}
					else {
						cout << "��������ȷ�Ĳ���" << endl;
						return 0;
					}
					cout << "ccc" << endl;
					break;
				case 'e':
					if (setLang) {

						setLang = false;
					}
					else {
						cout << "��������ȷ�Ĳ���" << endl;
						return 0;
					}
					cout << "eee" << endl;
					break;
				case 'f':
					if (setLang) {

						setLang = false;
					}
					else {
						cout << "��������ȷ�Ĳ���" << endl;
						return 0;
					}
					cout << "fff" << endl;
					break;
				case 'g':
					if (setLang) {

						setLang = false;
					}
					else {
						cout << "��������ȷ�Ĳ���" << endl;
						return 0;
					}
					cout << "ggg" << endl;
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
				cout << "Chinese" << endl;
			}
			else if (strcmp("English", index) == 0 && setLang) {
				setLang = false;
				cout << "English" << endl;
			}
			else if (strcmp("French", index) == 0 && setLang) {
				setLang = false;
				cout << "French" << endl;
			}
			else if (strcmp("German", index) == 0 && setLang) {
				setLang = false;
				cout << "German" << endl;
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
	srand(unsigned(time(NULL)));		//��������Ӳ��ܷ�����ĺ����У�������ܻᵼ�»����ͬ�������
	cout << "�������꼶(3��4��5):" << endl;
	cin >> gra;
	while (gra != 3 && gra != 4 && gra != 5) {
		cout << "��������ȷ���꼶(3��4��5):" << endl;
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
		cout << "��������Ŀ������:" << endl;
		cin >> num;
		while (num <= 0) {
			cout << "��������ȷ����Ŀ����:" << endl;
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
		student = new GradeThree();		//��ת�Ͷ���
		break;
	case GradeFo:
		student = new GradeFour();
		break;
	case GradeFi:
		student = new GradeFive();
		break;
	}

	student->Calculate(num, mode);

	getchar();
	cout << endl
		<< "(�������г���������r)" << endl
		<< "�س����˳�����:" << endl;
	delete student;
	if (getchar() == 'r') {
		cout << endl;
		main(argc, argv);
	}
	return 0;
}