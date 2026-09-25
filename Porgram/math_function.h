#pragma once
#include <functional>

namespace emansis {
    namespace Math {
        /// @brief 数学函数计算模拟器
        struct Function {
            /// @brief                  递归展开停止函数
            /// @tparam Result_Type     计算结果返回值类型
            /// @tparam ProcFunc        数据处理仿函数类
            /// @param registerObject   处理数据的存放器，每一个ProcFunc都需要对其进行处理，该参数决定最终返回值类型
            /// @param proc             数据处理仿函数对象
            /// @return                 完成处理后的数据引用
            template<typename Result_Type, class ProcFunc>
            Result_Type& operator()(Result_Type&& registerObject, ProcFunc&& proc) const
            { proc(registerObject); return registerObject; }
            
            /// @brief                  递归展开函数
            /// @tparam Result_Type     计算结果返回值类型
            /// @tparam ProcFunc        数据处理仿函数类
            /// @tparam ...ProcFuncArgs 处理仿函数参数列表包
            /// @param registerObject   处理数据的存放器，每一个ProcFunc都需要对其进行处理，该参数决定最终返回类型
            /// @param proc             数据处理仿函数对象
            /// @param ...func_packge   处理仿函数对象参数包
            /// @return                 完成处理后的数据引用
            template<typename Result_Type, class ProcFunc, class ...ProcFuncArgs>
            Result_Type& operator()(Result_Type&& registerObject, ProcFunc&& proc, ProcFuncArgs... func_packge) const
            { proc(registerObject); return operator()(registerObject, func_packge...); }
        };
        /// @brief              处理函数包装器
        /// @tparam ProcFunc    经过处理的处理函数类型 该函数需要拥有一个不可缺省参数
        /// 该参数用于存储计算中的寄存数据，数据的类型需要与调用它的Function仿函数返回值基本类型相同
        template<class ProcFunc>
        using procFunc = std::function<ProcFunc>;
    }
}