#include "CarModel.h"

namespace structures
{
    int &structures::CarModel::Sales()
    {
        return this->sales;
    }

    int &structures::CarModel::Complaints()
    {
        return this->complaints;
    }

    int &structures::CarModel::Grade()
    {
        return this->grade;
    }

    int &structures::CarModel::Id()
    {
        return this->id;
    }

    bool structures::CarModel::isBetterModel(const CarModel &model) const
    {
        if (this->grade == model.grade)
        {
            if (this->type == model.type)
            {
                return this->id < model.id;
            }
            return this->type < model.type;
        }
        return this->grade > model.grade;
    }

    bool structures::CarModel::operator>(const CarModel &model) const
    {
        return this->id > model.id;
    }

    bool structures::CarModel::operator>=(const CarModel &model) const
    {
        return this->id >= model.id;
    }

    bool structures::CarModel::operator<(const CarModel &model) const
    {
        return this->id < model.id;
    }

    bool structures::CarModel::operator<=(const CarModel &model) const
    {
        return this->id <= model.id;
    }

    bool structures::CarModel::operator==(const CarModel &model) const
    {
        return this->id == model.id;
    }
}