#include <iostream>
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

    manager->addAgency();
    manager->addAgency();
    manager->sellCar(1,1,3);
    manager->sellCar(2,2,2);
    manager->sellCar(0,-9,1);
    manager->sellCar(1,5,5);
    manager->sellCar(0,6,10);
    manager->sellCar(0,6,2);

    manager->getIthSoldType(1, 0, &type);
    std::cout << type << std::endl;
    manager->getIthSoldType(1, 1, &type);
    std::cout << type << std::endl;
    manager->getIthSoldType(0, 0, &type);
    std::cout << type << std::endl;
    manager->getIthSoldType(2, 0, &type);
    std::cout << type << std::endl;
    manager->getIthSoldType(0, 2, &type);
    std::cout << type << std::endl;
    manager->getIthSoldType(0, 3, &type);
    std::cout << type << std::endl;
    manager->getIthSoldType(1, 3, &type);
    std::cout << type << std::endl;

    delete manager;
    return 0;
}
