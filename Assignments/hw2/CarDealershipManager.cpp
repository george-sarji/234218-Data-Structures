#include "CarDealershipManager.h"
#include "Exception.h"
#include "TreeException.h"

namespace structures
{
    structures::CarDealershipManager::~CarDealershipManager()
    {
        delete bestModel;
    }

    structures::CarDealershipManager::CarDealershipManager() : bestModel(nullptr), total_models(0),
                                                               smallest_sold_model(nullptr), smallest_non_sold_type(nullptr)
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
        try
        {
            car_sales = new Tree<SalesNode>();
        }
        catch (const std::bad_alloc &e)
        {
            delete types;
            delete sold_models;
            delete non_sold_models;
            throw MemoryError();
        }
    }

    void CarDealershipManager::AddCarType(int typeID, int numModels)
    {
        if (typeID <= 0 || numModels <= 0)
        {
            throw InvalidInput();
        }

        // Allocate a new car type
        CarType *newType = new CarType(typeID);
        try
        {
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
            this->types = this->types->addIntersection(newType);
        }
        catch (const structures::TreeException &error)
        {
            // We have a similar type already in the tree. Throw a failure.
            if (error.errorType() == ALREADY_EXISTS)
            {
                delete newType;
                throw FailureError();
            }
        }
        CarModel *old_best_seller = this->bestModel;
        if (this->bestModel == nullptr)
        {
            // Default best seller.
            this->bestModel = new CarModel(newType->bestSeller());
        }
        // Check if the best seller is better than the global best seller.
        else if (newType->bestSeller().isBetterSeller(*this->bestModel))
        {
            // We have a better seller. Change the best seller.
            this->bestModel = new CarModel(newType->bestSeller());
        }
        // We need to add to the non-sold models tree.
        TypeNode *node = nullptr;
        Tree<TypeNode> *best = nullptr;
        try
        {
            node = new TypeNode(typeID, numModels);
            this->non_sold_models = this->non_sold_models->addIntersection(node);
            best = this->non_sold_models->findData(*node);
        }
        catch (const std::bad_alloc &e)
        {
            // We have a memory error. Release everything and throw a memory error.
            this->types = this->types->removeIntersection(newType);
            delete this->bestModel;
            this->bestModel = old_best_seller;
            delete newType;
            throw MemoryError();
        }
        // Increase the number of models.
        this->total_models += numModels;
        // Update the global variables.
        if (this->smallest_non_sold_type == nullptr || *this->smallest_non_sold_type->Data() > *node)
        {
            this->smallest_non_sold_type = best;
        }
        for (int i = 0; i < numModels; i++)
        {
            this->car_sales = this->car_sales->addIntersection(new SalesNode(new CarModel(i, typeID)));
        }
    }

    void CarDealershipManager::RemoveCarType(int typeID)
    {
        if (typeID <= 0)
            throw InvalidInput();
        CarType *temp = nullptr;
        Tree<CarType> *vertex = nullptr;
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
        catch (const std::bad_alloc &e)
        {
            throw MemoryError();
        }
        if (vertex == nullptr)
        {
            throw FailureError();
        }
        int total_models_num = vertex->Data()->numOfModels();
        // We found the relevant car type. Start removing the car models.
        // Get the relevant car type in the non-sold models, if it exists already.
        Tree<TypeNode> *typeNodeTree = nullptr;
        TypeNode *temp_node = nullptr;
        try
        {
            temp_node = new TypeNode(typeID);
            if (this->non_sold_models != nullptr && this->non_sold_models->Data() != nullptr)
                typeNodeTree = this->non_sold_models->findData(*temp_node);
        }
        catch (const DoesntExist &e)
        {
            // We don't have a non-sold model.
        }
        catch (const std::bad_alloc &e)
        {
            delete temp;
            throw MemoryError();
        }

        // Check if we removed the best selling model's type.
        if (bestModel->Type() == typeID)
        {
            // We have removed the best seller model. We have to update.
            Tree<SalesNode> *temp_model = this->car_sales->getLargest();
            if (temp_model)
            {
                CarModel *old_best = this->bestModel;
                // We have a good best seller.
                try
                {
                    this->bestModel = new CarModel(*temp_model->Data()->getModel());
                }
                catch (const std::bad_alloc &e)
                {
                    delete temp;
                    throw MemoryError();
                }
                delete old_best;
            }
            else
            {
                // No best seller.
                delete this->bestModel;
                this->bestModel = nullptr;
            }
        }
        // Remove the actual models.
        for (int i = 0; i < total_models_num; i++)
        {
            CarModel current = *vertex->Data()->Models()[i];
            // Check if vehicle has already been sold once.
            if (current.Sales() != 0)
            {
                // Check in the sold models.
                this->sold_models = this->sold_models->removeIntersection(&current);
            }
            else
            {
                // There shouldn't be an error. Remove the current car model.
                typeNodeTree->Data()->updateModels(typeNodeTree->Data()->getModels()->removeIntersection(&current));
            }
        }
        if (this->sold_models == nullptr)
        {
            this->sold_models = new Tree<CarModel>();
        }
        // We can now remove the type itself.
        try
        {
            // Remove the car type from the non-sold tree
            if (this->non_sold_models != nullptr && this->non_sold_models->Data() != nullptr)
            {
                this->non_sold_models = this->non_sold_models->removeIntersection(temp_node);
            }
            // Remove the car type from the types tree
            this->types = this->types->removeIntersection(vertex->Data());
        }
        catch (const TreeException &e)
        {
            if (e.errorType() == DOESNT_EXIST)
            {
                delete temp;
                delete temp_node;
                // We have a problem. Throw a general error, shouldn't arrive here logically.
                throw Exception();
            }
        }
        if (this->non_sold_models == nullptr)
        {
            this->non_sold_models = new Tree<TypeNode>();
        }
        if (this->types == nullptr)
        {
            this->types = new Tree<CarType>();
        }
        // Remove from the total models.
        this->total_models -= total_models_num;
        Tree<TypeNode> *newSmallest = this->non_sold_models->getSmallest();
        this->smallest_non_sold_type = (newSmallest != nullptr) ? newSmallest : nullptr;

        // Delete the local pointers
        delete temp_node;
        delete temp;
    }

    void CarDealershipManager::SellCar(int typeID, int modelID)
    {
        // Check the given parameters.
        if (typeID <= 0 || modelID < 0)
            throw InvalidInput();
        // We need to find the given type.
        CarType type(typeID);
        // Find the requested data.
        Tree<CarType> *requested_node = this->types->findData(type);
        if (requested_node == nullptr)
        {
            // No type to remove.
            throw FailureError();
            return;
        }
        // We found the requested type for the sale. Check if it has the proper number of models.
        if (requested_node->Data()->numOfModels() <= modelID)
        {
            // No proper model numbers.
            throw FailureError();
        }
        // We need to search for the model. Check if the sales of the model are 0.
        CarModel *requested_model = requested_node->Data()->Models()[modelID];
        CarModel *old_model = nullptr;
        try
        {
            old_model = new CarModel(*requested_model);
        }
        catch (const std::bad_alloc &e)
        {
            throw MemoryError();
        }
        Tree<CarModel> *new_sold_node = nullptr;
        bool deleted_smallest = false;
        // We still have to update the data.
        requested_model->Sales()++;
        requested_model->Grade() += 10;
        if (requested_model->Sales() == 1)
        {
            // We need to search in the no sales tree.
            TypeNode requested_type(typeID);
            Tree<TypeNode> *sales_node = this->non_sold_models->findData(requested_type);
            // We are supposed to get a valid node.
            // We should have the model in here.
            // We have to add the new car model into the sales tree with a NEW variable
            try
            {
                sold_models = sold_models->addIntersection(new CarModel(*requested_model));
            }
            catch (const std::bad_alloc &e)
            {
                delete old_model;
                throw MemoryError();
            }
            new_sold_node = sold_models->findData(*requested_model);
            // We need to remove it from the given tree.
            // We have to update the car_sales tree.
            SalesNode car_sales_node(new CarModel(*old_model));
            // Check for the sales node, we have to update it.
            Tree<SalesNode> *node_for_update = this->car_sales->findData(car_sales_node);
            // We have to remove the given node, and add it with the requested model.
            this->car_sales = this->car_sales->removeIntersection(node_for_update->Data());
            // Check if we have no car sales now.
            if (this->car_sales == nullptr)
            {
                try
                {
                    this->car_sales = new Tree<SalesNode>();
                }
                catch (const std::bad_alloc &e)
                {
                    delete old_model;
                    throw MemoryError();
                }
            }
            // Add the new model.
            try
            {
                this->car_sales = this->car_sales->addIntersection(new SalesNode(new CarModel(*requested_model)));
            }
            catch (const std::bad_alloc &e)
            {
                delete old_model;
                throw MemoryError();
            }
            // We can now finally remove the requested model:
            Tree<CarModel> *models = sales_node->Data()->getModels();
            models = models->removeIntersection(old_model);
            sales_node->Data()->updateModels(models);
            // Check if this was the last model in the type in the non sold model tree.
            if (models == nullptr)
            {
                // Remove the sales node.
                // We have to update the smallest non sold type in the system.
                if (*sales_node->Data() == *this->smallest_non_sold_type->Data())
                {
                    // We can update according to the getSmallest.
                    this->non_sold_models = this->non_sold_models->removeIntersection(&requested_type);
                    // Check if we have a parent to the getSmallest.
                    Tree<TypeNode> *smallest = this->non_sold_models->getSmallest();
                    if (smallest->Parent() == nullptr)
                    {
                        this->smallest_non_sold_type = this->non_sold_models->getSmallest();
                    }
                    else
                    {
                        this->smallest_non_sold_type = smallest->Parent();
                    }
                }
                else
                {
                    this->non_sold_models = this->non_sold_models->removeIntersection(&requested_type);
                }
                // Check if we have a null tree.
                if (this->non_sold_models == nullptr)
                {
                    try
                    {
                        this->non_sold_models = new Tree<TypeNode>();
                    }
                    catch (const std::bad_alloc &e)
                    {
                        delete old_model;
                        throw MemoryError();
                    }
                }
            }
            else
            {
                sales_node->Data()->updateSmallestModel(sales_node->Data()->getModels()->getSmallest());
            }
            // We have to update the smallest sold node.
            if (this->smallest_sold_model == nullptr || *this->smallest_sold_model->Data() < *requested_model)
            {
                this->smallest_sold_model = new_sold_node;
            }
        }
        else
        {
            // Search in the sales tree and update accordingly.
            // We need the remove the requested model and add it again for the updated data.
            if (*old_model == *this->smallest_sold_model->Data())
            {
                deleted_smallest = true;
            }
            this->sold_models = this->sold_models->removeIntersection(old_model);
            if (this->sold_models == nullptr)
            {
                try
                {
                    this->sold_models = new Tree<CarModel>();
                }
                catch (const std::bad_alloc &e)
                {
                    delete old_model;
                    throw MemoryError();
                }
            }
            try
            {
                this->sold_models = this->sold_models->addIntersection(new CarModel(*requested_model));
            }
            catch (const std::bad_alloc &e)
            {
                delete old_model;
                throw MemoryError();
            }
            new_sold_node = this->sold_models->findData(*requested_model);
            // We have to update the car_sales tree.
            // We need to remove the old sales node and add the new one.
            SalesNode *new_node = nullptr, *to_remove = nullptr;
            try
            {
                new_node = new SalesNode(new CarModel(*requested_model));
                to_remove = new SalesNode(new CarModel(*old_model));
            }
            catch (const std::bad_alloc &e)
            {
                if (new_node != nullptr)
                    delete new_node;
                if (to_remove != nullptr)
                    delete to_remove;
                throw MemoryError();
            }
            this->car_sales = this->car_sales->removeIntersection(to_remove);
            if (this->car_sales == nullptr)
            {
                try
                {
                    this->car_sales = new Tree<SalesNode>();
                }
                catch (const std::bad_alloc &e)
                {
                    delete new_node;
                    delete to_remove;
                    delete old_model;
                    throw MemoryError();
                }
            }
            this->car_sales = this->car_sales->addIntersection(new_node);
            delete to_remove;
        }

        // Check if this is the new smallest sold model.
        if (this->smallest_sold_model == nullptr || deleted_smallest)
        {
            this->smallest_sold_model = new_sold_node;
        }
        else if (*requested_model < *this->smallest_sold_model->Data())
        {
            // We have a new smallest sold model.
            this->smallest_sold_model = new_sold_node;
        }
        // Let's check the best seller now.
        if (this->bestModel == nullptr)
        {
            try
            {
                this->bestModel = new CarModel(*requested_model);
            }
            catch (const std::bad_alloc &e)
            {
                delete old_model;
                throw MemoryError();
            }
        }
        else if (requested_model->isBetterSeller(*this->bestModel))
        {
            // Update the best model.
            delete this->bestModel;
            try
            {
                this->bestModel = new CarModel(*requested_model);
            }
            catch (const std::bad_alloc &e)
            {
                delete old_model;
                throw MemoryError();
            }
        }
        // Update the type-specific best seller.
        if (requested_model->isBetterSeller(requested_node->Data()->bestSeller()))
        {
            // Change the type's best seller.
            requested_node->Data()->updateBestSeller(requested_model);
        }

        delete old_model;
    }

    void CarDealershipManager::MakeComplaint(int typeID, int modelID, int t)
    {
        if (modelID < 0 || typeID <= 0 || t <= 0)
        {
            throw InvalidInput();
        }
        // We need to get the type.
        CarType *temp_type = nullptr;
        try
        {
            temp_type = new CarType(typeID);
        }
        catch (const std::bad_alloc &e)
        {
            throw MemoryError();
        }
        Tree<CarType> *current_type = nullptr;
        try
        {
            current_type = this->types->findData(*temp_type);
        }
        catch (const DoesntExist &e)
        {
            delete temp_type;
            throw FailureError();
        }
        // Did we find the given type?
        if (current_type == nullptr)
        {
            delete temp_type;
            throw FailureError();
        }
        // We have the type in the tree. Let's check for the model.
        if (current_type->Data()->numOfModels() <= modelID)
        {
            // No proper model.
            delete temp_type;
            throw FailureError();
        }
        // We have the model, confirmed. Fetch it.
        CarModel *current_model = current_type->Data()->Models()[modelID];
        CarModel *old_model = nullptr;
        try
        {
            old_model = new CarModel(*current_model);
        }
        catch (const std::bad_alloc &e)
        {
            delete temp_type;
            throw MemoryError();
        }
        // We should have sold it earlier, according to the documentation. That means we check in the sold_cars and the car_sales.
        current_model->Grade() -= 100 / t;
        current_model->Complaints()++;
        // We have to remove the current model and update it.
        this->sold_models = this->sold_models->removeIntersection(old_model);
        if (this->sold_models == nullptr)
        {
            try
            {
                this->sold_models = new Tree<CarModel>();
            }
            catch (const std::bad_alloc &e)
            {
                delete old_model;
                delete temp_type;
                throw MemoryError();
            }
        }
        try
        {
            this->sold_models = this->sold_models->addIntersection(new CarModel(*current_model));
        }
        catch (const std::bad_alloc &e)
        {
            delete old_model;
            delete temp_type;
            throw MemoryError();
        }
        this->smallest_sold_model = this->sold_models->getSmallest();
        delete old_model;
        delete temp_type;
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
            Tree<CarType> *vertex = nullptr;
            try
            {
                CarType type(typeID);
                vertex = this->types->findData(type);
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
        if (numOfModels <= 0)
            throw InvalidInput();
        if (numOfModels > this->total_models)
            throw FailureError();
        int c = 0;
        CarDealershipManager::getWorstModelsMInOrder(this->smallest_sold_model, this->smallest_non_sold_type, c, numOfModels, types, models);
    }

    void CarDealershipManager::Quit()
    {
        types->clearTree();
        sold_models->clearTree();
        non_sold_models->clearTree();
        car_sales->clearTree();
    }

    void CarDealershipManager::getWorstModelsMInOrder(Tree<CarModel> *sold_models, Tree<TypeNode> *non_sold_models, int &counter, int threshhold, int *type_array, int *model_array)
    {
        // Check if we have reached the threshold.
        if (counter == threshhold)
            return;
        Tree<CarModel> *prev_model = nullptr;
        Tree<TypeNode> *prev_node = nullptr;
        Tree<CarModel> *prev_type_model = nullptr;
        while (counter != threshhold)
        {
            // Check if we have to use the non-sold models.
            if (sold_models == nullptr || (sold_models->Data()->Grade() >= 0 && sold_models->Left() != nullptr && sold_models->Left()->Data()->Grade() <= 0) || (sold_models->Data()->Grade() >= 0))
            {
                // We need to use the non-sold models. Let's advance through them.
                // Do we have a left for the non_sold_models?
                if (non_sold_models->Left() != nullptr && prev_node != non_sold_models->Left())
                {
                    // We can go through this node.
                    prev_node = non_sold_models;
                    non_sold_models = non_sold_models->Left();
                }
                // Use the current.
                Tree<CarModel> *models = non_sold_models->Data()->getSmallestModel();
                while (counter != threshhold && models != nullptr)
                {
                    // Check if we have a left.
                    if (models->Left() != nullptr && prev_type_model != models->Left())
                    {
                        prev_type_model = models;
                        models = models->Left();
                        continue;
                    }
                    // Use the current model.
                    type_array[counter] = models->Data()->Type();
                    model_array[counter] = models->Data()->Id();
                    counter++;
                    // Check if we have a right.
                    if (models->Right() != nullptr && prev_type_model != models->Right())
                    {
                        prev_type_model = models;
                        models = models->Right();
                        continue;
                    }
                    prev_type_model = models;
                    models = models->Parent();
                }
                // Do we have a right for the non_sold_models?
                if (non_sold_models->Right() != nullptr && prev_node != non_sold_models->Right())
                {
                    // We can go through this node.
                    prev_node = non_sold_models;
                    non_sold_models = non_sold_models->Right();
                }
            }
            else
            {
                // Use the sold models.
                // Check if we have a left.
                if (sold_models->Left() != nullptr && prev_model != sold_models)
                {
                    prev_model = sold_models;
                    sold_models = sold_models->Left();
                    continue;
                }
                // Use the current.
                type_array[counter] = sold_models->Data()->Type();
                model_array[counter] = sold_models->Data()->Id();
                counter++;
                // Check if we have a right.
                if (sold_models->Right() != nullptr && prev_model != sold_models)
                {
                    prev_model = sold_models;
                    sold_models = sold_models->Right();
                    continue;
                }
                // Advance the pointer back up.
                prev_model = sold_models;
                sold_models = sold_models->Parent();
            }
        }
    }

}