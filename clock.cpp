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
    Clock(int count) : runCount(count) {}

    void tic()
    {
        for (int i = 0; i < runCount; i++)
        {
            std::unique_lock<std::mutex> ul(status);
            cv.wait(ul, [=]() { return clockStatus == Status::TAC; });
            clockStatus = Status::TIC;
            std::cout << "TIC" << std::endl;
            cv.notify_one();
        }
    }

    void tac()
    {
        for (int i = 0; i < runCount; i++)
        {
            std::unique_lock<std::mutex> ul(status);
            cv.wait(ul, [=]() { return clockStatus == Status::TIC; });
            clockStatus = Status::TAC;
            std::cout << "\tTAC" << std::endl;
            cv.notify_one();
        }
    }


    void run()
    {
        std::thread ticThread(&Clock::tic, this);
        std::thread tacThread(&Clock::tac, this);
        ticThread.join();
        tacThread.join();
    }
};

int main()
{
    Clock clock(10);
    clock.run();
    return 0;
}