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
        Tree<structures::CarModel> *models;
        Tree<CarModel> *smallest_model;

    public:
        TypeNode();
        TypeNode(int type_id, int num_of_models = 0);
        ~TypeNode();

        // Operator overloads
        bool operator>(const TypeNode &) const;
        bool operator>=(const TypeNode &) const;
        bool operator<(const TypeNode &) const;
        bool operator<=(const TypeNode &) const;
        bool operator==(const TypeNode &) const;

        // Utility functions
        int getTypeId();
        Tree<CarModel> *getModels();
        void updateModels(Tree<CarModel> *t);
        Tree<CarModel> *getSmallestModel();
        void updateSmallestModel(Tree<CarModel> *smallest_model);
    };
}

#endif