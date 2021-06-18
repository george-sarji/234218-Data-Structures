#ifndef AGENCY_MANAGER_H
#define AGENCY_MANAGER_H

#include "Agency.h"
#include "SetManager.h"

namespace structures
{
    class AgencyManager
    {
    private:
        int total_agencies;
        SetManager* sets;
    public:
        AgencyManager();
        ~AgencyManager();
        AgencyManager(const AgencyManager &);

        // * Setters/Getters
        int getTotalAgencies() const;
        void setTotalAgencies(int num);

        // * Requested functions
        void addAgency();
        void sellCar(int agencyID, int typeID, int k);
        void uniteAgencies(int, int);
        void getIthSoldType(int, int, int *);
    };
}

#endif
