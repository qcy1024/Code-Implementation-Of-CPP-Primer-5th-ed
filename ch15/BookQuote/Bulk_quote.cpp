#include "Bulk_quote.h"
double Bulk_quote::net_price(int n)
{
	if (n >= min_qty)
		return n * price * (1 - discount);
	return n * price;
}

void Bulk_quote::printAllMem() const
{
	std::cout << "isbn: " << this->isbn() << " Price:" << this->price << " �������ٴ��ۣ� " << this->min_qty
		<< " ���˶��٣� " << this->discount ;
}