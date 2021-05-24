#include "SalesNode.h"

namespace structures
{
    structures::SalesNode::~SalesNode()
    {
        if (model != nullptr)
        {
            delete model;
        }
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

    bool SalesNode::operator==(const SalesNode &node) const
    {
        return *(this->model) == *(node.model);
    }

    SalesNode *SalesNode::operator*()
    {
        return this;
    }

    SalesNode &SalesNode::operator=(const SalesNode &node)
    {
        *this->model = *node.model;
        return *this;
    }

}
