#ifndef RankTree_H_
#define RankTree_H_

#include <stdio.h>
#include <iostream>
#include "TreeException.h"
#include "Exception.h"
namespace structures
{
#define MAX(left, right) (left > right ? left : right)

    template <class T>
    class RankTree
    {
    private:
        T *data;
        int num_of_subtrees;
        RankTree *left;
        RankTree *right;
        RankTree *parent;
        int height;

    public:
        RankTree() = default;
        explicit RankTree(T *data, RankTree *parent = nullptr, RankTree *left = nullptr, RankTree *right = nullptr) : data(data), num_of_subtrees(1), left(left), right(right), parent(parent), height(0) {}
        RankTree(const RankTree &RankTree) = delete;
        ~RankTree()
        {
            delete data;
        }

        void clearRankTree();
        void clearData();

        // Operator overloads
        T &operator*();
        RankTree &operator=(const RankTree &RankTree) = delete;
        bool operator>(const RankTree &RankTree) const;
        bool operator>=(const RankTree &RankTree) const;
        bool operator<(const RankTree &RankTree) const;
        bool operator<=(const RankTree &RankTree) const;
        bool operator==(const RankTree &RankTree) const;
        RankTree *findData(T& data);

        // Utility methods
        T *Data();
        RankTree *Left() const;
        RankTree *Right() const;
        RankTree* Parent() const;
        int Height();
        int getBalanceFactor() const;
        RankTree *LeftLeft(RankTree *root);
        RankTree *LeftRight(RankTree *root);
        RankTree *RightLeft(RankTree *root);
        RankTree *RightRight(RankTree *root);
        void printInOrder() const;
        void printPreOrder() const;
        RankTree *getSmallest();
        RankTree *getLargest();

        void setLeft(RankTree *new_left);
        void setRight(RankTree *new_right);

        // Addition/removal functions
        RankTree *addIntersection(T *data);
        RankTree *removeIntersection(T *data);
        RankTree *inorderSuccessor();

        int numOfSubtrees() const;
        void updateRank();
        int getRank(const T& data) const;
        int getRankAux(const T& data, int counter = 0) const;
        RankTree* Select(int index);
        void fullRankUpdate();

        T** getArrayFromTree();
        void getArrayFromTreeAux(T** array, int* counter);

        // ! Required functions
        // LeftRight, RightLeft

        void printParent() const;
    };

    template <class T>
    void structures::RankTree<T>::clearRankTree()
    {
        if (this->left != nullptr)
            this->left->clearRankTree();
        if (this->right != nullptr)
            this->right->clearRankTree();

        delete this;
    }

    template <class T>
    void structures::RankTree<T>::clearData()
    {
        if (this->left != nullptr)
            this->left->clearData();
        if (this->right != nullptr)
            this->right->clearData();

        delete data;
    }

    template <class T>
    RankTree<T> *structures::RankTree<T>::Left() const
    {
        return this->left;
    }

    template <class T>
    void structures::RankTree<T>::setLeft(RankTree<T> *new_left)
    {
        if (this->left != nullptr)
        {
            // Free the current left.
            this->left->clearRankTree();
            delete this->left;
        }
        this->left = new_left;
    }

    template <class T>
    RankTree<T> *structures::RankTree<T>::Right() const
    {
        return this->right;
    }

    template <class T>
    void structures::RankTree<T>::setRight(RankTree<T> *new_right)
    {
        if (this->right != nullptr)
        {
            // Free the current right.
            this->right->clearRankTree();
            delete this->right;
        }
        this->right = new_right;
    }


    template<class T>
    RankTree<T>* structures::RankTree<T>::Parent() const {
        return this->parent;
    }

    template <class T>
    T *structures::RankTree<T>::Data()
    {
        return this->data;
    }

    template <class T>
    int structures::RankTree<T>::Height()
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
    int structures::RankTree<T>::getBalanceFactor() const
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
            return - this->height;
        }
    }

    template <class T>
    T &structures::RankTree<T>::operator*()
    {
        return *(this->data);
    }

    template <class T>
    bool structures::RankTree<T>::operator<(const RankTree &RankTree) const
    {
        return *(this->data) < *(RankTree->data);
    }

    template <class T>
    bool structures::RankTree<T>::operator<=(const RankTree &RankTree) const
    {
        return *(this->data) <= *(RankTree->data);
    }

    template <class T>
    bool structures::RankTree<T>::operator>(const RankTree &RankTree) const
    {
        return *(this->data) > *(RankTree->data);
    }

    template <class T>
    bool structures::RankTree<T>::operator>=(const RankTree &RankTree) const
    {
        return *(this->data) >= *(RankTree->data);
    }

    template <class T>
    bool structures::RankTree<T>::operator==(const RankTree &RankTree) const
    {
        return *(this->data) == *(RankTree->data);
    }

    template <class T>
    RankTree<T> *structures::RankTree<T>::LeftLeft(RankTree *root)
    {
        RankTree *new_root = root->left;
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

        root->updateRank();
        new_root->updateRank();

        return new_root;
    }

    template <class T>
    RankTree<T> *structures::RankTree<T>::RightRight(RankTree *root)
    {
        RankTree *new_root = root->right;
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

        root->updateRank();
        new_root->updateRank();

        return new_root;
    }

    template <class T>
    RankTree<T> *structures::RankTree<T>::LeftRight(RankTree *root)
    {
        RankTree *new_root = root->left->right;
        RankTree *tmp_left = new_root->left;
        RankTree *tmp_right = new_root->right;

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

        (new_root->left)->updateRank();
        (new_root->right)->updateRank();
        new_root->updateRank();

        return new_root;
    }

    template <class T>
    RankTree<T> *structures::RankTree<T>::RightLeft(RankTree *root)
    {
        RankTree *new_root = root->right->left;
        RankTree *tmp_left = new_root->left;
        RankTree *tmp_right = new_root->right;

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

        (new_root->left)->updateRank();
        (new_root->right)->updateRank();
        new_root->updateRank();

        return new_root;
    }

    template <class T>
    RankTree<T> *structures::RankTree<T>::addIntersection(T *new_data)
    {
        // Check if first leaf in RankTree
        if (data == nullptr)
        {
            this->data = new_data;
            this->num_of_subtrees = 1;
            return this;
        }
        // Check if the data goes to the right subRankTree
        if (*new_data > *this->data)
        {
            // Is there a right subRankTree?
            if (this->right)
            {
                this->right = this->right->addIntersection(new_data);
            }
                // There isn't. Add a new subRankTree.
            else
            {
                this->right = new RankTree(new_data);
            }
            (this->right)->parent = this;
        }
            // Check if the data goes to the left subRankTree
        else if (*new_data < *this->data)
        {
            // Is there a left subRankTree?
            if (this->left)
            {
                this->left = this->left->addIntersection(new_data);
            }
                // There isn't. Add a new subRankTree.
            else
            {
                this->left = new RankTree(new_data);
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
        this->updateRank();

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
    RankTree<T> *structures::RankTree<T>::removeIntersection(T *data)
    {
        // Check if this goes to the left subRankTree
        if (*data < *this->data)
        {
            // Is there a left subRankTree?
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
            // Check if this goes to the right subRankTree.
        else if (*data > *this->data)
        {
            // Is there a right subRankTree?
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
                RankTree<T> *next = this->inorderSuccessor();
                T* temp = this->data;
                this->data = next->data;
                next->data = temp;
                this->right = this->right->removeIntersection(next->data);
            }
                // The intersection has only one child
            else
            {
                RankTree<T> *son = this->left ? this->left : this->right;
                son->parent = this->parent;
                delete this;
                return son;
            }
        }

        this->height = this->Height();
        int balance_factor = this->getBalanceFactor();
        this->updateRank();

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
    void structures::RankTree<T>::printInOrder() const
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
    void structures::RankTree<T>::printPreOrder() const
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
    RankTree<T> *structures::RankTree<T>::inorderSuccessor()
    {
        RankTree<T> *current = this->right;

        while (current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }

    template <class T>
    RankTree<T> *structures::RankTree<T>::findData(T& data)
    {
        if(this->data == nullptr) {
            throw DoesntExist();
        }
        // Did we find the data?
        if (data == *this->data)
        {
            return this;
        }
            // Should we check the right subRankTree?
        else if (data > *this->data && this->right != nullptr)
        {
            return this->right->findData(data);
        }
            // Should we check the left subRankTree?
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
    void structures::RankTree<T>::printParent() const
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
    RankTree<T> *structures::RankTree<T>::getSmallest()
    {
        if (this->left != nullptr)
        {
            return this->left->getSmallest();
        }
        return this;
    }

    template <class T>
    RankTree<T> *structures::RankTree<T>::getLargest()
    {
        if (this->right)
        {
            return this->right->getSmallest();
        }
        return this;
    }

    template<class T>
    void RankTree<T>::updateRank()
    {
        if(this->left && this->right)
        {
            this->num_of_subtrees = this->left->num_of_subtrees + this->right->num_of_subtrees + 1;
            return;
        }
        else if(this->left && !this->right)
        {
            this->num_of_subtrees = this->left->num_of_subtrees + 1;
            return;
        }
        else if(!this->left && this->right)
        {
            this->num_of_subtrees = this->right->num_of_subtrees + 1;
            return;
        }
        this->num_of_subtrees = 1;
    }


    template<class T>
    int RankTree<T>::getRank(const T& data) const
    {
        return this->getRankAux(data);
    }

    template<class T>
    int RankTree<T>::getRankAux(const T& data, int counter) const
    {
        if(data == *this->data)
        {
            if(!this->left)
            {
                return counter + 1;
            }
            return counter + this->left->num_of_subtrees + 1;
        }
        else if(data < *this->data)
        {
            if(this->left)
            {
                return this->left->getRankAux(data, counter);
            }
                // data doesn't exist.
            else
            {
                return 0;
            }
        }
        else if(data > *this->data)
        {
            if(this->right)
            {
                if(!this->left)
                {
                    return this->right->getRankAux(data, counter + 1);
                }
                return this->right->getRankAux(data, counter + this->left->num_of_subtrees + 1);
            }
                // data doesn't exist.
            else
            {
                return 0;
            }
        }
        return 0;
    }

    template<class T>
    RankTree<T>* RankTree<T>::Select(int index)
    {
        if(!this->left)
        {
            if(index == 1)
            {
                return this;
            }
            else if(index == 2)
            {
                if(this->right)
                {
                    return this->right;
                }
                else
                {
                    return nullptr;
                }
            }
            else
            {
                if(this->right)
                {
                    return this->right->Select(index - 1);
                }
                else
                {
                    throw FailureError();
                }
            }
        }
        if(this->left->num_of_subtrees == index - 1)
        {
            return this;
        }
        else if(this->left->num_of_subtrees > index - 1)
        {
            return this->left->Select(index);
        }
        else if(this->left->num_of_subtrees < index - 1)
        {
            if(this->right)
            {
                return this->right->Select(index - this->left->num_of_subtrees - 1);
            }
            else
            {
                return nullptr;
            }
        }
        return nullptr;
    }

    template<class T>
    T **RankTree<T>::getArrayFromTree()
    {
        if(this->data == nullptr)
        {
            return nullptr;
        }
        T** array = new T*[this->num_of_subtrees];
        int* counter = new int(0);
        this->getArrayFromTreeAux(array, counter);
        delete counter;
        return array;
    }

    template<class T>
    void RankTree<T>::getArrayFromTreeAux(T** array, int* counter)
    {
        if(this->left)
        {
            this->left->getArrayFromTreeAux(array, counter);
        }

        T* temp_data = new T(*data);
        array[*counter] = temp_data;
        (*counter)++;

        if(this->right)
        {
            this->right->getArrayFromTreeAux(array, counter);
        }
    }

    template<class T>
    int RankTree<T>::numOfSubtrees() const
    {
        return this->num_of_subtrees;
    }

    template<class T>
    void RankTree<T>::fullRankUpdate()
    {
        if(this->left)
        {
            this->left->fullRankUpdate();
        }
        if(this->right)
        {
            this->right->fullRankUpdate();
        }
        this->updateRank();
    }

}

#endif
