#pragma once
class Product {
public:
	virtual ~Product() {}
	virtual std::string Operation() const = 0;
};

