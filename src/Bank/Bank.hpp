#include <iostream>
#include "../Entities/Tower.hpp"
#include "../Entities/Monster.hpp"

using namespace std;

class Bank
{
private:
    static const int MAX{1000};
    static const int MIN{0};
    float sold{};

public:
    Bank();
    void addMoney(float amount_to_add);
    void removeMoney(float amount_to_remove);
    float getBankSold();
    void setBankSold(float new_sold);
};