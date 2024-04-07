#include "myThread.h"  
#include "JTools.h"

// 构造函数  
MyThread::MyThread() : running(true) {
    // 初始化随机数生成器  
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    // 启动线程  
    // 注意：由于随机数生成器仅在构造函数中初始化一次，因此无法在addRandomNumber中直接使用  
    // 因此，随机数生成器的初始化应移至addRandomNumber函数中  
    adderThread = std::thread(&MyThread::addRandomNumber, this);
    deleterThread = std::thread(&MyThread::deleteRandomElement, this);
    printerThread = std::thread(&MyThread::printVector, this);
}

// 析构函数  
MyThread::~MyThread() {
    // 停止线程  
    stop();
    // 等待线程完成  
    if (adderThread.joinable()) adderThread.join();
    if (deleterThread.joinable()) deleterThread.join();
    if (printerThread.joinable()) printerThread.join();
}

// 启动线程  
void MyThread::start() {
    // 如果已经运行，则无需启动  
    if (running) return;
    running = true;
    // 注意：由于线程已经在构造函数中启动，此函数现在是多余的  
}

// 停止线程  
void MyThread::stop() {
    // 设置停止标志  
    running = false;
    // 通知所有等待的线程  
    cv.notify_all();
}

// 向vector中添加随机数  
void MyThread::addRandomNumber() {
    // 在这里初始化随机数生成器，确保每个线程都有自己的生成器实例  
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);

    while (running) {
        std::unique_lock<std::mutex> lock(mtx);
        // 等待直到线程不被停止，并且拥有锁  
        cv.wait(lock, [this] { return running; });
        if (!running) break; // 如果线程被停止，则退出循环  

        // 生成随机数并添加到vector中  
        int num = dis(gen);
        data.push_back(num);

        // 释放锁并通知其他可能正在等待的线程  
        lock.unlock();
        cv.notify_all();
    }
}

// 从vector中删除随机元素  
void MyThread::deleteRandomElement() {
    while (running) {
        std::unique_lock<std::mutex> lock(mtx);
        // 等待直到线程不被停止，并且vector不为空，同时拥有锁  
        cv.wait(lock, [this] { return running && !data.empty(); });
        if (!running) break; // 如果线程被停止，则退出循环  

        // 选择一个随机索引并删除对应元素  
        size_t index = std::rand() % data.size();
        data.erase(data.begin() + index);

        // 释放锁并通知其他可能正在等待的线程  
        lock.unlock();
        cv.notify_all();
    }
}

// 打印vector的内容  
void MyThread::printVector() {
    while (running) {
        std::unique_lock<std::mutex> lock(mtx);
        // 等待直到线程不被停止，并且vector不为空，同时拥有锁  
        cv.wait(lock, [this] { return running && !data.empty(); });
        if (!running) break; // 如果线程被停止，则退出循环  

        // 打印vector的内容  
        for (int num : data) {
            std::cout << num << ' ';
        }
        std::cout << std::endl;

        // 释放锁并通知其他可能正在等待的线程  
        lock.unlock();
        cv.notify_all();

        // 控制打印频率，避免过快地打印  
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}