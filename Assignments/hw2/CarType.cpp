#include "CarType.h"

namespace structures
{
    structures::CarType::~CarType()
    {
        delete best_seller;
        delete models;
    }

    int &structures::CarType::Id()
    {
        return this->id;
    }

    int &structures::CarType::Max_sales()
    {
        return this->max_sales;
    }

    CarModel &structures::CarType::bestSeller()
    {
        return *(this->best_seller);
    }

    CarModel *structures::CarType::Models()
    {
        return this->models;
    }

    void structures::CarType::AddModel(CarModel &new_model)
    {
        if (new_model.Id() > this->num_of_models)
        {
            return;
        }
        this->models[new_model.Id()] = new_model;
    }

    void structures::CarType::RemoveModel(const int id)
    {
        if (id > this->num_of_models)
        {
            return;
        }
        CarModel *model = &(this->models[id]);
        delete model;
    }

    void structures::CarType::InitiateModels(const int num)
    {
        if (num <= 0)
        {
            return;
        }
        // Initiate the models array.
        this->models = new CarModel[num]();
        if (this->models == nullptr)
        {
            return;
        }
        this->num_of_models = num;
        for (int i = 0; i < num; i++)
        {
            CarModel *temp = new CarModel(i);
            this->AddModel(*temp);
        }
    }
}