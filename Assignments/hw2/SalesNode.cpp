#include "SalesNode.h"

namespace structures
{
    structures::SalesNode::~SalesNode() {
        delete model;
    }

    bool structures::SalesNode::operator>(const SalesNode &node) const
    {
        return this->model->isBetterSeller(*node.model);
    }

    bool structures::SalesNode::operator<(const SalesNode &node) const
    {
        return node.model->isBetterSeller(*this->model);
    }

    void structures::SalesNode::setModel(CarModel *model)
    {
        this->model = model;
    }

    CarModel *structures::SalesNode::getModel() const
    {
        return this->model;
    }

}