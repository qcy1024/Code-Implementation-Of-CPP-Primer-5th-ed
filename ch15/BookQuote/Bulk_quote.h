#pragma once
#include "Quote.h"
class Bulk_quote :
    public Quote
{
public:
    double net_price(int n);
    Bulk_quote(const std::string& tmpNo, int tmpPrice, int min_qty, double discount) : 
        Quote(tmpNo, tmpPrice), min_qty(min_qty), discount(discount) {};

    virtual void printAllMem() const override;
private:
    //打折所需的最小购买量
    int min_qty;
    double discount;
};

