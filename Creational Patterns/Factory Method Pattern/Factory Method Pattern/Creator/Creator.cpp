#include "stdafx.h"
#include "Creator.h"

std::string Creator::SomeOperation() const {
    Product* product = this->FactoryMethod();
    std::string result = "Creator의 operation 함수: " + product->Operation() + "의 함수 호출!";
    delete product;
    return result;
}
