#include "Product/Product.h"

#pragma once
class ConcreteProduct2 : public Product {
public:
	virtual std::string Operation() const override;
};