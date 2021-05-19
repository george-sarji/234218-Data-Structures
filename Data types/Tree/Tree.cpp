#include "Tree.h"

int main()
{
    structures::Tree<int> *root = new structures::Tree<int>();
    /*correct output for the four next cases
	1 BF: 0 Height: 0
	2 BF: 0 Height: 1
	3 BF: 0 Height: 0 */

    //basic LL root change
    // root = root->addIntersection(3);
    // root = root->addIntersection(2);
    root = root->addIntersection(20);
    root = root->addIntersection(5);
    root = root->addIntersection(4);
    root = root->addIntersection(9);
    root = root->addIntersection(22);
    root = root->addIntersection(12);
    // root = root->addIntersection(11);
    // root = root->addIntersection(-1);
    // root = root->addIntersection(1);
    // root = root->addIntersection(2);
    root->printInOrder();
    root->printParent();
    root->Left()->printParent();
    root->Right()->printParent();
    root->Left()->Left()->printParent();
    root->Right()->Left()->printParent();
    root->Right()->Right()->printParent();


    std::cout << std::endl;
    root = root->removeIntersection(5);
    root->printInOrder();
    std::cout << std::endl;
    root = root->addIntersection(5);

    root->printParent();
    root->Left()->printParent();
    root->Right()->printParent();
    root->Left()->Right()->printParent();
    root->Right()->Left()->printParent();
    root->Right()->Right()->printParent();

    root = root->removeIntersection(12);
    root->printInOrder();

    root->printParent();
    root->Left()->printParent();
    root->Right()->printParent();
    root->Left()->Right()->printParent();
    root->Right()->Right()->printParent();

    root->clearTree();

    return 0;
}