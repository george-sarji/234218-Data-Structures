#include "Agency.h"
#include "Utilities.cpp"

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
        // We can do the merge functions here.
        CarType **current_types = nullptr, **other_types = nullptr;
        CarSale **current_sales = nullptr, **other_sales = nullptr;
        // TODO: Get the arrays.
        // TODO: Get the sizes.
        int current_types_size = 0, other_types_size = 0, current_sales_size = 0, other_sales_size = 0;
        // We need to merge both arrays.
        CarType **new_types = mergeArrays(current_types, other_types, current_types_size, other_types_size);
        CarSale **new_sales = mergeArrays(current_sales, other_sales, current_sales_size, other_sales_size);
        // We need to now create trees from the given arrays.
        // Delete the previous arrays.
        delete[] current_types;
        delete[] other_types;
        delete[] current_sales;
        delete[] other_sales;
        // Clear the previous trees.
        this->car_sales->clearRankTree();
        this->car_types->clearTree();
        // Delete the previous trees
        delete this->car_sales;
        delete this->car_types;
        // Update into the new trees.
        this->car_sales = createRankTreeFromArray(new_sales, 0, current_sales_size + other_sales_size);
        this->car_types = createAVLFromArray(new_types, 0, current_types_size + other_types_size);
        // Delete the resultant arrays from the merge.
        delete[] new_types;
        delete[] new_sales;
        }

    Tree<CarType> *Agency::getCarTypes() const
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
}
