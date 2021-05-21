#include "SalesNode.h"

namespace structures
{
    bool structures::SalesNode::operator>(const SalesNode &node) const
    {
        return this->model->isBetterSeller(*node.model);
    }

    bool structures::SalesNode::operator<(const SalesNode &node) const
    {
        return node.model->isBetterSeller(*this->model);
    }
}