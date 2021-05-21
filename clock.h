#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <mutex>
#include <condition_variable>
#include <iostream>
#include <thread>

class Clock
{
private:
    enum Status
    {
        TIC,
        TAC
    };

    Clock(const Clock&) = delete;               // конструктор копирования 
    Clock& operator=(const Clock&) = delete;    // оператор присваивания копирования 

    Status clockStatus = Status::TAC;
    std::mutex status;
    std::condition_variable cv;
    int runCount;
public:
    Clock(int count);

    void tic();

    void tac();

    void run();
};
#endif