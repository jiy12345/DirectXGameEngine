#include"ThreadUnsafeSingleton.h"
#include<thread>

Singleton* Singleton::instance = nullptr;

int main() {
    std::thread a(Singleton::getInstance);
    std::thread b(Singleton::getInstance);
    std::thread c(Singleton::getInstance);
    std::thread d(Singleton::getInstance);
    a.join();
    b.join();
    c.join();
    d.join();
    return 0;
}