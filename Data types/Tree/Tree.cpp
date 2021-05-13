#include "Tree.h"
#include <stdio.h>
#include <iostream>
#define MAX(left, right) (left > right ? left : right)

namespace structures
{
    template <class T>
    structures::Tree<T>::Tree(const Tree &tree) : data(tree->data), left(tree->left), right(tree->right)
    {
    }

    template <class T>
    Tree<T> *structures::Tree<T>::Left() const
    {
        return this->left;
    }

    template <class T>
    Tree<T> *structures::Tree<T>::Right() const
    {
        return this->right;
    }

    template <class T>
    int structures::Tree<T>::Height()
    {
        if (this->left && this->right)
        {
            return MAX(this->left->height, this->right->height) + 1;
        }
        else if (this->left)
        {
            return this->left->height + 1;
        }
        else if (this->right)
        {
            return this->right->height + 1;
        }
        return this->height;
    }

    template <class T>
    int structures::Tree<T>::getBalanceFactor() const
    {
        if (this->left && this->right)
        {
            return this->left->height - this->right->height;
        }
        else if (!this->left && !this->right)
        {
            return 0;
        }
        else if (this->left && !this->right)
        {
            return this->left->height;
        }
        else
        {
            return this->right->height;
        }
    }

    template <class T>
    T &structures::Tree<T>::operator*()
    {
        return this->data;
    }

    template <class T>
    Tree<T> &structures::Tree<T>::operator=(const Tree<T> &tree)
    {
        this->data = tree->data;
        this->left = tree->left;
        this->right = tree->right;
        this->height = tree->height;
        return this;
    }

    template <class T>
    bool structures::Tree<T>::operator<(const Tree &tree) const
    {
        return this->data < tree->data;
    }

    template <class T>
    bool structures::Tree<T>::operator<=(const Tree &tree) const
    {
        return this->data <= tree->data;
    }

    template <class T>
    bool structures::Tree<T>::operator>(const Tree &tree) const
    {
        return this->data > tree->data;
    }

    template <class T>
    bool structures::Tree<T>::operator>=(const Tree &tree) const
    {
        return this->data >= tree->data;
    }

    template <class T>
    bool structures::Tree<T>::operator==(const Tree &tree) const
    {
        return this->data == tree->data;
    }

    template <class T>
    Tree<T> *structures::Tree<T>::LeftLeft(Tree *root)
    {
        Tree *new_root = root->left;
        root->left = new_root->right;
        new_root->right = root;

        root->height = root->Height();
        new_root->height = new_root->Height();

        return new_root;
    }

    template <class T>
    Tree<T> *structures::Tree<T>::RightRight(Tree *root)
    {
        Tree *new_root = root->right;
        root->right = new_root->left;
        new_root->left = root;

        root->height = root->Height();
        new_root->height = new_root->Height();

        return new_root;
    }

    template <class T>
    Tree<T> *structures::Tree<T>::LeftRight(Tree *root)
    {
        Tree *new_root = root->left->right;
        Tree *tmp_left = new_root->left;
        Tree *tmp_right = new_root->right;

        new_root->left = root->left;
        new_root->right = root;
        (new_root->left)->right = tmp_left;
        (new_root->right)->left = tmp_right;

        (new_root->left)->height = new_root->left->Height();
        (new_root->right)->height = new_root->right->Height();
        new_root->height = new_root->Height();

        return new_root;
    }

    template <class T>
    Tree<T> *structures::Tree<T>::RightLeft(Tree *root)
    {
        Tree *new_root = root->right->left;
        Tree *tmp_left = new_root->left;
        Tree *tmp_right = new_root->right;

        new_root->left = root;
        new_root->right = root->right;
        (new_root->left)->right = tmp_left;
        (new_root->right)->left = tmp_right;

        (new_root->left)->height = new_root->left->Height();
        (new_root->right)->height = new_root->right->Height();
        new_root->height = new_root->Height();

        return new_root;
    }

    template <class T>
    Tree<T> *structures::Tree<T>::addIntersection(T new_data)
    {
        // Reached end of recursion, create new leaf.
        if (this == nullptr)
        {
            return new Tree(new_data);
        }
        else if(this->data == T()) {
            this->data = new_data;
            return this;
        }
        // Check if the data goes to the right subtree
        if (new_data > this->data)
        {
            if (this->right)
            {
                this->right = this->right->addIntersection(new_data);
            }
            else
            {
                this->right = new Tree(new_data);
            }
        }
        // Check if the data goes to the left subtree
        else if (new_data < this->data)
        {
            if (this->left)
            {
                this->left = this->left->addIntersection(new_data);
            }
            else
            {
                this->left = new Tree(new_data);
            }
        }
        // AVL does not allow equal keys
        else
        {
            return this;
        }

        this->height = this->Height();
        int balance_factor = this->getBalanceFactor();

        // Check the balance factors for the proper rotations
        // Left-Left rotation:
        if (balance_factor > 1 && this->left && this->left->getBalanceFactor() > -1)
        {
            return this->LeftLeft(this);
        }
        // Left-Right rotation:
        if (balance_factor > 1 && this->left && this->left->getBalanceFactor() < 0)
        {
            return this->LeftRight(this);
        }
        // Right-Right rotation:
        if (balance_factor < -1 && this->right && this->right->getBalanceFactor() < 1)
        {
            return this->RightRight(this);
        }
        // Right-Left rotation:
        if (balance_factor < -1 && this->right && this->right->getBalanceFactor() > 0)
        {
            return this->RightLeft(this);
        }

        return this;
    }

    template <class T>
    Tree<T> *structures::Tree<T>::removeIntersection(T data)
    {
        if (!this)
        {
            return this;
        }

        if (data < this->data)
        {
            if (this->left)
            {
                this->left = this->left->removeIntersection(data);
            }
            else
            {
                return this;
            }
        }
        else if (data > this->data)
        {
            if (this->right)
            {
                this->right = this->right->removeIntersection(data);
            }
            else
            {
                return this;
            }
        }
        //intersection to delete
        else
        {
            //intersection is a leaf
            if (this->left == nullptr && this->right == nullptr)
            {
                delete this;
                return nullptr;
            }
            //intersection has two children
            else if (this->left != nullptr && this->right != nullptr)
            {
                Tree<T> *next = this->inorderSuccessor();
                this->data = next->data;
                this->right = this->right->removeIntersection(next->data);
            }
            //intersection has only one child
            else
            {
                Tree<T> *son = this->left ? this->left : this->right;
                delete this;
                return son;
            }
        }

        if (this == nullptr)
        {
            return this;
        }

        this->height = this->Height();

        int balance_factor = this->getBalanceFactor();

        // Check the balance for each specific rotation
        if (balance_factor > 1 && this->left->getBalanceFactor() >= 0)
        {
            // Left Left.
            return this->LeftLeft(this);
        }
        else if (balance_factor < -1 && this->right->getBalanceFactor() <= 0)
        {
            return this->RightRight(this);
        }
        else if (balance_factor > 1 && this->left->getBalanceFactor() == -1)
        {
            return this->LeftRight(this);
        }
        else if (balance_factor < -1 && this->right->getBalanceFactor() == 1)
        {
            return this->RightLeft(this);
        }

        return this;
    }

    template <class T>
    void structures::Tree<T>::printInOrder() const
    {
        if (!this)
        {
            return;
        }
        this->left->printInOrder();
        std::cout << this->data << " ";
        this->right->printInOrder();
    }

    template <class T>
    void structures::Tree<T>::printPreOrder() const
    {
        if (!this)
            return;
        std::cout << this->data << " ";
        this->left->printPreOrder();
        this->right->printPreOrder();
    }

    template <class T>
    Tree<T> *structures::Tree<T>::inorderSuccessor()
    {
        Tree<T> *current = this->right;

        while (current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }

}

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
    // root = root->addIntersection(11);
    // root = root->addIntersection(-1);
    // root = root->addIntersection(1);
    // root = root->addIntersection(2);
    root->printInOrder();
    std::cout << std::endl;
    root = root->removeIntersection(10);
    root->printInOrder();
    return 0;
}

// /*
//  * testAVLTree.cpp
//  *
//  *  Created on: 19 ���� 2013
//  *      Author: shirel
//  */

// #include "AVLTree.h"
// #include <vector>
// #include <ostream>
// #include <random>
// #include <chrono>
// #include <algorithm>

// int main(){
// 	Tree<int, int> tree;

// 	//Specific Cases

// 	/*correct output for the four next cases
// 	1 BF: 0 Height: 0
// 	2 BF: 0 Height: 1
// 	3 BF: 0 Height: 0 */

// 	//basic LL root change
// 	tree.addNode(3,3);
// 	tree.addNode(2,2);
// 	tree.addNode(1,1);
// 	tree.printTree();
// 	tree.treeClear();

// 	//basic LR root change
// 	tree.addNode(3,3);
// 	tree.addNode(1,1);
// 	tree.addNode(2,2);
// 	tree.printTree();
// 	tree.treeClear();

// 	//basic RR root change
// 	tree.addNode(1,1);
// 	tree.addNode(2,2);
// 	tree.addNode(3,3);
// 	tree.printTree();
// 	tree.treeClear();

// 	//basic RL root change
// 	tree.addNode(1,1);
// 	tree.addNode(3,3);
// 	tree.addNode(2,2);
// 	tree.printTree();
// 	tree.treeClear();

// 	//basic LR not root change
// 	/*correct output
// 	1 BF: 0 Height: 0
// 	2 BF: 0 Height: 1
// 	3 BF: 0 Height: 0
// 	4 BF: 1 Height: 2
// 	5 BF: 0 Height: 0
// 	6 BF: 1 Height: 3
// 	7 BF: 0 Height: 0
// 	8 BF: 1 Height: 1 */
// 	tree.addNode(6,6);
// 	tree.addNode(4,4);
// 	tree.addNode(8,8);
// 	tree.addNode(3,3);
// 	tree.addNode(5,5);
// 	tree.addNode(7,7);
// 	tree.addNode(1,1);
// 	tree.addNode(2,2);
// 	tree.printTree();
// 	tree.treeClear();

// 	//basic LL not root change
// 	/*correct output
// 	1 BF: 0 Height: 0
// 	2 BF: 0 Height: 1
// 	3 BF: 0 Height: 0
// 	4 BF: 1 Height: 2
// 	5 BF: 0 Height: 0
// 	6 BF: 1 Height: 3
// 	7 BF: 0 Height: 0
// 	8 BF: 1 Height: 1 */
// 	tree.addNode(6,6);
// 	tree.addNode(4,4);
// 	tree.addNode(8,8);
// 	tree.addNode(3,3);
// 	tree.addNode(5,5);
// 	tree.addNode(7,7);
// 	tree.addNode(2,2);
// 	tree.addNode(1,1);
// 	tree.printTree();
// 	tree.treeClear();

// 	//basic RR not root change
// 	/*correct output
// 	 * 1 BF: 0 Height: 0
// 	2 BF: 0 Height: 1
// 	3 BF: 0 Height: 0
// 	5 BF: 1 Height: 2
// 	7 BF: 0 Height: 0*/
// 	tree.addNode(5,5);
// 	tree.addNode(7,7);
// 	tree.addNode(1,1);
// 	tree.addNode(2,2);
// 	tree.addNode(3,3);
// 	tree.printTree();
// 	tree.treeClear();

// 	//basic RL not root change
// 	/*correct output
// 	 * 1 BF: 0 Height: 0
// 	2 BF: 0 Height: 1
// 	3 BF: 0 Height: 0
// 	5 BF: 1 Height: 2
// 	7 BF: 0 Height: 0*/
// 	tree.addNode(5,5);
// 	tree.addNode(7,7);
// 	tree.addNode(1,1);
// 	tree.addNode(3,3);
// 	tree.addNode(2,2);
// 	tree.printTree();
// 	tree.treeClear();

// 	//root deletion no roll successor is a neighbour
// 	/*correct output
// 	2 BF: 0 Height: 0
// 	3 BF: 1 Height: 1
// 	5 BF: 1 Height: 2
// 	6 BF: 0 Height: 0*/
// 	tree.addNode(4,4);
// 	tree.addNode(5,5);
// 	tree.addNode(3,3);
// 	tree.addNode(2,2);
// 	tree.addNode(6,6);
// 	tree.removeNode(4);
// 	tree.printTree();
// 	tree.treeClear();

// 	//root deletion no roll successor is not a neighbour
// 	/*correct output
// 	2 BF: 0 Height: 0
// 	3 BF: 1 Height: 1
// 	5 BF: 0 Height: 2
// 	6 BF: 0 Height: 0
// 	7 BF: 0 Height: 1
// 	8 BF: 0 Height: 0 */
// 	tree.addNode(4,4);
// 	tree.addNode(3,3);
// 	tree.addNode(7,7);
// 	tree.addNode(2,2);
// 	tree.addNode(5,5);
// 	tree.addNode(8,8);
// 	tree.addNode(6,6);
// 	tree.removeNode(4);
// 	tree.printTree();
// 	tree.treeClear();

// 	//node deletion no roll successor is a neighbour case7
// 	/*correct output
// 	1 BF: 0 Height: 0
// 	2 BF: 1 Height: 1
// 	4 BF: 1 Height: 2
// 	5 BF: 0 Height: 0
// 	7 BF: 1 Height: 3
// 	8 BF: -1 Height: 1
// 	9 BF: 0 Height: 0*/
// 	tree.addNode(7,7);
// 	tree.addNode(3,3);
// 	tree.addNode(8,8);
// 	tree.addNode(2,2);
// 	tree.addNode(4,4);
// 	tree.addNode(9,9);
// 	tree.addNode(5,5);
// 	tree.addNode(1,1);
// 	tree.removeNode(3);
// 	tree.printTree();
// 	tree.treeClear();

// 	//node deletion no roll successor is not a neighbour case8
// 	/*correct output
// 	1 BF: 0 Height: 0
// 	2 BF: 1 Height: 1
// 	5 BF: 0 Height: 2
// 	6 BF: 0 Height: 0
// 	7 BF: 0 Height: 1
// 	8 BF: 0 Height: 0
// 	9 BF: 0 Height: 3
// 	10 BF: 0 Height: 0
// 	12 BF: -1 Height: 2
// 	13 BF: -1 Height: 1
// 	14 BF: 0 Height: 0*/
// 	tree.addNode(9,9);
// 	tree.addNode(3,3);
// 	tree.addNode(12,12);
// 	tree.addNode(2,2);
// 	tree.addNode(7,7);
// 	tree.addNode(10,10);
// 	tree.addNode(13,13);
// 	tree.addNode(1,1);
// 	tree.addNode(5,5);
// 	tree.addNode(8,8);
// 	tree.addNode(14,14);
// 	tree.addNode(6,6);
// 	tree.removeNode(3);
// 	tree.printTree();
// 	tree.treeClear();

// 	//node deletion causing LR case9
// 	/*correct output
// 	1 BF: 0 Height: 0
// 	2 BF: 0 Height: 1
// 	3 BF: 0 Height: 0
// 	4 BF: 0 Height: 2
// 	7 BF: -1 Height: 1
// 	8 BF: 0 Height: 0*/
// 	tree.addNode(7,7);
// 	tree.addNode(2,2);
// 	tree.addNode(8,8);
// 	tree.addNode(1,1);
// 	tree.addNode(4,4);
// 	tree.addNode(9,9);
// 	tree.addNode(3,3);
// 	tree.removeNode(9);
// 	tree.printTree();
// 	tree.treeClear();

// 	//node deletion causing LL case10
// 	/*correct output
// 	1 BF: 0 Height: 0
// 	2 BF: 1 Height: 1
// 	3 BF: 0 Height: 2
// 	4 BF: 0 Height: 0
// 	7 BF: 0 Height: 1
// 	8 BF: 0 Height: 0*/
// 	tree.addNode(7,7);
// 	tree.addNode(3,3);
// 	tree.addNode(8,8);
// 	tree.addNode(2,2);
// 	tree.addNode(4,4);
// 	tree.addNode(9,9);
// 	tree.addNode(1,1);
// 	tree.removeNode(9);
// 	tree.printTree();
// 	tree.treeClear();

// 	//node deletion causing RR case11
// 	/*correct output
// 	2 BF: 0 Height: 0
// 	3 BF: 0 Height: 1
// 	7 BF: 0 Height: 0
// 	8 BF: 0 Height: 2
// 	9 BF: -1 Height: 1
// 	10 BF: 0 Height: 0*/
// 	tree.addNode(3,3);
// 	tree.addNode(2,2);
// 	tree.addNode(8,8);
// 	tree.addNode(7,7);
// 	tree.addNode(1,1);
// 	tree.addNode(9,9);
// 	tree.addNode(10,10);
// 	tree.removeNode(1);
// 	tree.printTree();
// 	tree.treeClear();

// 	//node deletion causing RL case12
// 	/*correct output
// 	* 2 BF: 0 Height: 0
// 	3 BF: 1 Height: 1
// 	7 BF: 0 Height: 2
// 	10 BF: 0 Height: 0
// 	13 BF: 0 Height: 1
// 	14 BF: 0 Height: 0*/
// 	tree.addNode(3,3);
// 	tree.addNode(2,2);
// 	tree.addNode(13,13);
// 	tree.addNode(7,7);
// 	tree.addNode(1,1);
// 	tree.addNode(14,14);
// 	tree.addNode(10,10);
// 	tree.removeNode(1);
// 	tree.printTree();
// 	tree.treeClear();

// 	//double rotations RL and RR case 13
// 	/*correct output
// 	3 BF: 0 Height: 0
// 	5 BF: 0 Height: 1
// 	7 BF: 0 Height: 0
// 	9 BF: 0 Height: 2
// 	11 BF: 0 Height: 0
// 	13 BF: 1 Height: 1
// 	15 BF: 0 Height: 3
// 	17 BF: 0 Height: 0
// 	19 BF: -1 Height: 2
// 	21 BF: -1 Height: 1
// 	23 BF: 0 Height: 0*/
// 	tree.addNode(9,9);
// 	tree.addNode(3,3);
// 	tree.addNode(15,15);
// 	tree.addNode(1,1);
// 	tree.addNode(7,7);
// 	tree.addNode(13,13);
// 	tree.addNode(19,19);
// 	tree.addNode(5,5);
// 	tree.addNode(11,11);
// 	tree.addNode(17,17);
// 	tree.addNode(21,21);
// 	tree.addNode(23,23);
// 	tree.removeNode(1);
// 	tree.printTree();
// 	tree.treeClear();

// 	//double rotations RR and RR case 14
// 	/*correct output
// 	3 BF: 0 Height: 0
// 	7 BF: 0 Height: 1
// 	8 BF: 0 Height: 0
// 	9 BF: 0 Height: 2
// 	11 BF: 0 Height: 0
// 	13 BF: 1 Height: 1
// 	15 BF: 0 Height: 3
// 	17 BF: 0 Height: 0
// 	19 BF: -1 Height: 2
// 	21 BF: -1 Height: 1
// 	23 BF: 0 Height: 0*/
// 	tree.addNode(9,9);
// 	tree.addNode(3,3);
// 	tree.addNode(15,15);
// 	tree.addNode(1,1);
// 	tree.addNode(7,7);
// 	tree.addNode(13,13);
// 	tree.addNode(19,19);
// 	tree.addNode(8,8);
// 	tree.addNode(11,11);
// 	tree.addNode(17,17);
// 	tree.addNode(21,21);
// 	tree.addNode(23,23);
// 	tree.removeNode(1);
// 	tree.printTree();
// 	tree.treeClear();

// 	//double rotations RL and LL case 15
// 	/*correct output
// 	6 BF: 0 Height: 0
// 	7 BF: 1 Height: 1
// 	8 BF: 1 Height: 2
// 	9 BF: 0 Height: 0
// 	10 BF: 0 Height: 3
// 	11 BF: -1 Height: 1
// 	12 BF: 0 Height: 0
// 	15 BF: 0 Height: 2
// 	17 BF: 0 Height: 0
// 	18 BF: 0 Height: 1
// 	20 BF: 0 Height: 0
// 	 */
// 	tree.addNode(15,15);
// 	tree.addNode(10,10);
// 	tree.addNode(20,20);
// 	tree.addNode(8,8);
// 	tree.addNode(11,11);
// 	tree.addNode(17,17);
// 	tree.addNode(21,21);
// 	tree.addNode(7,7);
// 	tree.addNode(9,9);
// 	tree.addNode(12,12);
// 	tree.addNode(18,18);
// 	tree.addNode(6,6);
// 	tree.removeNode(21);
// 	tree.printTree();
// 	tree.treeClear();

// 	//double rotations LR and LL case 16
// 	/*correct output
// 	6 BF: 0 Height: 0
// 	7 BF: 1 Height: 1
// 	8 BF: 1 Height: 2
// 	9 BF: 0 Height: 0
// 	10 BF: 0 Height: 3
// 	11 BF: -1 Height: 1
// 	12 BF: 0 Height: 0
// 	15 BF: 0 Height: 2
// 	20 BF: 0 Height: 0
// 	21 BF: 0 Height: 1
// 	22 BF: 0 Height: 0 */
// 	tree.addNode(15,15);
// 	tree.addNode(10,10);
// 	tree.addNode(20,20);
// 	tree.addNode(8,8);
// 	tree.addNode(11,11);
// 	tree.addNode(17,17);
// 	tree.addNode(22,22);
// 	tree.addNode(7,7);
// 	tree.addNode(9,9);
// 	tree.addNode(12,12);
// 	tree.addNode(21,21);
// 	tree.addNode(6,6);
// 	tree.removeNode(17);
// 	tree.printTree();
// 	tree.treeClear();

// 	//delete node cause LR
// 	/*correct output
// 	 * 2 BF: 0 Height: 0
// 	3 BF: -1 Height: 2
// 	4 BF: 0 Height: 0
// 	6 BF: 1 Height: 1*/

// 	tree.addNode(5,5);
// 	tree.addNode(3,3);
// 	tree.addNode(6,6);
// 	tree.addNode(2,2);
// 	tree.addNode(4,4);
// 	tree.removeNode(5);
// 	tree.printTree();
// 	tree.treeClear();

// 	//delete node cause LR
// 	/*correct output
// 	 * 2 BF: 0 Height: 0
// 	3 BF: 0 Height: 1
// 	6 BF: 0 Height: 0*/
// 	tree.addNode(5,5);
// 	tree.addNode(3,3);
// 	tree.addNode(6,6);
// 	tree.addNode(2,2);
// 	tree.removeNode(5);
// 	tree.printTree();
// 	tree.treeClear();

// 	std::vector<int> vector;
// 	 for (int i=1; i<=100; i++) vector.push_back(i);

// 	 //Randomly insert and removes nodes
// 	 for (int k = 0; k < 20; ++k) {
// 		 unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
// 		 shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
// 		 for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); ++it){
// 				tree.addNode(*it,*it);

// 		 }
// 		 tree.printTree();
// 		 shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
// 		 for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); ++it){
// 				tree.removeNode(*it);
// 				tree.printTree();

// 		 }
// 		 tree.treeClear();
// 		 tree.printTree();
// 		 std::cout << '\n';
// 	}

// 	return 0;
// }
