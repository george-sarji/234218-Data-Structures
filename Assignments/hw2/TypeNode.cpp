#include "TypeNode.h"

namespace structures
{
    structures::TypeNode::TypeNode() : type_id(int()), models(new Tree<CarModel>()), smallest_model(nullptr)
    {

    }

    structures::TypeNode::~TypeNode()
    {
        models->clearTree();
    }

    structures::TypeNode::TypeNode(int type_id, int num_of_models)
    {
        this->models = new Tree<CarModel>();
        this->smallest_model = nullptr;
        this->type_id = type_id;
        // Initiate the models array.
        for (int i = 0; i < num_of_models; i++)
        {
            CarModel *temp = new CarModel(i, this->type_id);
            this->models = this->models->addIntersection(temp);
        }
        // Update the smallest model.
        this->smallest_model = this->models->getSmallest()->Data();
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

    bool structures::TypeNode::operator==(const TypeNode &node) const
    {
        return type_id == node.type_id;
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

    void structures::TypeNode::updateSmallestModel(CarModel* smallest_model)
    {
        this->smallest_model = smallest_model;
    }

}