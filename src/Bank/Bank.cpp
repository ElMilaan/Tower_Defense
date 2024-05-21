#include <iostream>
#include "../../include/Tower.hpp"
#include "../../include/Monster.hpp"
#include "../../include/Bank.hpp"

using namespace std;

Bank::Bank()
{
    this->sold = 0;
}

void Bank::addMoney(float amount_to_add)
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

void Bank::removeMoney(float amount_to_remove)
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

float Bank::getBankSold()
{
    return this->sold;
}

void Bank::setBankSold(float new_sold)
{
    this->sold = new_sold;
}