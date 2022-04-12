#include<iostream>

class Singleton {
    static Singleton* instance;
public:
    static Singleton* getInstance() {
        if (Singleton::instance == nullptr) {
            std::cout << "new" << std::endl;
            Singleton::instance = new Singleton;
        }
        return Singleton::instance;
    }
private:
    Singleton() = default;
    ~Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};
