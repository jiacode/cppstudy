#pragma once
#ifndef MYTHREAD_H  
#define MYTHREAD_H  

#include <iostream>  
#include <vector>  
#include <thread>  
#include <random>  
#include <mutex>  
#include <condition_variable>  

class MyThread {
public:
    MyThread();
    ~MyThread();

    void start();
    void stop();

private:
    std::vector<int> data;
    std::mutex mtx;
    std::condition_variable cv;
    bool running;
    std::thread adderThread;
    std::thread deleterThread;
    std::thread printerThread;

    void addRandomNumber();
    void deleteRandomElement();
    void printVector();
};

#endif // MYTHREAD_H