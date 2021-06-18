#include "Agency.h"
#include "Utilities.h"

namespace structures
{

    structures::Agency::~Agency()
    {
        this->car_sales->clearRankTree();
        this->car_types->clearTree();
    }
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
        // Get the relevant arrays.
        // Check if we even need to merge the trees.
        if (this->car_sales->Data() == nullptr && agency.getCarSales()->Data() == nullptr)
        {
            return;
        }
        CarType **current = nullptr, **other = nullptr;
        current = this->getArrayFromNormalTree();
        other = agency.getArrayFromNormalTree();
        // Get the relevant sizes.
        int current_size = this->getTreeSize(), other_size = agency.getTreeSize();
        // Get a new array.
        CarType **merged_arr = mergeArrays(current, other, current_size, other_size);
        // We need to remove the current tree and add the new one.
        this->car_types->clearTree();
        //delete this->car_types;
        this->car_types = createAVLFromArray(merged_arr, 0, current_size + other_size - 1);
        // We can delete the merged array and the previous arrays now.
        delete[] merged_arr;
        delete[] current;
        delete[] other;
        // We need to merge the car sales now.
        CarSale **current_sales = nullptr, **other_sales = nullptr;
        current_sales = this->car_sales->getArrayFromTree();
        other_sales = agency.getCarSales()->getArrayFromTree();
        // Merge the arrays.
        CarSale **merged_sales = mergeArrays(current_sales, other_sales, current_size, other_size);
        // Delete the previous tree and add the new one.
        this->car_sales->clearRankTree();
        //delete this->car_sales;
        this->car_sales = createRankTreeFromArray(merged_sales, 0, current_size + other_size - 1);
        // Delete the arrays.
        delete[] merged_sales;
        delete[] current_sales;
        delete[] other_sales;
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

    CarType **Agency::getArrayFromNormalTree() const
    {
        return car_types->getArrayFromTree(car_sales->numOfSubtrees());
    }

    int Agency::getTreeSize() const
    {
        if (this->car_sales->Data() == nullptr)
        {
            return 0;
        }
        return car_sales->numOfSubtrees();
    }
}
