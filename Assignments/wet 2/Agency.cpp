#include "Agency.h"

namespace structures
{

    structures::Agency::Agency() {}
    structures::Agency::~Agency() {}
    structures::Agency::Agency(const Agency &agency) {}

    int structures::Agency::getAgencyId() const
    {
        return this->agency_id;
    }
    int structures::Agency::getTotalSales() const
    {
        return this->total_sales;
    }
    int structures::Agency::getTotalTypes() const
    {
        return this->total_types;
    }
    // Tree<CarType>* structures::Agency::getCarTypes() const
    // {
    //      return this->car_types;
    // }
    // Tree<CarSale> *structures::Agency::getCarSales() const
    // {
    //     return this->car_sales;
    // }

    void structures::Agency::setAgencyId(int num)
    {
        this->agency_id = num;
    }
    void structures::Agency::setTotalSales(int sales)
    {
        this->total_sales = sales;
    }
    void structures::Agency::setTotalTypes(int types)
    {
        this->total_types = types;
    }
    // void structures::Agency::setCarTypes(Tree<CarType> *tree)
    // {
    //     this->car_types = tree;
    // }
    // void structures::Agency::setCarSales(Tree<CarSale> *tree)
    // {
    //     this->car_sales = tree;
    // }

    bool structures::Agency::operator<(const Agency &agency)
    {
        return this->agency_id < agency.agency_id;
    }
    bool structures::Agency::operator<=(const Agency &agency)
    {
        return this->agency_id <= agency.agency_id;
    }
    bool structures::Agency::operator>(const Agency &agency)
    {
        return this->agency_id > agency.agency_id;
    }
    bool structures::Agency::operator>=(const Agency &agency)
    {
        return this->agency_id >= agency.agency_id;
    }
    bool structures::Agency::operator==(const Agency &agency)
    {
        return this->agency_id == agency.agency_id;
    }
}