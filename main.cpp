#include "CarDealershipManager.h"

int main()
{
    structures::CarDealershipManager *m = new structures::CarDealershipManager();
    m->AddCarType(10, 3);
    m->AddCarType(21, 5);
    m->RemoveCarType(21);
    m->SellCar(10, 1);
    m->SellCar(10, 2);
    m->SellCar(10, 1);
    m->MakeComplaint(10, 2, 5);
    int i = 0;
    m->GetBestSellerModelByType(10, &i);
    std::cout << i << std::endl;
    int *types = new int[3];
    int *models = new int[3];
    for (int i = 0; i < 3; i++)
    {
        types[i] = 0;
        models[i] = 0;
    }
    m->GetWorstModels(3, types, models);
    std::cout << types[0] << models[0] << std::endl;
    std::cout << types[1] << models[1] << std::endl;
    std::cout << types[2] << models[2] << std::endl;
    m->Quit();
    delete[] types;
    delete[] models;
    delete m;
    return 0;
}

//int main()
//{
//    using structures::Tree;
//    Tree<int> *tree = new Tree<int>();
//
//    tree = tree->addIntersection(new int(9));
//    tree = tree->addIntersection(new int(6));
//    tree = tree->addIntersection(new int(8));
//    tree = tree->addIntersection(new int(4));
//    tree = tree->addIntersection(new int(33));
//    tree = tree->addIntersection(new int(144));
//    tree = tree->addIntersection(new int(7));
//    tree = tree->addIntersection(new int(73));
//
//    tree->printInOrder();
//    std::cout << std::endl;
//    std::cout << *tree->Data() << ";" << tree->Height() << std::endl;
//    std::cout << *tree->Left()->Data() << ";" << tree->Left()->Height() << std::endl;
//    std::cout << *tree->Right()->Data() << ";" << tree->Right()->Height() << std::endl;
//    std::cout << *tree->Left()->Left()->Data() << ";" << tree->Left()->Left()->Height() << std::endl;
//    std::cout << *tree->Left()->Right()->Data() << ";" << tree->Left()->Right()->Height() << std::endl;
//    std::cout << *tree->Right()->Left()->Data() << ";" << tree->Right()->Left()->Height() << std::endl;
//    std::cout << *tree->Right()->Right()->Data() << ";" << tree->Right()->Right()->Height() << std::endl;
//    std::cout << *tree->Right()->Right()->Left()->Data() << ";" << tree->Right()->Right()->Left()->Height() << std::endl;
//
//
//    tree->clearTree();
//    delete tree;
//    return 0;
//}