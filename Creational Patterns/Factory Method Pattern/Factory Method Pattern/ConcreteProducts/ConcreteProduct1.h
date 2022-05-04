#include "Product/Product.h"

#pragma once
class ConcreteProduct1 : public Product {
public:
	virtual std::string Operation() const override;
};