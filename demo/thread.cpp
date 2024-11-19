#include <iostream>
#include <thread>
#include <vector>
#include <sys/syscall.h>
#include <unistd.h>
#include <chrono>

using namespace std;

// 定义一个函数作为线程的执行函数
void threadFunction(int threadId) {
    cout << "thread-" << threadId << "’s lighting_weight_pid is ：" << syscall(SYS_gettid) << endl;
    this_thread::sleep_for( chrono::seconds(30));
    cout << "thread-" << threadId << " 执行完毕" <<  endl;
}

int loop_main() {
    int busyTime = 1000000; // 单位：毫秒
    // 获取程序开始时间
    auto startTime = chrono::steady_clock::now();
    while (true) {
        // 获取当前时间
        auto currentTime = chrono::steady_clock::now();

        // 检查已经运行的时间是否达到要求
        auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(currentTime - startTime).count();
        if (elapsedTime >= busyTime) {
            break;
        }
    }
    return 0;
}

int main() {
    cout << "Start main thread" << endl;
    loop_main();
    // 创建5个线程·
    vector<thread> threads;
    for (int i = 1; i <= 5; ++i) {
        threads.push_back( thread(threadFunction, i));
    }
    // 等待所有线程执行完毕
    for (auto& thread : threads) {
        thread.join();
    }

     cout << "主进程结束" <<  endl;

    return 0;
}




//编译 g++ -o main thread.cpp -pthread
//用于指示编译器链接pthread库，#include <thread> 就要用到