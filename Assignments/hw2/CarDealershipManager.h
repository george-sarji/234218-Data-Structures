#ifndef CAR_DEALERSHIP_MANAGER
#define CAR_DEALERSHIP_MANAGER

#include "CarType.h"
#include "Tree.h"

namespace structures
{
    class CarDealershipManager
    {
        private:
            Tree<CarType> types;
            Tree<Tree<CarModel>> grades;
            CarModel bestModel;

        public:
            CarDealershipManager();
            ~CarDealershipManager() = default;

            void AddCarType(int typeID, int numModels);
            void RemoveCarType(int typeID);
            void SellCar(int typeID, int modelID);
            void MakeComplaint(int typeID, int modelID, int t);
            void GetBestSellerModelByType(int typeID, int *modelID);
            void GetWorstModels(int numOfModels , int *types, int *models);
            void Quit();

    };
}

#endif