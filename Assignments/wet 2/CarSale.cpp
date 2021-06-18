#include "CarSale.h"

bool structures::CarSale::operator<(const structures::CarSale &carType) const
{
    if(this->sales == carType.sales)
    {
        return this->typeId < carType.typeId;
    }
    return this->sales < carType.sales;
}

bool structures::CarSale::operator<=(const structures::CarSale &carType) const
{
    return this->sales <= carType.sales;
}

bool structures::CarSale::operator>(const structures::CarSale &carType) const
{
    return carType < *this;
}

bool structures::CarSale::operator>=(const structures::CarSale &carType) const
{
    return this->sales >= carType.sales;
}

bool structures::CarSale::operator==(const structures::CarSale &carType) const
{
    return this->sales == carType.sales;
}

int structures::CarSale::getTypeID() const
{
    return this->typeId;
}

int structures::CarSale::getSales() const
{
    return this->sales;
}

void structures::CarSale::setTypeID(int newID)
{
    this->typeId = newID;
}

void structures::CarSale::setSales(int sales)
{
    this->sales = sales;
}
