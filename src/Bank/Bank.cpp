#include <iostream>
#include "Tower.hpp"
#include "Monster.hpp"
#include "Bank.hpp"

using namespace std;

Bank::Bank()
{
    this->sold = 0;
}

void Bank::addMoney(double amount_to_add)
{
    if (!this->sold + amount_to_add > MAX)
    {
        this->sold += amount_to_add;
    }
    else
    {
        this->sold = MAX;
    }
}

void Bank::removeMoney(double amount_to_remove)
{
    if (!this->sold - amount_to_remove < MIN)
    {
        this->sold -= amount_to_remove;
    }
    else
    {
        this->sold = MIN;
    }
}

double Bank::getBankSold()
{
    return this->sold;
}

void Bank::setBankSold(double new_sold)
{
    this->sold = new_sold;
}