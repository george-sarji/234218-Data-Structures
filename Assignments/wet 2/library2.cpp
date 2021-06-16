#include "library2.h"
#include "AgencyManager.h"

void *Init()
{
    structures::AgencyManager *manager;
    try
    {
        manager = new structures::AgencyManager();
    }
    catch (const std::bad_alloc &e)
    {
        return NULL;
    }
    return (void *)manager;
}

StatusType AddAgency(void *DS)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    try
    {
        ((structures::AgencyManager *)DS)->addAgency();
    }
    catch (const std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType SellCar(void *DS, int agencyID, int typeID, int k)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    try
    {
        ((structures::AgencyManager *)DS)->sellCar(agencyID, typeID, k);
    }
    catch (const std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch (const structures::InvalidInput &e)
    {
        return INVALID_INPUT;
    }
    catch (const structures::FailureError &e)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType UniteAgencies(void *DS, int agency1, int agency2)
{
    if (DS == NULL)
    {
        return INVALID_INPUT;
    }
    try
    {
        ((structures::AgencyManager *)DS)->uniteAgencies(agency1, agency2);
    }
    catch (const std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch (const structures::InvalidInput &e)
    {
        return INVALID_INPUT;
    }
    catch (const structures::FailureError &e)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetIthSoldType(void *DS, int agencyID, int i, int *res)
{
    if (DS == NULL)
    {
        return ALLOCATION_ERROR;
    }
    try
    {
        ((structures::AgencyManager *)DS)->getIthSoldType(agencyID, i, res);
    }
    catch (const std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch (const structures::InvalidInput &e)
    {
        return INVALID_INPUT;
    }
    catch (const structures::FailureError &e)
    {
        return FAILURE;
    }
    return SUCCESS;
}

void Quit(void **DS)
{
    structures::AgencyManager *manager = static_cast<structures::AgencyManager *>(*DS);
    delete manager;

    *DS = NULL;
}