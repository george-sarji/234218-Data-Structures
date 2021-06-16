#include "AgencyManager.h"

namespace structures
{
    structures::AgencyManager::AgencyManager() {}

    structures::AgencyManager::~AgencyManager() {
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

    void structures::AgencyManager::sellCar(int agency_id, int type_id, int num);

    void structures::AgencyManager::uniteAgencies(int agency1, int agency2);

    void structures::AgencyManager::getIthSoldType(int agency_id, int i, int *ptr);
}
