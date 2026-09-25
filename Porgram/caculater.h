#include <cstdint>
#include <iostream>
#include <cstdlib>


namespace emansis {
    namespace CaculaterOfMaleFremlProprotion {
        /// @brief 家庭模拟器对象
        class Family{
        private:
        	/// @brief 男性数量
        	uint8_t m_nMaleCount 	= 0;
        	/// @brief 女性数量
        	uint8_t m_nFemalCount 	= 0;
			/// @brief 生育意愿衰减倍率
			double 	m_lfBornIdeasReduceMul	= 0.0;
			/// @brief 一胎意愿
			double	m_lfBornIdeasFirst	= 0.0;
        public:
			/// @brief 						初始化家庭
			/// @param bornIdeasFirst 		一胎意愿			1.0~0.0
			/// @param bornIdeasReduceMul 	生育意愿衰减倍率	1.0~0.0
			Family(double bornIdeasFirst = 1.0, double bornIdeasReduceMul = 0.0)
			: m_nMaleCount	(0)
			, m_nFemalCount	(0)
			, m_lfBornIdeasReduceMul	(bornIdeasReduceMul)
			, m_lfBornIdeasFirst		(bornIdeasFirst) {
				if 	(m_lfBornIdeasFirst 	<= 0.0 || m_lfBornIdeasFirst 	>= 1.0)
					m_lfBornIdeasFirst = 1.0;
				if 	(m_lfBornIdeasReduceMul 	<= 0.0 || m_lfBornIdeasReduceMul 	>= 1.0)
					m_lfBornIdeasReduceMul = 0.0;
			}
        	/// @brief 性别
        	enum Gender{
        		Male 	= 0,
        		Femal 	= 1
        	};
			/// @brief 			重置意愿衰减倍率
			/// @param newFirst	新的衰减倍率	1.0~0.0
			/// @return 		重置失败不修改并返回false，重置成功返回true
			bool		reBornIdeasReduce	(double newReduceMul) {
				if 	(newReduceMul <= 0.0 || newReduceMul >= 1.0) return false;
				m_lfBornIdeasReduceMul = newReduceMul; return true;
			}
			/// @brief 			重置一胎意愿
			/// @param newFirst	新的意愿		1.0~0.0
			/// @return 		重置失败不修改并返回false，重置成功返回true
			bool		reBornIdeasFirst	(double newFirst) {
				if 	(newFirst <= 0.0 || newFirst >= 1.0) return false;
				m_lfBornIdeasFirst = newFirst; return true;
			}
        	/// @brief 重置对象并模拟一次成员诞生流程
        	void 		reCaculation		() {
        		//重置
        		m_nMaleCount 	= 0;
        		m_nFemalCount 	= 0;
        		//开始模拟
        		int gender = 0;
        		int step = 0;
				double currentIdeas = m_lfBornIdeasFirst;
        		do {
					double temp = (double)rand() / (double)32767;
					if (temp <= currentIdeas) {	
						gender 	= rand() % 2;
						if (gender == Male)	++m_nMaleCount;
						else 				++m_nFemalCount;
						if (++step >= UINT8_MAX) break;	//可更改保底条件
						//意愿迭代
						currentIdeas *= (1.0 - m_lfBornIdeasReduceMul);
					}
        		} while (gender != Male);
        	}
        	/// @brief 			获取成员数量
        	/// @param gender 	获取成员数量的性别
        	/// @return 		指定性别成员的数量
        	uint32_t 	count				(Gender gender) { return gender == Male ? m_nMaleCount : m_nFemalCount; }
        };

        /// @brief 单个测试单元
        class TestUnit{
        private:
        #pragma region member
        	/// @brief 	总人数
        	uint64_t 	m_uPeopleCount 	= 0;
        	/// @brief 	家庭总数
        	uint32_t	m_uFamilyCount 	= 0;
        	/// @brief 	男性总数
        	uint32_t 	m_uMaleSum 		= 0;
        	/// @brief 	女性总数
        	uint32_t 	m_uFemalSum 	= 0;
        	/// @brief 	单子家庭总数
        	uint32_t	m_uSingleChildFamily 			= 0;
        	/// @brief 	双子家庭总数
        	uint32_t	m_uDoubleChildFamily 			= 0;
        	/// @brief 	多子家庭总数
        	uint32_t	m_uMultipieChildFamily			= 0;
        	/// @brief 	最多孩子家庭的孩子数量
        	uint8_t		m_uBiggerstFamilyPeopleCount 	= 0;
        #pragma endregion
        public:
        	/// @brief 重置测试数据
        	void clear() {
        		m_uPeopleCount	= 
        		m_uFamilyCount	=
        		m_uMaleSum		=
        		m_uFamilyCount	=
        		m_uSingleChildFamily			=
        		m_uDoubleChildFamily			=
        		m_uMultipieChildFamily			=
        		m_uBiggerstFamilyPeopleCount	= 
        		0;
        	}
        	/// @brief 			开始计算-会清空当前数据
        	/// @param count 	计算家庭总数
        	void runCaculater(uint32_t count) {
        		clear();
        		m_uFamilyCount = count;
        		Family f;
        		//开始计算
        		for (uint32_t i = 0; i < count; ++i) {
        			//模拟家庭生产
        			f.reCaculation();
        			//获取数据
        			int maleCount 	= f.count(Family::Male);
        			int femalCount	= f.count(Family::Femal);
        			int sum = maleCount + femalCount;
        			//计算与更新数据
        			m_uMaleSum 		+= maleCount;
        			m_uFemalSum 	+= femalCount;
        			m_uPeopleCount 	+= sum;
        			switch(sum) {
        			case 1:
        				++m_uSingleChildFamily;
        				break;
        			case 2:
        				++m_uDoubleChildFamily;
        				break;
        			default:
        				++m_uMultipieChildFamily;
        				break;
        			}
        			//max();
        			m_uBiggerstFamilyPeopleCount = m_uBiggerstFamilyPeopleCount > sum ? m_uBiggerstFamilyPeopleCount : sum;
        		}
        	}
        #pragma region getter
        	friend std::ostream& operator<<		(std::ostream& out, TestUnit& obj);
        	const uint64_t 	getPeopleCount	() const { return m_uPeopleCount; }
        	const uint32_t 	getFamilyCount	() const { return m_uFamilyCount; }
        	const uint32_t 	getMaleCount	() const { return m_uMaleSum; }
        	const uint32_t 	getFemalCount	() const { return m_uFemalSum; }
        	const uint32_t 	getSingleChildFamilyCount	() const { return m_uSingleChildFamily; }
        	const uint32_t 	getDoubleChildFamilyCount	() const { return m_uDoubleChildFamily; }
        	const uint32_t 	getMultipieChildFamilyCount	() const { return m_uMultipieChildFamily; }
        	const uint8_t	getBiggerFamilyPeopleCount	() const { return m_uBiggerstFamilyPeopleCount;}
        #pragma endregion
        };
        std::ostream&       operator<<      (std::ostream& out, TestUnit& obj) {
        	out << "people 	count " << obj.m_uPeopleCount << '\n'
        		<< "male 	count " << obj.m_uMaleSum << '\n'
        		<< "femal	count " << obj.m_uFemalSum << '\n'
        		<< "family	count " << obj.m_uFamilyCount << '\n'
        		<< "average child number of family "<< (double)obj.m_uPeopleCount / (double)obj.m_uFamilyCount << '\n'
        		<< "biggerst famliy have " 			<< (uint32_t)obj.m_uBiggerstFamilyPeopleCount << " people" << '\n'
        		<< "one child family		count "	<< obj.m_uSingleChildFamily << '\n'
        		<< "double child family 	count "	<< obj.m_uDoubleChildFamily << '\n'
        		<< "multipie child family	count "	<< obj.m_uMultipieChildFamily << '\n'
        		<< "male : female " << (double)obj.m_uMaleSum / (double)obj.m_uFemalSum << '\n'
        		<< "multipie : double : single > " 
        		<< 1 << " : " 
        		<< (double)obj.m_uDoubleChildFamily / (double)obj.m_uMultipieChildFamily << " : " 
        		<< (double)obj.m_uSingleChildFamily / (double)obj.m_uMultipieChildFamily << '\n'
        		;
        	return out;
        }
    }
}