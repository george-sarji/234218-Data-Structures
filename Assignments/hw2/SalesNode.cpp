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
        if (this->model->Sales() == node.model->Sales())
        {
            if (this->model->Type() == node.model->Type())
            {
                return this->model->Id() > node.model->Id();
            }
            return this->model->Type() > node.model->Type();
        }
        return this->model->Sales() > node.model->Sales();
    }

    bool structures::SalesNode::operator<(const SalesNode &node) const
    {
        return node > *this;
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
