#ifndef AGENCY_H
#define AGENCY_H

namespace structures
{
    class Agency
    {
    private:
        int agency_id;
        int total_types;
        int total_sales;
        // Tree<CarType> car_types;
        // Tree<CarSale> car_sales;
    public:
        Agency() = default;
        ~Agency();
        Agency(const Agency &);

        // * Getters/Setters
        int getAgencyId() const;
        int getTotalTypes() const;
        int getTotalSales() const;
        // Tree<CarType>* getCarTypes() const;
        // Tree<CarSale>* getCarSales() const;
        void setAgencyId(int);
        void setTotalTypes(int);
        void setTotalSales(int);
        // void setCarTypes(Tree<CarType>*);
        // void setCarSales(Tree<CarSale>*);

        // * Operator overloads
        bool operator<(const Agency &);
        bool operator<=(const Agency &);
        bool operator>(const Agency &);
        bool operator>=(const Agency &);
        bool operator==(const Agency &);

        // * Utility functions
        void updateAgency(const Agency&);
    };
}

#endif