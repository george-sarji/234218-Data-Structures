#include "CarType.h"

bool structures::CarType::operator<(const structures::CarType &carType) const
{
    return this->typeID < carType.typeID;
}

bool structures::CarType::operator<=(const structures::CarType &carType) const
{
    return this->typeID <= carType.typeID;
}

bool structures::CarType::operator>(const structures::CarType &carType) const
{
    return this->typeID > carType.typeID;
}

bool structures::CarType::operator>=(const structures::CarType &carType) const
{
    return this->typeID >= carType.typeID;
}

bool structures::CarType::operator==(const structures::CarType &carType) const
{
    return this->typeID == carType.typeID;
}

int structures::CarType::getTypeID() const
{
    return this->typeID;
}

int structures::CarType::getSales() const {
    return this->sales;
}

void structures::CarType::setTypeID(int newID)
{
    this->typeID = newID;
}

void structures::CarType::setSales(int sales)
{
    this->sales = sales;
}
