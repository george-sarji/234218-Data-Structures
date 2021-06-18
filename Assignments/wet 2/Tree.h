#ifndef TREE_H_
#define TREE_H_

#include <stdio.h>
#include <iostream>
#include "TreeException.h"
namespace structures
{
#define MAX(left, right) (left > right ? left : right)

    template <class T>
    class Tree
    {
    private:
        T *data;
        Tree *left;
        Tree *right;
        Tree *parent;
        int height;

    public:
        Tree() = default;
        Tree(T *data, Tree *parent = nullptr, Tree *left = nullptr, Tree *right = nullptr) : data(data), left(left), right(right), parent(parent), height(0) {}
        Tree(const Tree &tree) = delete;
        ~Tree()
        {
            delete data;
        }

        void clearTree();
        void clearData();

        // Operator overloads
        T &operator*();
        Tree &operator=(const Tree &tree) = delete;
        bool operator>(const Tree &tree) const;
        bool operator>=(const Tree &tree) const;
        bool operator<(const Tree &tree) const;
        bool operator<=(const Tree &tree) const;
        bool operator==(const Tree &tree) const;
        Tree *findData(T &data);

        // Utility methods
        T *Data();
        Tree *Left() const;
        Tree *Right() const;
        Tree *Parent() const;
        int Height();
        int getBalanceFactor() const;
        Tree *LeftLeft(Tree *root);
        Tree *LeftRight(Tree *root);
        Tree *RightLeft(Tree *root);
        Tree *RightRight(Tree *root);
        void printInOrder() const;
        void printPreOrder() const;
        Tree *getSmallest();
        Tree *getLargest();

        void setLeft(Tree *new_left);
        void setRight(Tree *new_right);

        // Addition/removal functions
        Tree *addIntersection(T *data);
        Tree *removeIntersection(T *data);
        Tree *inorderSuccessor();

        T **getArrayFromTree(int size);
        void getArrayFromTreeAux(T **array, int *counter);

        // ! Required functions
        // LeftRight, RightLeft

        void printParent() const;
    };

    template <class T>
    void structures::Tree<T>::clearTree()
    {
        if (this->left != nullptr)
            this->left->clearTree();
        if (this->right != nullptr)
            this->right->clearTree();

        delete this;
    }

    template <class T>
    void structures::Tree<T>::clearData()
    {
        if (this->left != nullptr)
            this->left->clearData();
        if (this->right != nullptr)
            this->right->clearData();

        delete data;
    }

    template <class T>
    Tree<T> *structures::Tree<T>::Left() const
    {
        return this->left;
    }

    template <class T>
    void structures::Tree<T>::setLeft(Tree<T> *new_left)
    {
        if (this->left != nullptr)
        {
            // Free the current left.
            this->left->clearTree();
            delete this->left;
        }
        this->left = new_left;
    }

    template <class T>
    Tree<T> *structures::Tree<T>::Right() const
    {
        return this->right;
    }

    template <class T>
    void structures::Tree<T>::setRight(Tree<T> *new_right)
    {
        if (this->right != nullptr)
        {
            // Free the current right.
            this->right->clearTree();
            delete this->right;
        }
        this->right = new_right;
    }

    template <class T>
    Tree<T> *structures::Tree<T>::Parent() const
    {
        return this->parent;
    }

    template <class T>
    T *structures::Tree<T>::Data()
    {
        return this->data;
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
        return 0;
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
            return this->height;
        }
        else
        {
            return -this->height;
        }
    }

    template <class T>
    T &structures::Tree<T>::operator*()
    {
        return *(this->data);
    }

    template <class T>
    bool structures::Tree<T>::operator<(const Tree &tree) const
    {
        return *(this->data) < *(tree->data);
    }

    template <class T>
    bool structures::Tree<T>::operator<=(const Tree &tree) const
    {
        return *(this->data) <= *(tree->data);
    }

    template <class T>
    bool structures::Tree<T>::operator>(const Tree &tree) const
    {
        return *(this->data) > *(tree->data);
    }

    template <class T>
    bool structures::Tree<T>::operator>=(const Tree &tree) const
    {
        return *(this->data) >= *(tree->data);
    }

    template <class T>
    bool structures::Tree<T>::operator==(const Tree &tree) const
    {
        return *(this->data) == *(tree->data);
    }

    template <class T>
    Tree<T> *structures::Tree<T>::LeftLeft(Tree *root)
    {
        Tree *new_root = root->left;
        root->left = new_root->right;
        new_root->right = root;

        new_root->parent = root->parent;
        (new_root->left)->parent = new_root;
        (new_root->right)->parent = new_root;
        if ((new_root->left)->left)
        {
            ((new_root->left)->left)->parent = new_root->left;
        }
        if ((new_root->left)->right)
        {
            ((new_root->left)->right)->parent = new_root->left;
        }

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

        new_root->parent = root->parent;
        (new_root->left)->parent = new_root;
        (new_root->right)->parent = new_root;
        if ((new_root->right)->left)
        {
            ((new_root->right)->left)->parent = new_root->left;
        }
        if ((new_root->right)->right)
        {
            ((new_root->right)->right)->parent = new_root->left;
        }

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

        new_root->parent = root->parent;
        (new_root->left)->parent = new_root;
        (new_root->right)->parent = new_root;
        if (new_root->left->left)
        {
            ((new_root->left)->left)->parent = new_root->left;
        }
        if (new_root->left->right)
        {
            ((new_root->left)->right)->parent = new_root->left;
        }
        if (new_root->right->left)
        {
            ((new_root->right)->left)->parent = new_root->right;
        }
        if (new_root->right->right)
        {
            ((new_root->right)->right)->parent = new_root->right;
        }

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

        new_root->parent = root->parent;
        (new_root->left)->parent = new_root;
        (new_root->right)->parent = new_root;
        if (new_root->left->left)
        {
            ((new_root->left)->left)->parent = new_root->left;
        }
        if (new_root->left->right)
        {
            ((new_root->left)->right)->parent = new_root->left;
        }
        if (new_root->right->left)
        {
            ((new_root->right)->left)->parent = new_root->right;
        }
        if (new_root->right->right)
        {
            ((new_root->right)->right)->parent = new_root->right;
        }

        (new_root->left)->height = new_root->left->Height();
        (new_root->right)->height = new_root->right->Height();
        new_root->height = new_root->Height();

        return new_root;
    }

    template <class T>
    Tree<T> *structures::Tree<T>::addIntersection(T *new_data)
    {
        // Check if first leaf in tree
        if (data == nullptr)
        {
            this->data = new_data;
            return this;
        }
        // Check if the data goes to the right subtree
        if (*new_data > *this->data)
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
            (this->right)->parent = this;
        }
            // Check if the data goes to the left subtree
        else if (*new_data < *this->data)
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
            (this->left)->parent = this;
        }
            // AVL does not allow equal keys, don't add.
        else
        {
            throw AlreadyExists();
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
    Tree<T> *structures::Tree<T>::removeIntersection(T *data)
    {
        // Check if this goes to the left subtree
        if (*data < *this->data)
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
        else if (*data > *this->data)
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
                T *temp = this->data;
                this->data = next->data;
                next->data = temp;
                this->right = this->right->removeIntersection(next->data);
            }
                // The intersection has only one child
            else
            {
                Tree<T> *son = this->left ? this->left : this->right;
                son->parent = this->parent;
                delete this;
                return son;
            }
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
        if (this->left)
        {
            this->left->printInOrder();
        }
        std::cout << *this->data << " ";
        if (this->right)
        {
            this->right->printInOrder();
        }
    }

    template <class T>
    void structures::Tree<T>::printPreOrder() const
    {
        std::cout << *this->data << " ";
        if (this->left)
        {
            this->left->printPreOrder();
        }
        if (this->right)
        {
            this->right->printPreOrder();
        }
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
    Tree<T> *structures::Tree<T>::findData(T &data)
    {
        if (this->data == nullptr)
        {
            throw DoesntExist();
        }
        // Did we find the data?
        if (data == *this->data)
        {
            return this;
        }
            // Should we check the right subtree?
        else if (data > *this->data && this->right != nullptr)
        {
            return this->right->findData(data);
        }
            // Should we check the left subtree?
        else if (data < *this->data && this->left != nullptr)
        {
            return this->left->findData(data);
        }
            // Did we reach a deadend?
        else if (this->left == nullptr && this->right == nullptr)
        {
            throw DoesntExist();
        }
        // Shouldn't reach here
        throw DoesntExist();
    }

    template <class T>
    void structures::Tree<T>::printParent() const
    {
        if ((this->parent) == nullptr)
        {
            std::cout << "no parent" << std::endl;
            return;
        }

        std::cout << "parent is:" << *((this->parent)->Data()) << std::endl;
        return;
    }

    template <class T>
    Tree<T> *structures::Tree<T>::getSmallest()
    {
        if (this->left != nullptr)
        {
            return this->left->getSmallest();
        }
        return this;
    }

    template <class T>
    Tree<T> *structures::Tree<T>::getLargest()
    {
        if (this->right)
        {
            return this->right->getSmallest();
        }
        return this;
    }

    template <class T>
    T **Tree<T>::getArrayFromTree(int size)
    {
        if(this->data == nullptr)
        {
            return nullptr;
        }
        T **array = new T*[size];
        int *counter = new int(0);
        this->getArrayFromTreeAux(array, counter);
        delete counter;
        return array;
    }

    template <class T>
    void Tree<T>::getArrayFromTreeAux(T **array, int *counter)
    {
        if (this->left)
        {
            this->left->getArrayFromTreeAux(array, counter);
        }

        T *temp_data = new T(*data);
        array[*counter] = temp_data;
        (*counter)++;

        if (this->right)
        {
            this->right->getArrayFromTreeAux(array, counter);
        }
    }

}

#endif
