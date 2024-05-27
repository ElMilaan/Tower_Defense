#pragma once

#include <iostream>
#include "Tower.hpp"
#include "Monster.hpp"

using namespace std;

class Bank
{
private:
    static const int MAX{1000};
    static const int MIN{0};
    double sold{};

public:
    Bank();
    void addMoney(double amount_to_add);
    void removeMoney(double amount_to_remove);
    double getBankSold();
    void setBankSold(double new_sold);
};