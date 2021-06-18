#ifndef AGENCY_H
#define AGENCY_H

#include "CarType.h"
#include "Tree.h"
#include "RankTree.h"
#include "CarSale.h"

namespace structures
{
    class Agency
    {
    private:
        int agency_id;
        int total_types;
        int total_sales;
        Tree<CarType>* car_types;
        RankTree<CarSale>* car_sales;
    public:
        Agency() = default;
        Agency(const int i) : agency_id(i), total_types(0), total_sales(0) {}
        ~Agency();
        Agency(const Agency &);

        // * Getters/Setters
        int getAgencyId() const;
        int getTotalTypes() const;
        int getTotalSales() const;
        Tree<CarType>* getCarTypes() const;
        RankTree<CarSale>* getCarSales() const;
        void setAgencyId(int);
        void setTotalTypes(int);
        void setTotalSales(int);
        void setCarTypes(Tree<CarType>* carType);
        void setCarSales(RankTree<CarSale>* carSale);

        // * Operator overloads
        bool operator<(const Agency &);
        bool operator<=(const Agency &);
        bool operator>(const Agency &);
        bool operator>=(const Agency &);
        bool operator==(const Agency &);

        // * Utility functions
        void updateAgency(const Agency &);
    };
}

#endif
