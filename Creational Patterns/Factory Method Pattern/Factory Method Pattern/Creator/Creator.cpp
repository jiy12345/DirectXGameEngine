#include "stdafx.h"
#include "Product/Product.h"
#include "Creator.h"

std::string Creator::SomeOperation() const {
    Product* product = this->FactoryMethod();
    std::string result = "Creator: The same creator's code has just worked with " + product->Operation();
    delete product;
    return result;
}
