#include "stdafx.h"
#include "ConcreteProducts/ConcreteProduct1.h"
#include "Creator/Creator.h"
#include "Product/Product.h"

#pragma once
class ConcreteCreator1 : public Creator {
public:
    Product* FactoryMethod() const override {
        return new ConcreteProduct1();
    }
};