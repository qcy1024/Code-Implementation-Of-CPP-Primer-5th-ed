#pragma once
#include <string>
#include <iostream>

//�����۳���(����ٶ�������)
class Quote
{
public:
	Quote():price(0),bookNo("00") {};
	Quote(const std::string& tmpNo,double tmpPrice) :bookNo(tmpNo), price(tmpPrice) {};
	virtual ~Quote() {};

	std::string isbn() const { return bookNo; };
	//����ϣ��net_price����Ϊ��������صģ���˽���������麯��
	virtual double net_price(int n) { return n * price; }
	virtual void printAllMem() const;
private:
	std::string bookNo;
protected:
	double price;
};

