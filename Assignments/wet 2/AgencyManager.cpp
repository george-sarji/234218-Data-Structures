#include "AgencyManager.h"

namespace structures
{
    structures::AgencyManager::AgencyManager()
    {
        this->sets = new SetManager();
        this->total_agencies = 0;
    }

    structures::AgencyManager::~AgencyManager()
    {
        delete sets;
    }

    structures::AgencyManager::AgencyManager(const AgencyManager &manager) {}

    int structures::AgencyManager::getTotalAgencies() const
    {
        return this->total_agencies;
    }

    void structures::AgencyManager::setTotalAgencies(int num)
    {
        this->total_agencies = num;
    }

    void structures::AgencyManager::addAgency()
    {
        this->sets->initiateAgency();
        this->total_agencies++;
    }

    void AgencyManager::sellCar(int agencyID, int typeID, int k)
    {
        if (k <= 0 || agencyID < 0)
        {
            throw InvalidInput();
        }

        //Find the agency to sell the car to.
        Agency temp(agencyID);
        Agency *wanted_agency = sets->findAgency(&temp);

        if (wanted_agency == nullptr)
        {
            throw FailureError();
        }

        CarType temp_car(typeID);
        bool exists = true;
        Tree<CarType> *wanted_car_node;

        //first check if car with typeID was already sold before with wanted_agency.
        try
        {
            wanted_car_node = wanted_agency->getCarTypes()->findData(temp_car);
        }
        catch (const structures::TreeException &error)
        {
            if (error.errorType() == DOESNT_EXIST)
            {
                exists = false;
            }
        }

        //if car to sell has already been sold before in wanted_agency
        if (exists)
        {
            //update data in car_types tree.
            CarType *wanted_car_type = wanted_car_node->Data();
            int new_sales = wanted_car_type->getSales() + k;
            wanted_car_type->setSales(new_sales);

            //remove car from car_sales tree then add it again with updated data.
            CarSale wanted_car_sale(wanted_car_type->getTypeID(), wanted_car_type->getSales());
            RankTree<CarSale> *temp_tree_ptr = wanted_agency->getCarSales()->removeIntersection(&wanted_car_sale);
            wanted_agency->setCarSales(temp_tree_ptr);

            temp_tree_ptr = wanted_agency->getCarSales()->addIntersection(new CarSale(typeID, new_sales));
            wanted_agency->setCarSales(temp_tree_ptr);

            wanted_agency->setTotalSales(wanted_agency->getTotalSales() + k);
        }
        else
        {
            //add car to car_types tree.
            Tree<CarType> *temp_tree_ptr = wanted_agency->getCarTypes()->addIntersection(new CarType(typeID, k));
            wanted_agency->setCarTypes(temp_tree_ptr);

            //add car to sar_sales tree.
            RankTree<CarSale> *tmp_tree_ptr = wanted_agency->getCarSales()->addIntersection(new CarSale(typeID, k));
            wanted_agency->setCarSales(tmp_tree_ptr);

            wanted_agency->setTotalSales(wanted_agency->getTotalSales() + k);
            wanted_agency->setTotalTypes(wanted_agency->getTotalTypes() + 1);
        }
    }

    void structures::AgencyManager::uniteAgencies(int agency1, int agency2)
    {
        if (agency1 < 0 || agency2 < 0)
        {
            throw InvalidInput();
        }
        if (agency1 > this->total_agencies || agency2 > this->total_agencies)
        {
            throw FailureError();
        }
        this->sets->uniteAgencies(agency1, agency2);
    }

    void structures::AgencyManager::getIthSoldType(int agencyID, int i, int *res)
    {
        if (agencyID < 0 || i < 0 || res == nullptr)
        {
            throw InvalidInput();
        }

        //Find the agency to sell the car to.
        Agency temp(agencyID);
        Agency *wanted_agency = sets->findAgency(&temp);

        if (wanted_agency == nullptr)
        {
            throw FailureError();
        }

        if (wanted_agency->getTotalTypes() < i + 1)
        {
            throw FailureError();
        }

        //get the car with rank i + 1 from car sales tree
        RankTree<CarSale> *wanted_car_node = wanted_agency->getCarSales()->Select(i + 1);
        *res = wanted_car_node->Data()->getTypeID();
    }

}
