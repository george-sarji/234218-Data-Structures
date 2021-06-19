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
        int current_id = agency->getAgencyId();
        // Check if we have a parent.
        if (this->parents->getElementAt(current_id) == nullptr)
        {
            return nullptr;
        }
        else if (*this->parents->getElementAt(current_id) != -1)
        {
            // We have a valid parent. Let's carry on.
            int *parent = this->parents->getElementAt(current_id);
            // Call the findAgency on the parent.
            Agency *root = this->findAgency(this->elements->getElementAt(*parent));
            // Update the parent accordingly.
            this->parents->updateElementAt(current_id, new int(root->getAgencyId()));
            return root;
        }
        // We don't have a parent. Return the current agency.
        else
        {
            return this->elements->getElementAt(current_id);
        }
    }

    void structures::SetManager::uniteAgencies(int agency1, int agency2)
    {
        // We need to check which agency to merge into the other. Get each parent.
        int parent1 = *this->parents->getElementAt(agency1);
        int parent2 = *this->parents->getElementAt(agency2);
        // Check if the parents are actually available.
        if (parent1 == -1)
        {
            // Change the parent to the actual agency itself.
            parent1 = agency1;
        }
        // Do the same for the second agency.
        if (parent2 == -1)
        {
            parent2 = agency2;
        }

        // We should now start checking according to the sizes.
        int size1 = *this->sizes->getElementAt(parent1);
        int size2 = *this->sizes->getElementAt(parent2);
        // Let's check who needs to be the parent agency.
        int parent, child;
        if (size1 > size2)
        {
            // Parent needs to be parent1.
            parent = parent1;
            child = parent2;
        }
        else
        {
            parent = parent2;
            child = parent1;
        }
        // We now need to unite the agencies and set the sizes properly.
        int new_size = size1 + size2;
        // Update the size for the child and the parent.
        this->sizes->updateElementAt(parent, new int(new_size));
        this->sizes->updateElementAt(child, new int(new_size));
        // Get the child element and the parent element.
        Agency* parent_agency = this->elements->getElementAt(parent);
        Agency* child_agency = this->elements->getElementAt(child);
        // Update the parent agency with the new data.
        parent_agency->updateAgency(*child_agency);
        // We have updated the parent. We can now exit.
    }

    int structures::SetManager::getSize() const
    {
        return this->size;
    }
}
