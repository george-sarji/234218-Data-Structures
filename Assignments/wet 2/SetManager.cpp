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
        if (*this->parents->getElementAt(current_id) != -1)
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
            return agency;
        }
    }

    Agency *structures::SetManager::uniteAgencies(int agency1, int agency2)
    {
        // Check if we have valid IDs.
        if (agency1 > this->size || agency2 > this->size)
        {
            throw InvalidInput();
        }
        // We have two valid agencies. Now we need to create the union according to the parents.
        int bigger, smaller;
        // Check which one is a smaller size.
        if (this->sizes->getElementAt(agency1) > this->sizes->getElementAt(agency2))
        {
            // Second is smaller than the first. We have to use that as reference for the union.
            smaller = agency2;
            bigger = agency1;
        }
        else
        {
            // First is smaller than the second. Use that for the union.
            smaller = agency1;
            bigger = agency2;
        }
        // Now wwe perform the union according to the algorithm in the lecture.
        this->parents->updateElementAt(smaller, new int(bigger));
        // Update the sizes.
        int new_size = *this->sizes->getElementAt(smaller) + *this->sizes->getElementAt(bigger);
        this->sizes->updateElementAt(smaller, new int(new_size));
        this->sizes->updateElementAt(bigger, new int(new_size));
        this->elements->getElementAt(bigger)->updateAgency(*this->elements->getElementAt(smaller));
        return this->elements->getElementAt(bigger);
    }

    int structures::SetManager::getSize() const
    {
        return this->size;
    }
}