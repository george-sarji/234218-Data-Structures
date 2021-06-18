#include "AgencyManager.h"
#include <stdio.h>

int main() {
    structures::AgencyManager *manager = new structures::AgencyManager();

    manager->addAgency();
    manager->addAgency();
    std::cout << manager->getTotalAgencies() << std::endl;
    manager->sellCar(1, 1, 1);
    manager->uniteAgencies(0, 1);
    int type = -1;
    manager->getIthSoldType(1, 0, &type);
    std::cout << type << std::endl;

    delete manager;
    return 0;
}