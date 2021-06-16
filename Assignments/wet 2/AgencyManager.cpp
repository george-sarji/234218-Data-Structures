#include "AgencyManager.h"

namespace structures
{
    structures::AgencyManager::AgencyManager() {}

    structures::AgencyManager::~AgencyManager()
    {
        delete sets;
        // TODO: Clear tree
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

    // Tree<T>* structures::AgencyManager::getAgenciesTree() const {}
    // void structures::AgencyManager::setAgenciesTree(Tree<T>* tree) {}

    void structures::AgencyManager::addAgency()
    {
        this->sets->initiateAgency();
        this->total_agencies++;
    }

    void AgencyManager::sellCar(int agencyID, int typeID, int k)
    {
        if(k <= 0 || agencyID < 0)
        {
            throw InvalidInput();
        }

        //Find the agency to sell the car to.
        Agency temp(agencyID);
        Agency* wanted_agency = sets->findAgency(&temp);

        CarType temp_car(typeID);

        //first check if car with typeID was already sold before with wanted_agency.
        try
        {
            Tree<CarType>* wanted_car = wanted_agency->getCarTypes()->findData(temp_car);
        }
        catch (const TreeException& e)
        {

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

    void structures::AgencyManager::getIthSoldType(int agency_id, int i, int *ptr) {}


}
