#pragma once
#include <string>
#include <iostream>

//不打折出售(买多少都不打折)
class Quote
{
public:
	Quote():price(0),bookNo("00") {};
	Quote(const std::string& tmpNo,double tmpPrice) :bookNo(tmpNo), price(tmpPrice) {};
	virtual ~Quote() {};

	std::string isbn() const { return bookNo; };
	//我们希望net_price的行为是类型相关的，因此将它定义成虚函数
	virtual double net_price(int n) { return n * price; }
	virtual void printAllMem() const;
private:
	std::string bookNo;
protected:
	double price;
};

