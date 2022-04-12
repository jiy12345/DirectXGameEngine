#include"ThreadSafeSingleton.h"
#include<vector>
#include<thread>

int main() {
    std::vector<std::thread*> threadVector;

    for (int i = 0; i < 20; i++) {
        threadVector.push_back(new std::thread(Singleton::getInstance));
    }

    for (int i = 0; i < 20; i++) {
        threadVector[i]->join();
    }

    return 0;
}