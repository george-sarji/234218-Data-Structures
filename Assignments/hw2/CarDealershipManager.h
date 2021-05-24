#ifndef CAR_DEALERSHIP_MANAGER
#define CAR_DEALERSHIP_MANAGER

#include "CarModel.h"
#include "CarType.h"
#include "Tree.h"
#include "TypeNode.h"
#include "Exception.h"
#include "SalesNode.h"

namespace structures
{
    class CarDealershipManager
    {
    private:
        CarModel *bestModel;
        int total_models;
        Tree<CarModel> *smallest_sold_model;
        Tree<TypeNode> *smallest_non_sold_type;
        Tree<CarType> *types;
        Tree<CarModel> *sold_models;
        Tree<TypeNode> *non_sold_models;
        Tree<SalesNode> *car_sales;

    public:
        CarDealershipManager();
        ~CarDealershipManager();

        void AddCarType(int typeID, int numModels);
        void RemoveCarType(int typeID);
        void SellCar(int typeID, int modelID);
        void MakeComplaint(int typeID, int modelID, int t);
        void GetBestSellerModelByType(int typeID, int *modelID);
        void GetWorstModels(int numOfModels, int *types, int *models);
        void Quit();
    };
}

#endif