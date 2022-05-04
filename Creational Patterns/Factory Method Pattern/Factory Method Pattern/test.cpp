#include "stdafx.h"
#include "Creator/Creator.h"
#include "ConcreteCreators/ConcreteCreator1.h"
#include "ConcreteCreators/ConcreteCreator2.h"

void ClientCode(const Creator& creator) {
    std::cout << "Client측: Creator 클래스의 내부를 알지 못해도 다음과 같이 사용 가능" << std::endl;
    std::cout << creator.SomeOperation() << std::endl;
}

int main() {
    std::cout << "=== ConcreteCreator1을 이용한 어플리케이션 시작 ===\n";
    Creator* creator = new ConcreteCreator1();
    ClientCode(*creator);
    std::cout << std::endl;
    std::cout << "=== ConcreteCreator2를 이용한 어플리케이션 시작 ===\n";
    Creator* creator2 = new ConcreteCreator2();
    ClientCode(*creator2);

    delete creator;
    delete creator2;
    return 0;
}