#include "CarDealershipManager.h"
#include "Exception.h"
#include "TreeException.h"

namespace structures
{
    structures::CarDealershipManager::~CarDealershipManager() {
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
        // TODO: Add the new constructor for each update of best model pointers.
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
            // TODO: Fix the bug with the data update in addIntersection on the second add.
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
        TypeNode *node;
        Tree<TypeNode>* best;
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
        for (int i = 0; i < numModels; ++i)
        {
            this->car_sales = this->car_sales->addIntersection(new SalesNode(new CarModel(i, typeID)));
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
        TypeNode *temp_node;
        try
        {
            temp_node = new TypeNode(typeID);
            typeNodeTree = this->non_sold_models->findData(*temp_node);
        }
        catch (const TreeException &e)
        {
            if (e.errorType() == DOESNT_EXIST)
            {
                all_sold = true;
            }
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
                // We have a good best seller.
                this->bestModel = temp_model->Data()->getModel();
            }
            else
            {
                // No best seller.
                this->bestModel = nullptr;
            }
        }
        // Remove the actual models.
        for (int i = 0; i < total_models; i++)
        {
            CarModel current = *vertex->Data()->Models()[i];
            // Check if vehicle has already been sold once.
            if (current.Sales() != 0)
            {
                // Check in the sold models.
                this->sold_models->removeIntersection(&current);
            }
            else if (all_sold)
            {
                delete temp;
                delete temp_node;
                // We have something problematic. Throw an error.
                throw Exception();
            }
            else
            {
                // There shouldn't be an error. Remove the current car model.
                typeNodeTree->Data()->getModels()->removeIntersection(&current);
            }
        }
        // We can now remove the type itself.
        try
        {
            // Remove the car type from the non-sold tree
            this->non_sold_models->removeIntersection(typeNodeTree->Data());
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
        // Remove from the total models.
        this->total_models -= total_models;
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
        Tree<CarModel>* new_sold_node;
        // We still have to update the data.
        requested_model->Sales()++;
        requested_model->Grade() += 10;
        if (requested_model->Sales() == 1)
        {
        //     // We need to search in the no sales tree.
            TypeNode requested_type(typeID);
            Tree<TypeNode> *sales_node = this->non_sold_models->findData(requested_type);
            // We are supposed to get a valid node.
            // We should have the model in here.
            // We have to add the new car model into the sales tree with a NEW variable
            sold_models = sold_models->addIntersection(new CarModel(*requested_model));
            new_sold_node = sold_models->findData(*requested_model);
            // We need to remove it from the given tree.
            Tree<CarModel> *root = sales_node->Data()->getModels();
            // We have to update the car_sales tree.
            SalesNode car_sales_node(new CarModel(*requested_model));
            // Check for the sales node, we have to update it.
            Tree<SalesNode> *node_for_update = this->car_sales->findData(car_sales_node);
            // We have to remove the given node, and add it with the requested model.
            this->car_sales = this->car_sales->removeIntersection(node_for_update->Data());
            // Add the new model.
            this->car_sales = this->car_sales->addIntersection(new SalesNode(new CarModel(*requested_model)));
            // We can now finally remove the requested model:
            Tree<CarModel> *models = sales_node->Data()->getModels();
            models = models->removeIntersection(requested_model);
            sales_node->Data()->updateModels(models);
            // Check if this was the last model in the type in the non sold model tree.
            if (models == nullptr)
            {
                // Remove the sales node.
                // We have to update the smallest non sold type in the system.
                if (*sales_node->Data() == *this->smallest_non_sold_type->Data())
                {
                    // We can update according to the getSmallest.
                    this->smallest_non_sold_type = this->non_sold_models->getSmallest()->Parent();
                }
                this->non_sold_models = this->non_sold_models->removeIntersection(&requested_type);
            }
        }
        else
        {
            // Search in the sales tree and update accordingly.
            // We need the remove the requested model and add it again for the updated data.
            this->sold_models = this->sold_models->removeIntersection(requested_model);
            this->sold_models = this->sold_models->addIntersection(new CarModel(*requested_model));
            // We have to update the car_sales tree.
            // We need to remove the old sales node and add the new one.
            SalesNode *new_node = new SalesNode(requested_model);
            this->car_sales = this->car_sales->removeIntersection(new_node);
            this->car_sales = this->car_sales->addIntersection(new_node);
        }

        // // Check if this is the new smallest sold model.
        if (this->smallest_sold_model == nullptr)
        {
            this->smallest_sold_model = new_sold_node;
        }
        else if (*requested_model < *this->smallest_sold_model->Data())
        {
            // We have a new smallest sold model.
            // Delete the smallest model.
            delete this->smallest_sold_model;
            this->smallest_sold_model = new_sold_node;
        }
        // Let's check the best seller now.
        if (this->bestModel == nullptr)
        {
            this->bestModel = new CarModel(*requested_model);
        }
        else if (requested_model->isBetterSeller(*this->bestModel))
        {
            // Update the best model.
            delete this->bestModel;
            this->bestModel = new CarModel(*requested_model);
        }
    }

    void CarDealershipManager::MakeComplaint(int typeID, int modelID, int t)
    {
        // Check if the initial parameters are correct.
        if (modelID < 0 || typeID <= 0 || t <= 0)
            throw InvalidInput();
        // Lets check for the type ID.
        Tree<CarType> *typeNode;
        CarType *temp_type;
        try
        {
            temp_type = new CarType(typeID);
            typeNode = this->types->findData(*temp_type);
        }
        catch (const TreeException &e)
        {
            // We don't have a type with the given ID. Throw an error.
            if (e.errorType() == DOESNT_EXIST)
            {
                throw FailureError();
            }
        }
        catch (const std::bad_alloc &e)
        {
            throw MemoryError();
        }
        // We have the type node. Check if the model ID is appropriate.
        if (typeNode->Data()->numOfModels() <= modelID)
        {
            delete temp_type;
            throw FailureError();
        }
        // Check for the model in the models tree, according to the sales.
        CarModel currentModel = *typeNode->Data()->Models()[modelID];
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
                    delete temp_type;
                    // Model does not exist in the sold models.
                    throw FailureError();
                }
            }
            // We have the requested model. Decrease the grade accordingly.
            currentModel.Grade() -= (10 / t);
            // Increase the complaints counter
            currentModel.Complaints()++;
            // Remove the model from the sold trees.
            this->sold_models = this->sold_models->removeIntersection(requested_model->Data());
            // Add the new model.
            this->sold_models = this->sold_models->addIntersection(&currentModel);
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
    }

    void CarDealershipManager::Quit()
    {
        types->clearTree();
        sold_models->clearTree();
        non_sold_models->clearTree();
        car_sales->clearTree();
    }

}

//int main()
//{
//    structures::CarDealershipManager *m = new structures::CarDealershipManager();
//    m->AddCarType(1, 1);
//    m->AddCarType(2, 1);
//    m->AddCarType(3, 5);
//    m->SellCar(1, 0);
//    m->Quit();
//    delete m;
//    return 0;
//}