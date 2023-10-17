#include "Quote.h"
#include <iostream>
double printTotal(std::ostream& os, Quote& q, int n)
{
	double ret = q.net_price(n);
	std::cout << "isbn:" << q.isbn() << "  " << "sold:" << n << "  total price:" << ret;
	return ret;
}

void Quote::printAllMem() const
{
	std::cout << "isbn:" << this->isbn() <<  " Price:" << this->price;
}
