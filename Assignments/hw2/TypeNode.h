#ifndef TYPE_NODE_H_
#define TYPE_NODE_H_

#include "CarType.h"
#include "Tree.h"
namespace structures
{
    class TypeNode
    {
    private:
        int type_id;
        structures::Tree<CarModel> *models;
        CarModel *smallest_model;

    public:
        TypeNode(int type_id, int num_of_models);
        ~TypeNode();

        // Operator overloads
        bool operator>(const TypeNode &) const;
        bool operator>=(const TypeNode &) const;
        bool operator<(const TypeNode &) const;
        bool operator<=(const TypeNode &) const;

        // Utility functions
        int getTypeId();
        Tree<CarModel> *getModels();
        CarModel *getSmallestModel();
    };
}

#endif