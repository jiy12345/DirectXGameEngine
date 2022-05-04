#include "Product/Product.h"

#pragma once
class Creator {
public:
    virtual ~Creator() {};
    virtual Product* FactoryMethod() const = 0;

    std::string SomeOperation() const;
};
