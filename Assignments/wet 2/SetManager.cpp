#include "SetManager.h"

namespace structures
{
    structures::SetManager::SetManager()
    {
        this->size = 0;
        this->elements = new DynamicArray<Agency>();
        this->parents = new DynamicArray<int>();
        this->sizes = new DynamicArray<int>();
    }

    structures::SetManager::~SetManager()
    {
        delete this->elements;
        delete this->sizes;
        delete this->parents;
    }

    void structures::SetManager::addAgency(Agency *agency)
    {
        this->size++;
        this->elements->addElement(agency);
        this->parents->addElement(new int(-1));
        this->sizes->addElement(new int(1));
    }

    void structures::SetManager::initiateAgency()
    {
        // Create a new structure according to the size.
        Agency *new_agency = nullptr;
        try
        {
            new_agency = new Agency(this->size);
        }
        catch (const std::bad_alloc &)
        {
            throw MemoryError();
        }
        this->addAgency(new_agency);
    }

    Agency *structures::SetManager::findAgency(Agency *agency)
    {
        // Get the current agency's ID.
        int current_id = agency->getAgencyId();
        // Check if we have a parent for the agency.
        int *parent = this->parents->getElementAt(current_id);
        if (parent == nullptr || *parent == -1 || *parent == current_id)
        {
            // We don't have a parent. Return the given agency.
            return this->elements->getElementAt(current_id);
        }
        else
        {
            // We have a parent. Check if they have a parent as well.
            // Create a mock parent.
            Agency *mock_parent = new Agency(*parent);
            // Look for the mock parent's parent.
            Agency *root = this->findAgency(mock_parent);
            delete mock_parent;
            // Check if we got any result.
            if (root == nullptr)
            {
                // We found the ultimate parent. Return it.
                return this->elements->getElementAt(*parent);
            }
            // We got an ultimate parent through root. Return it.
            return root;
        }
        // Not supposed to get here.
        return nullptr;
    }

    void structures::SetManager::uniteAgencies(int agency1, int agency2)
    {
        if (agency1 >= this->size || agency2 >= this->size)
        {
            throw FailureError();
        }
        // We need to get the parent agencies. Use findAgency.
        Agency mock1(agency1), mock2(agency2);
        Agency *parent1 = this->findAgency(&mock1);
        Agency *parent2 = this->findAgency(&mock2);
        // Check which one is supposed to be the proper parent.
        int size1 = *this->sizes->getElementAt(parent1->getAgencyId());
        int size2 = *this->sizes->getElementAt(parent2->getAgencyId());
        // Check which one has to be the parent, and which has to be the child.
        Agency *parent, *child;
        if (size1 > size2)
        {
            // Parent 1 is the proper parent.
            parent = parent1;
            child = parent2;
        }
        else
        {
            parent = parent2;
            child = parent1;
        }
        // We now have to update the agencies accordingly, update the sizes and exit.
        parent->updateAgency(*child);
        // Update the size for both items.
        int new_size = size1 + size2;
        // Update the size for the child and the parent.
        this->sizes->updateElementAt(parent, new int(new_size));
        this->sizes->updateElementAt(child, new int(new_size));
        // Get the child element and the parent element.
        Agency mock_parent(parent), mock_child(child);
        Agency *parent_agency = this->findAgency(&mock_parent);
        Agency *child_agency = this->findAgency(&mock_child);
        // Update the parent agency with the new data.
        parent_agency->updateAgency(*child_agency);
        // We have updated the parent. We can now exit.
        this->parents->updateElementAt(child, new int(parent));
    }

    int structures::SetManager::getSize() const
    {
        return this->size;
    }

    int SetManager::getParent(int typeID) const
    {
        if(*this->parents->getElementAt(typeID) == -1)
        {
            return typeID;
        }
        return getParent(*this->parents->getElementAt(typeID));
    }
}
