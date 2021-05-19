#include "TypeNode.h"

namespace structures
{
    structures::TypeNode::~TypeNode()
    {
    }

    structures::TypeNode::TypeNode(int type_id, int num_of_models)
    {
        this->models = new Tree<CarModel>();
        if (this->models == nullptr)
        {
            return;
        }
        this->smallest_model = nullptr;
        // Initiate the models array.
        for (int i = 0; i < num_of_models; i++)
        {
            CarModel *temp = new CarModel(i, this->type_id);
            this->models = this->models->addIntersection(*temp);
        }
    }

    bool structures::TypeNode::operator>(const TypeNode &node) const
    {
        return type_id > node.type_id;
    }
    bool structures::TypeNode::operator>=(const TypeNode &node) const
    {
        return type_id >= node.type_id;
    }
    bool structures::TypeNode::operator<(const TypeNode &node) const
    {
        return type_id < node.type_id;
    }
    bool structures::TypeNode::operator<=(const TypeNode &node) const
    {
        return type_id <= node.type_id;
    }

    // Utility functions
    int structures::TypeNode::getTypeId()
    {
        return this->type_id;
    }
    Tree<CarModel> *structures::TypeNode::getModels()
    {
        return this->models;
    }
    CarModel *structures::TypeNode::getSmallestModel()
    {
        return this->smallest_model;
    }
}