#include <iostream>
#include <cstdlib>
#include <functional>
#include <utility>
#include "./baseTest.h"
#include "./math_function.h"

void example01() {
	using namespace emansis::Math;
	double ret = 0.0;
	double a = 2;
	double base = 1.1;
	int count = 5;
	Function func;	//实例化仿函数对象
	procFunc<void(double&)> funcProc_1 = [&a, count, &base](double& registerObject)->void const {
		if (registerObject == 0.0)
			registerObject = base;
		for (int i = 0; i < count; ++i)
			registerObject *= a;			//进行count次a倍累乘
	};				//实例化一个lambda对象并包装成一个处理函数，lambda对象捕捉当前域中的对象以进行计算
	ret = func(0.0, funcProc_1, funcProc_1);
	std::cout << ret << std::endl;
	exit(0);
}

void example02() {
	//实例化模拟器仿函数对象
	emansis::Math::Function caculate;
	//在准备传入参数
	double 	y 		= 0.0;
	double 	x		= 0.0;
	int 	pow_n	= 2;
	std::cout << "input x >" ;
	std::cin >> x;

	//准备处理函数
	emansis::Math::procFunc<void(double&)> y_f_x_pow_n = [&x, &pow_n](double& registerObject)->void const {
		if (pow_n == 0) {
			registerObject = x == 0.0 ? 0.0 : 1.0;
			return;
		}
		double sum = x;
		for (int i = 0; i < pow_n - 1; ++i)
			sum *= x;
		registerObject = sum;
	};
	//启动计算
	y = caculate(0.0, y_f_x_pow_n);
	std::cout << "y = x ^ " << pow_n << " : y(" << x << ") = " << y << std::endl;

	exit(0);
}

int main() {
	system("chcp 65001");

	example02();

	//随机数生成器初始化
	srand(time(nullptr));
	unsigned int 	group = 0;
	unsigned long long count = 0;
	
	//数值录入
	std::cout << "group>";
	std::cin >> group;
	std::cout << "count>";
	std::cin >> count;

	emansis::baseTest_CaculaterOfMaleFremlProprotion(group, count);

	system("pause");
	return 0;
}