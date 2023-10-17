#pragma once
#include "Quote.h"

//������num�����Ĳ��ְ�discount���ۣ��������ְ�ԭ�۳���
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

