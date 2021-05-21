#include "clock.h"

Clock::Clock(int count) : runCount(count) {}

void Clock::tic()
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

void Clock::tac()
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

void Clock::run()
{
    std::thread ticThread(&Clock::tic, this);
    std::thread tacThread(&Clock::tac, this);
    ticThread.join();
    tacThread.join();
}