#include <iostream>
#include <cstdlib>
#include "./baseTest.h"

int main() {
	system("chcp 65001");

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