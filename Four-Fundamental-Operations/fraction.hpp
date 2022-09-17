#pragma once
#ifndef _FRACTION_HPP_
#define _FRACTION_HPP_

class Fraction {
public :
	int molecule;		//分子
	int denominator;	//分母
	Fraction() { molecule = 0; denominator = 0; }
	Fraction(int molecule, int denominator) :molecule(molecule), denominator(denominator) {}
	//Fraction FraGenerate(int randomNum1, int randomNum2);				//随机生成分数
	friend Fraction operator+(const Fraction& F1, const Fraction& F2);
	friend Fraction operator-(const Fraction& F1, const Fraction& F2);
	friend Fraction operator*(const Fraction& F1, const Fraction& F2);
	friend Fraction operator/(const Fraction& F1, const Fraction& F2);
	friend bool operator==(const Fraction& F1, const Fraction& F2);
	friend bool operator!=(const Fraction& F1, const Fraction& F2);
};

namespace Gcd {
	int Gcd(int large, int small);
}

#endif // !_FRACTION_HPP_
