#include "CarDealershipManager.h"
#include "Exception.h"
#include "TreeException.h"

namespace structures
{

    structures::CarDealershipManager::CarDealershipManager() : total_models(0), bestModel(nullptr),
                                                               sold_models(nullptr), non_sold_models(nullptr)
    {
        types = new Tree<CarType>();

        try
        {
            sold_models = new Tree<CarModel>();
        }
        catch (const std::bad_alloc &e)
        {
            delete types;
            throw MemoryError();
        }

        try
        {
            non_sold_models = new Tree<TypeNode>();
        }
        catch (const std::bad_alloc &e)
        {
            delete types;
            delete sold_models;
            throw MemoryError();
        }
    }

    void CarDealershipManager::AddCarType(int typeID, int numModels)
    {
        if (typeID <= 0 || numModels <= 0)
        {
            throw InvalidInput();
        }
        CarType *newType;
        try
        {
            // Allocate a new car type
            newType = new CarType(typeID);
            // Add the models for the car type.
            newType->InitiateModels(numModels);
        }
        catch (const std::bad_alloc &e)
        {
            if (newType != nullptr)
            {
                delete newType;
            }
            throw MemoryError();
        }
        try
        {
            // Add the type to the types tree.
            this->types = this->types->addIntersection(*newType);
        }
        catch (const structures::TreeException &error)
        {
            // We have a similar type already in the tree. Throw a failure.
            if (error.errorType() == ALREADY_EXISTS)
            {
                throw FailureError();
            }
        }
        // Check if the best seller is better than the global best seller.
        if (newType->bestSeller().isBetterSeller(*this->bestModel))
        {
            // We have a better seller. Change the best seller.
            this->bestModel = &newType->bestSeller();
        }
        // We need to add to the non-sold models tree.
        TypeNode *node;
        try
        {
            node = new TypeNode(typeID, numModels);
            this->non_sold_models = this->non_sold_models->addIntersection(*node);
        }
        catch (const std::bad_alloc &e)
        {
            // We have a memory error. Release everything and throw a memory error.
            this->types = this->types->removeIntersection(*newType);
            delete newType;
            if (node != nullptr)
                this->non_sold_models = this->non_sold_models->removeIntersection(*node);
            delete node;
            throw MemoryError();
        }
        // Increase the number of models.
        this->total_models += numModels;
        // Update the global variables.
        if (this->smallest_non_sold_type == nullptr || this->smallest_non_sold_type > node)
        {
            this->smallest_non_sold_type = node;
        }
    }

    void CarDealershipManager::RemoveCarType(int typeID)
    {
        if (typeID <= 0)
            throw InvalidInput();
        CarType *temp;
        Tree<CarType> *vertex;
        bool all_sold = false;
        try
        {
            temp = new CarType(typeID);
            vertex = this->types->findData(*temp);
        }
        catch (const structures::TreeException &e)
        {
            if (e.errorType() == DOESNT_EXIST)
            {
                throw FailureError();
            }
        }
        int total_models = vertex->Data()->numOfModels();
        // We found the relevant car type. Start removing the car models.
        // Get the relevant car type in the non-sold models, if it exists already.
        Tree<TypeNode> *typeNodeTree;
        try
        {
            typeNodeTree = this->non_sold_models->findData(*(new TypeNode(typeID)));
        }
        catch (const TreeException &e)
        {
            if (e.errorType() == DOESNT_EXIST)
            {
                all_sold = true;
            }
        }
        for (int i = 0; i < total_models; i++)
        {
            CarModel current = vertex->Data()->Models()[i];
            // Check if vehicle has already been sold once.
            if (current.Sales() != 0)
            {
                // Check in the sold models.
                this->sold_models->removeIntersection(current);
            }
            else if (all_sold)
            {
                // We have something problematic. Throw an error.
                throw Exception();
            }
            else
            {
                // There shouldn't be an error. Remove the current car model.
                typeNodeTree->Data()->getModels()->removeIntersection(current);
            }
        }
        // We can now remove the type itself.
        try
        {
            // Remove the car type from the non-sold tree
            this->non_sold_models->removeIntersection(*(typeNodeTree->Data()));
            // Remove the car type from the types tree
            this->types = this->types->removeIntersection(*(vertex->Data()));
        }
        catch (const TreeException &e)
        {
            if (e.errorType() == DOESNT_EXIST)
            {
                // We have a problem. Throw a general error, shouldn't arrive here logically.
                throw Exception();
            }
        }
        // Remove from the total models.
        this->total_models -= total_models;
        Tree<TypeNode> *newSmallest = this->non_sold_models->getSmallest();
        this->smallest_non_sold_type = (newSmallest != nullptr) ? newSmallest->Data() : nullptr;
    }

    void CarDealershipManager::SellCar(int typeID, int modelID)
    {
        if (typeID <= 0 || modelID < 0)
        {
            throw InvalidInput();
        }

        Tree<CarType> *temp = this->types->findData(typeID);
        if (temp == nullptr || temp->Data()->numOfModels() <= modelID)
        {
            throw FailureError();
        }
        CarModel current = temp->Data()->Models()[modelID];
        current.Sales()++;
        current.Grade() += 10;

        if (current.isBetterSeller(temp->Data()->bestSeller()))
        {
            temp->Data()->bestSeller() = current;
        }
        if (current.isBetterSeller(*this->bestModel))
        {
            this->bestModel = &current;
        }

        if (current.Sales() == 1)
        {
            //remove from unsold tree to sold tree
            // Tree<TypeNode> *
        }
        else
        {
            //update in sold models tree
        }
    }

    void CarDealershipManager::MakeComplaint(int typeID, int modelID, int t)
    {
        // Check if the initial parameters are correct.
        if (modelID < 0 || typeID <= 0 || t <= 0)
            throw InvalidInput();
        // Lets check for the type ID.
        Tree<CarType> *typeNode;
        try
        {
            typeNode = this->types->findData(*(new CarType(typeID)));
        }
        catch (const TreeException &e)
        {
            // We don't have a type with the given ID. Throw an error.
            if (e.errorType() == DOESNT_EXIST)
            {
                throw FailureError();
            }
        }
        // We have the type node. Check if the model ID is appropriate.
        if (typeNode->Data()->numOfModels() <= modelID)
            throw FailureError();
        // Check for the model in the models tree, according to the sales.
        CarModel currentModel = typeNode->Data()->Models()[modelID];
        if (currentModel.Sales() != 0)
        {
            // This model has been sold already. Check the sold vehicles tree.
            Tree<CarModel> *requested_model;
            try
            {
                requested_model = this->sold_models->findData(currentModel);
            }
            catch (const TreeException &e)
            {
                if (e.errorType() == DOESNT_EXIST)
                {
                    // Model does not exist in the sold models.
                    throw FailureError();
                }
            }
            // We have the requested model. Decrease the grade accordingly.
            currentModel.Grade() -= (10 / t);
            // Increase the complaints counter
            currentModel.Complaints()++;
            // Remove the model from the sold trees.
            this->sold_models = this->sold_models->removeIntersection(*requested_model->Data());
            // Add the new model.
            this->sold_models = this->sold_models->addIntersection(currentModel);
            // We can leave now.

            // TODO: Update the global variable for the best models, and for the smallest model in sold models.
        }
    }

    void CarDealershipManager::GetBestSellerModelByType(int typeID, int *modelID)
    {
        // Check if type ID is proper
        if (typeID < 0)
            throw InvalidInput();
        // Check if type ID is zero, for global variable.
        if (typeID == 0)
        {
            if (bestModel == nullptr)
            {
                // No best model; system is empty.
                throw FailureError();
            }
            // There is a best model. Give the model ID and exit.
            *modelID = bestModel->Id();
            return;
        }
        // It's not a global request. Search for the given type ID.
        else
        {
            Tree<CarType> *vertex;
            try
            {
                vertex = this->types->findData(*(new CarType(typeID)));
            }
            catch (const TreeException &e)
            {
                if (e.errorType() == DOESNT_EXIST)
                {
                    // The requested type ID does not exist. Give a failure.
                    throw FailureError();
                }
            }
            // The type that was requested is available. Return its best model.
            *modelID = vertex->Data()->bestSeller().Id();
            return;
        }
    }

    void CarDealershipManager::GetWorstModels(int numOfModels, int *types, int *models)
    {
    }

    void CarDealershipManager::Quit()
    {
    }

}