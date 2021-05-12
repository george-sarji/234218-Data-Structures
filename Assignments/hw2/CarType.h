#include "CarModel.h"

namespace structures
{
    class CarType
    {
    private:
        int id, max_sales, num_of_models;
        CarModel *best_seller;
        CarModel *models;

    public:
        CarType(int id): id(id), max_sales(0), models(nullptr), best_seller(nullptr), num_of_models(0) {}
        ~CarType();

        // Parameter functions
        int& Id();
        int& Max_sales();
        CarModel& bestSeller();
        CarModel* Models();

        // Utility functions
        void AddModel(CarModel& new_model);
        void RemoveModel(const int id);
        void InitiateModels(const int num);
    };
}