#include "library.h"
#include "CarDealershipManager.h"
#include <iostream>

void *Init()
{
    structures::CarDealershipManager *manager = NULL;
    try
    {
        manager = new structures::CarDealershipManager();
    }
    catch (std::bad_alloc &e)
    {
        return NULL;
    }
    return manager;
}
StatusType AddCarType(void *DS, int typeID, int numOfModels)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    try
    {
        ((structures::CarDealershipManager *)DS)->AddCarType(typeID, numOfModels);
    }
    catch (std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch (structures::MemoryError &e)
    {
        return ALLOCATION_ERROR;
    }
    catch (structures::InvalidInput &e)
    {
        return INVALID_INPUT;
    }
    catch (structures::FailureError &e)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType RemoveCarType(void *DS, int typeID)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    try
    {
        ((structures::CarDealershipManager *)DS)->RemoveCarType(typeID);
    }
    catch (std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch (structures::MemoryError &e)
    {
        return ALLOCATION_ERROR;
    }
    catch (structures::InvalidInput &e)
    {
        return INVALID_INPUT;
    }
    catch (structures::FailureError &e)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType SellCar(void *DS, int typeID, int modelID)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    try
    {
        ((structures::CarDealershipManager *)DS)->SellCar(typeID, modelID);
    }
    catch (std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch (structures::MemoryError &e)
    {
        return ALLOCATION_ERROR;
    }
    catch (structures::InvalidInput &e)
    {
        return INVALID_INPUT;
    }
    catch (structures::FailureError &e)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType MakeComplaint(void *DS, int typeID, int modelID, int t)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    try
    {
        ((structures::CarDealershipManager *)DS)->MakeComplaint(typeID, modelID, t);
    }
    catch (std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch (structures::MemoryError &e)
    {
        return ALLOCATION_ERROR;
    }
    catch (structures::InvalidInput &e)
    {
        return INVALID_INPUT;
    }
    catch (structures::FailureError &e)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetBestSellerModelByType(void *DS, int typeID, int *modelID)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    try
    {
        ((structures::CarDealershipManager *)DS)->GetBestSellerModelByType(typeID, modelID);
    }
    catch (std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch (structures::MemoryError &e)
    {
        return ALLOCATION_ERROR;
    }
    catch (structures::InvalidInput &e)
    {
        return INVALID_INPUT;
    }
    catch (structures::FailureError &e)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetWorstModels(void *DS, int numOfModels, int *types, int *models)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    try
    {
        ((structures::CarDealershipManager *)DS)->GetWorstModels(numOfModels, types, models);
    }
    catch (std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch (structures::MemoryError &e)
    {
        return ALLOCATION_ERROR;
    }
    catch (structures::InvalidInput &e)
    {
        return INVALID_INPUT;
    }
    catch (structures::FailureError &e)
    {
        return FAILURE;
    }
    return SUCCESS;
}

void Quit(void **DS)
{
    structures::CarDealershipManager *dealership = static_cast<structures::CarDealershipManager *>(*DS);
    dealership->Quit();

    delete dealership;

    *DS = NULL;
}
