#include "AgencyManager.h"

namespace structures
{
    structures::AgencyManager::AgencyManager() {}

    structures::AgencyManager::~AgencyManager() {}

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

    void addAgency() {}

    void sellCar(int agency_id, int type_id);

    void uniteAgencies(int agency1, int agency2);

    void getIthSoldType(int agency_id, int i, int *ptr);
}

int main()
{
    return 0;
}