#ifndef AGENCY_MANAGER_H
#define AGENCY_MANAGER_H

// ! #include "Tree.h"

namespace structures
{
    class AgencyManager
    {
    private:
        int total_agencies;
        // Tree<T>* agencies_tree
    public:
        AgencyManager();
        ~AgencyManager();
        AgencyManager(const AgencyManager &);

        // * Setters/Getters
        int getTotalAgencies() const;
        // Tree<T> *getAgenciesTree() const;
        void setTotalAgencies(int num);
        // void setAgenciesTree(Tree<T>* tree);

        // * Requested functions
        void addAgency();
        void sellCar(int, int);
        void uniteAgencies(int, int);
        void getIthSoldType(int, int, int *);
    };
}

#endif