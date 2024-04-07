#include "JTools.h"  

// 构造函数实现  
JTools::JTools() {
    // 使用当前时间作为随机数种子  
    seed = static_cast<unsigned int>(std::time(0));
    std::srand(seed);
}

// 生成随机整数函数实现  
int JTools::getRandomInt(int min, int max) {
    // 生成随机数并限制在指定范围内  
    return std::rand() % (max - min + 1) + min;
}