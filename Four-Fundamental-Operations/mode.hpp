#pragma once
#ifndef _MODE_HPP_
#define _MODE_HPP_

enum Mode {
	DEFAULT,	//默认模式：程序直接在命令行输出题目和答案
	QUERY,		//模式1：程序出题，用户回答
	OUTPUT,		//模式2：程序输出1000道题到文件中
	FRACTION	//模式3：程序创建真分数的四则运算
	//三种模式应当能混用，例如程序出题，用户回答，同时每回答一道题，就将回答记录到文件中
};

#endif // !_MODE_HPP_
