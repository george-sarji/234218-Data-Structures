#include "Agency.h"

namespace structures
{

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

    void structures::Agency::updateAgency(const Agency &agency)
    {
        // Update the proper agency items.
        this->total_sales += agency.total_sales;
        this->total_types += agency.total_types;
        // TODO: Update the trees accordingly.
    }

    Tree<CarType>* Agency::getCarTypes() const
    {
        return this->car_types;
    }

    RankTree<CarSale> *Agency::getCarSales() const
    {
        return this->car_sales;
    }

    void Agency::setCarTypes(Tree<CarType> *carType)
    {
        this->car_types = carType;
    }

    void Agency::setCarSales(RankTree<CarSale> *carSale)
    {
        this->car_sales = carSale;
    }

    CarType** Agency::getArrayFromNormalTree()
    {
        return car_types->getArrayFromTree(car_sales->numOfSubtrees());
    }

    int Agency::getTreeSize() const
    {
        return car_sales->numOfSubtrees();
    }
}
