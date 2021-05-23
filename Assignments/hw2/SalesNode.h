#ifndef SALES_NODE_H_
#define SALES_NODE_H_
#include "CarModel.h"

namespace structures
{
    class SalesNode
    {
    private:
        CarModel *model;

    public:
        SalesNode(CarModel *model) : model(model) {}
        ~SalesNode();
        SalesNode() : model(nullptr) {}
        SalesNode(const SalesNode *node) : model(node->model) {}
        SalesNode& operator=(const SalesNode& node);

        void setModel(CarModel* model);
        CarModel* getModel() const;

        // Operator overloads
        bool operator>(const SalesNode &node) const;
        bool operator<(const SalesNode &node) const;
        bool operator==(const SalesNode& node) const;
        SalesNode* operator*();
    };
}

#endif
