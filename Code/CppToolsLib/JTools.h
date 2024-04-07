#pragma once

#include <cstdlib>  
#include <ctime>  

class JTools {
public:
    // 构造函数，初始化随机数种子  
    JTools();

    // 生成指定范围内的随机整数  
    int getRandomInt(int min, int max);

private:
    // 随机数生成器的种子  
    unsigned int seed;
};

