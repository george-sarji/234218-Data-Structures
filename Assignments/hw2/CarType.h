#ifndef CARTYPE_H_
#define CARTYPE_H_

#include "CarModel.h"

namespace structures
{
    class CarType
    {
    private:
        int id, max_sales, num_of_models;
        CarModel *best_seller;
        CarModel **models;

    public:
        CarType() : id(int()), max_sales(int()), num_of_models(int()), best_seller(nullptr), models(nullptr) {}
        CarType(int id) : id(id), max_sales(0), num_of_models(0), best_seller(nullptr), models(nullptr) {}
        ~CarType();
        CarType(const CarType &car_type) = default;
        CarType &operator=(const CarType &car_type) = default;

        // Parameter functions
        int &Id();
        int &Max_sales();
        CarModel &bestSeller();
        void updateBestSeller(CarModel *bestSeller);
        CarModel **Models();
        int numOfModels() const;

        // Operator overloads
        bool operator>(const CarType &) const;
        bool operator>=(const CarType &) const;
        bool operator<(const CarType &) const;
        bool operator<=(const CarType &) const;
        bool operator==(const CarType &) const;

        // Utility functions
        void AddModel(CarModel *new_model);
        void RemoveModel(const int id);
        void InitiateModels(const int num);
    };
}

#endif