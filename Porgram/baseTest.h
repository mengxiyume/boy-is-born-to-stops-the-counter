#pragma once
#include <thread>
#include <future>
#include <vector>
#include <iostream>
#include <ctime>
#include "./caculater.h"

namespace emansis {
    /// @brief                              基准测试
    /// @param simulationCount              模拟单元数量
    /// @param singleSimulationFamilyCount  每个单元模拟次数
    void baseTest_CaculaterOfMaleFremlProprotion(uint8_t simulationCount, uint32_t singleSimulationFamilyCount) {
	    std::cout << (uint32_t)simulationCount << " group " << singleSimulationFamilyCount << " count" << std::endl;
	    //计时
	    clock_t start_clock = clock();
	    //异步计算结果存储数组
	    std::vector<std::future<emansis::CaculaterOfMaleFremlProprotion::TestUnit>> group;
	    group.reserve(simulationCount);
	    for (uint8_t i = 0; i < simulationCount; ++i) {
	    	//创建异步任务
	    	group.push_back(async(std::launch::async, [](uint32_t count){
	    		putchar('R');
	    		emansis::CaculaterOfMaleFremlProprotion::TestUnit result;
	    		result.runCaculater(count);
	    		putchar('O');
	    		return result;
	    	}, singleSimulationFamilyCount));
	    }

	    uint64_t 	familyCount 	= 0;
	    uint64_t 	maleCount 		= 0;
	    uint64_t 	femalCount 		= 0; 
	    uint64_t 	peopleCount 	= 0;
	    uint64_t 	singleChildFamily 			= 0;
	    uint64_t 	doubleChildFamily 			= 0;
	    uint64_t 	multipieChildFamily 		= 0;
	    uint8_t		biggerstFamilyPeopleCount 	= 0;
    
	    //获取最终统计数据
	    for (auto& e : group) {
	    	emansis::CaculaterOfMaleFremlProprotion::TestUnit result = e.get();
	    	familyCount	+= result.getFamilyCount();
	    	maleCount 	+= result.getMaleCount();
	    	femalCount	+= result.getFemalCount();
	    	peopleCount	+= result.getPeopleCount();
	    	singleChildFamily	+= result.getSingleChildFamilyCount();
	    	doubleChildFamily	+= result.getDoubleChildFamilyCount();
	    	multipieChildFamily	+= result.getMultipieChildFamilyCount();
	    	biggerstFamilyPeopleCount = biggerstFamilyPeopleCount > result.getBiggerFamilyPeopleCount() ? biggerstFamilyPeopleCount : result.getBiggerFamilyPeopleCount();
	    }
    
	    //计时结束
	    clock_t totalTime = clock() - start_clock;
	    putchar('\n');
	    std::cout << "total " << totalTime << "ms" << std::endl;
	    //输出统计数据
	    std::cout
	    	<< "people 	count " << peopleCount << '\n'
	    	<< "male 	count " << maleCount << '\n'
	    	<< "femal	count " << femalCount << '\n'
	    	<< "family	count " << familyCount << '\n'
	    	<< "average child number of family "<< (double)peopleCount / (double)familyCount << '\n'
	    	<< "biggerst famliy have " 			<< (uint32_t)biggerstFamilyPeopleCount << " people" << '\n'
	    	<< "one child family		count "	<< singleChildFamily << '\n'
	    	<< "double child family 	count "	<< doubleChildFamily << '\n'
	    	<< "multipie child family	count "	<< multipieChildFamily << '\n'
	    	<< "male : female " << (double)maleCount / (double)femalCount << '\n'
	    	<< "multipie : double : single > " 
	    	<< 1 << " : " 
	    	<< (double)((double)doubleChildFamily / (double)multipieChildFamily) << " : " 
	    	<< (double)((double)singleChildFamily / (double)multipieChildFamily) << '\n'
	    ;
    }
}