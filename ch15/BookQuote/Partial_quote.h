#pragma once
#include "Quote.h"

//不超过num数量的部分按discount打折，超出部分按原价出售
class Partial_quote :
    public Quote
{
public:
    Partial_quote(const std::string& tmpNo, int tmpPrice, int num, double discount) :
        Quote(tmpNo, tmpPrice), num(num), discount(discount) {};
    double net_price(int n);
    virtual void printAllMem() const override;
private:
    int num;
    double discount;
};

