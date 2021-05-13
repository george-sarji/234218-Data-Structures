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

    template<class T>
    void structures::Tree<T>::clearTree() {
        if(!this) return;
        if(this->left)
            this->left->clearTree();
        if(this->right)
            this->right->clearTree();
        delete this;
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
    T *structures::Tree<T>::Data() const
    {
        return &this->data;
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
        // Check if first leaf in tree
        else if (this->data == T())
        {
            this->data = new_data;
            return this;
        }
        // Check if the data goes to the right subtree
        if (new_data > this->data)
        {
            // Is there a right subtree?
            if (this->right)
            {
                this->right = this->right->addIntersection(new_data);
            }
            // There isn't. Add a new subtree.
            else
            {
                this->right = new Tree(new_data);
            }
        }
        // Check if the data goes to the left subtree
        else if (new_data < this->data)
        {
            // Is there a left subtree?
            if (this->left)
            {
                this->left = this->left->addIntersection(new_data);
            }
            // There isn't. Add a new subtree.
            else
            {
                this->left = new Tree(new_data);
            }
        }
        // AVL does not allow equal keys, don't add.
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
        // Have we reached a leaf?
        if (!this)
        {
            return this;
        }
        // Check if this goes to the left subtree
        if (data < this->data)
        {
            // Is there a left subtree?
            if (this->left)
            {
                this->left = this->left->removeIntersection(data);
            }
            // There isn't. Nothing to remove.
            else
            {
                return this;
            }
        }
        // Check if this goes to the right subtree.
        else if (data > this->data)
        {
            // Is there a right subtree?
            if (this->right)
            {
                this->right = this->right->removeIntersection(data);
            }
            // There isn't. Nothing to remove.
            else
            {
                return this;
            }
        }

        // We have reached the intersection to delete
        else
        {
            // Is the intersection a leaf?
            if (this->left == nullptr && this->right == nullptr)
            {
                delete this;
                return nullptr;
            }
            // Does the intersection have two children?
            else if (this->left != nullptr && this->right != nullptr)
            {
                Tree<T> *next = this->inorderSuccessor();
                this->data = next->data;
                this->right = this->right->removeIntersection(next->data);
            }
            // The intersection has only one child
            else
            {
                Tree<T> *son = this->left ? this->left : this->right;
                delete this;
                return son;
            }
        }
        // Nothing to remove, exit.
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

    template <class T>
    Tree<T> *structures::Tree<T>::findData(T data) const
    {
        // Have we reached a deadend?
        if (!this)
        {
            return nullptr;
        }
        // Did we find the data?
        if (data == this->data)
        {
            return this;
        }
        // Should we check the right subtree?
        else if (data > this->data)
        {
            return this->right->findData(data);
        }
        // Should we check the left subtree?
        else if (data < this->data)
        {
            return this->left->findData(data);
        }
        // Shouldn't reach here
        return nullptr;
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
    root = root->addIntersection(12);
    // root = root->addIntersection(11);
    // root = root->addIntersection(-1);
    // root = root->addIntersection(1);
    // root = root->addIntersection(2);
    root->printInOrder();
    std::cout << std::endl;
    root = root->removeIntersection(5);
    root->printInOrder();
    std::cout << std::endl;
    root = root->addIntersection(5);
    root = root->removeIntersection(12);
    root->printInOrder();
    root->clearTree();
    return 0;
}