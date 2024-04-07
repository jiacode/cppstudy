#include <iostream>  
#include <thread>  
#include <chrono>  
#include "myThread.h"  

int main() {
    // 创建 MyThread 对象  
    MyThread myThreadObj;

    // 等待一段时间以便线程可以执行一些操作  
    // 在这个例子中，我们等待5秒钟，以便观察线程的操作效果  
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // 在等待时间结束后，线程应该已经添加了一些随机数，删除了一些元素，并打印了vector的内容  
    // 输出一些信息来表明程序即将结束  
    std::cout << "Main thread is about to exit. Waiting for MyThread to stop..." << std::endl;

    // 当main函数返回时，MyThread的析构函数会被调用，从而停止线程并清理资源  
    // 不需要显式调用myThreadObj.stop()，因为析构函数已经处理了  

    return 0;
}