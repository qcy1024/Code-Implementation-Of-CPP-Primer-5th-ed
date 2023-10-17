#include "Partial_quote.h"

double Partial_quote::net_price(int n)
{
	double total = 0;
	if (n >= num)
	{
		total += num * price * (1 - discount);
		total += (n - num) * price;
	}
	else
	{
		total += n * price * (1 - discount);
	}
	return total;
}

void Partial_quote::printAllMem() const 
{
	std::cout << "isbn: " << this->isbn() << " price:" << this->price << " 多少本以内打折："
		<< this->num << " 便宜多少： " << this->discount;
}