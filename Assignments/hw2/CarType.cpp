#include "CarModel.h"
#include "CarType.h"
namespace structures
{
    structures::CarType::~CarType()
    {
        for(int i = 0;i<num_of_models;i++) {
            delete models[i];
        }
        delete[] models;
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

    CarModel **structures::CarType::Models()
    {
        return this->models;
    }

    int structures::CarType::numOfModels() const
    {
        return this->num_of_models;
    }

    bool structures::CarType::operator>(const CarType& type) const
    {
        return this->id > type.id;
    }

    bool structures::CarType::operator>=(const CarType& type) const
    {
        return this->id >= type.id;
    }

    bool structures::CarType::operator<(const CarType& type) const
    {
        return this->id < type.id;
    }

    bool structures::CarType::operator<=(const CarType& type) const
    {
        return this->id <= type.id;
    }

    bool structures::CarType::operator==(const CarType& type) const
    {
        return this->id == type.id;
    }

    void structures::CarType::AddModel(CarModel *new_model)
    {
        if (new_model->Id() > this->num_of_models)
        {
            return;
        }
        this->models[new_model->Id()] = new_model;
    }

    void structures::CarType::RemoveModel(const int id)
    {
        if (id > this->num_of_models)
        {
            return;
        }
        CarModel *model = this->models[id];
        delete model;
    }

    void structures::CarType::InitiateModels(const int num)
    {
        if (num <= 0)
        {
            return;
        }
        // Initiate the models array.
        this->models = new CarModel *[num]();
        this->num_of_models = num;
        for (int i = 0; i < num; i++)
        {
            CarModel *temp = new CarModel(i, this->id);
            this->AddModel(temp);
            // Check if we have the smallest model ID.
            if (i == 0)
            {
                // Set the best seller to this model.
                this->best_seller = temp;
            }
        }
    }
}