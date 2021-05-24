#include "CarDealershipManager.h"

int main()
{
    structures::CarDealershipManager *m = new structures::CarDealershipManager();
    m->AddCarType(1, 1);
    m->AddCarType(2, 1);
    // m->AddCarType(3, 1);
    m->AddCarType(4,1);
    m->SellCar(4, 0);
    m->SellCar(4, 0);
    int model = 5;
    m->GetBestSellerModelByType(1, &model);
    std::cout << model << std::endl;
    m->MakeComplaint(4, 0, 1);
    m->MakeComplaint(4, 0, 2);
    m->RemoveCarType(4);
    m->RemoveCarType(1);
    m->RemoveCarType(2);
    m->Quit();
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