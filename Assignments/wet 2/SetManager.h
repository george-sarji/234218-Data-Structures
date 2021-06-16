#ifndef SET_MANAGER_H_
#define SET_MANAGER_H_
#include "DynamicArray.h"
#include "Agency.h"

namespace structures
{

    class SetManager
    {
    private:
        DynamicArray<Agency> *elements;
        DynamicArray<int>* parents;
        DynamicArray<int>* sizes;
        int size;

        public:
        SetManager();
        ~SetManager();

        int getSize() const;

        void addAgency(Agency* agency);
        void initiateAgency();
        Agency* findAgency(Agency* agency);
        Agency* uniteAgencies(int agency1, int agency2);
    };
}

#endif