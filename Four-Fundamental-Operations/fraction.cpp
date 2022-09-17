#include "fraction.hpp"

//Fraction Fraction::FraGenerate(int randomNum1, int randomNum2)
//{
//	if (randomNum1 > randomNum2) {		//��֤���ӱȷ�ĸС
//		int t = randomNum1;
//		randomNum1 = randomNum2;
//		randomNum2 = t;
//	}
//	if (randomNum1 == randomNum2) {		//��֤�������ĸ�����
//		randomNum2 += 1;
//	}
//	Fraction randomFra;
//	randomFra.molecule = randomNum1;
//	randomFra.denominator = randomNum2;
//	return randomFra;
//}

int Gcd::Gcd(int large, int small) {	//�����Լ�������ڶԷ���Լ��
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

Fraction operator+(const Fraction& F1, const Fraction& F2)
{
	Fraction result;
	result.denominator = F1.denominator * F2.denominator;
	result.molecule = F1.molecule * F2.denominator + F2.molecule * F1.denominator;
	int gcd = Gcd::Gcd(result.denominator, result.molecule);		//Լ��
	result.denominator /= gcd;
	result.molecule /= gcd;
	if (result.denominator < 0) {	//��ĸ���С��0����ת����������
		result.denominator = -result.denominator;
		result.molecule = -result.molecule;
	}
	return result;
}

Fraction operator-(const Fraction& F1, const Fraction& F2) {	//F1 - F2
	Fraction result;
	result.denominator = F1.denominator * F2.denominator;
	result.molecule = F1.molecule * F2.denominator - F2.molecule * F1.denominator;
	int gcd = Gcd::Gcd(result.denominator, result.molecule);		//Լ��
	result.denominator /= gcd;
	result.molecule /= gcd;
	if (result.denominator < 0) {	//��ĸ���С��0����ת����������
		result.denominator = -result.denominator;
		result.molecule = -result.molecule;
	}
	return result;
}

Fraction operator*(const Fraction& F1, const Fraction& F2) {
	Fraction result;
	result.denominator = F1.denominator * F2.denominator;
	result.molecule = F1.molecule * F2.molecule;
	int gcd = Gcd::Gcd(result.denominator, result.molecule);		//Լ��
	result.denominator /= gcd;
	result.molecule /= gcd;
	if (result.denominator < 0) {	//��ĸ���С��0����ת����������
		result.denominator = -result.denominator;
		result.molecule = -result.molecule;
	}
	return result;
}

Fraction operator/(const Fraction& F1, const Fraction& F2) {	//F1 / F2
	Fraction result;
	result.molecule = F1.molecule * F2.denominator;
	result.denominator = F1.denominator * F2.molecule;
	int gcd = Gcd::Gcd(result.denominator, result.molecule);		//Լ��
	result.denominator /= gcd;
	result.molecule /= gcd;
	if (result.denominator < 0) {	//��ĸ���С��0����ת����������
		result.denominator = -result.denominator;
		result.molecule = -result.molecule;
	}
	return result;
}

bool operator==(const Fraction& F1, const Fraction& F2) {
	return F1.denominator == F2.denominator && F1.molecule == F2.molecule;
}

bool operator!=(const Fraction& F1, const Fraction& F2) {
	return !(F1 == F2);
}


