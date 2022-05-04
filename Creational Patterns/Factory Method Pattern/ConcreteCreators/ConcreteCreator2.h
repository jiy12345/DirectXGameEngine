#include "stdafx.h"
#include "ConcreteProducts/ConcreteProduct2.h"
#include "Creator/Creator.h"
#include "Product/Product.h"

#pragma once
class ConcreteCreator2 : public Creator {
public:
    Product* FactoryMethod() const override {
        return new ConcreteProduct2();
    }
};

