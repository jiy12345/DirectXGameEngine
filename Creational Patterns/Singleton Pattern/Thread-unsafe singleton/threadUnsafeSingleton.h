#pragma once
#include<iostream>

class Singleton {
    static Singleton* instance;
public:
    static Singleton* getInstance() {
        if (Singleton::instance == nullptr) {
            Singleton::instance = new Singleton;
        }
        return Singleton::instance;
    }
private:
    Singleton() {
        std::cout << "new instance created\n";
    };
    ~Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};
