#ifndef TREE_H_
#define TREE_H_

#include <stdio.h>
#include <iostream>
#define MAX(left, right) (left > right ? left : right)

namespace structures
{
    template <class T>
    class Tree
    {
    private:
        T data;
        Tree *left;
        Tree *right;
        Tree *parent;
        int height;

    public:
        Tree() = default;
        Tree(const Tree &tree) : data(tree->data), left(tree->left), right(tree->right), parent(tree->parent)
        {
        }
        Tree(T data, Tree *parent = nullptr, Tree *left = nullptr, Tree *right = nullptr) : data(data), left(left), right(right), parent(parent), height(1) {}
        ~Tree() = default;

        void clearTree()
        {
            if (!this)
                return;
            if (this->left)
                this->left->clearTree();
            if (this->right)
                this->right->clearTree();
            delete this;
        }

        Tree<T> *Left() const
        {
            return this->left;
        }

        Tree<T> *Right() const
        {
            return this->right;
        }

        T *Data()
        {
            return &this->data;
        }

        int Height()
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

        int getBalanceFactor() const
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

        T &operator*()
        {
            return this->data;
        }

        Tree<T> &operator=(const Tree<T> &tree)
        {
            this->data = tree->data;
            this->left = tree->left;
            this->right = tree->right;
            this->height = tree->height;
            this->parent = tree->parent;
            return this;
        }

        bool operator<(const Tree &tree) const
        {
            return this->data < tree->data;
        }

        bool operator<=(const Tree &tree) const
        {
            return this->data <= tree->data;
        }

        bool operator>(const Tree &tree) const
        {
            return this->data > tree->data;
        }

        bool operator>=(const Tree &tree) const
        {
            return this->data >= tree->data;
        }

        bool operator==(const Tree &tree) const
        {
            return this->data == tree->data;
        }

        Tree<T> *LeftLeft(Tree *root)
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

        Tree<T> *RightRight(Tree *root)
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

        Tree<T> *LeftRight(Tree *root)
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

        Tree<T> *RightLeft(Tree *root)
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

        Tree<T> *addIntersection(T new_data)
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
                (this->right)->parent = this;
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
                (this->left)->parent = this;
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

        Tree<T> *removeIntersection(T data)
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
                    son->parent = this->parent;
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

        void printInOrder() const
        {
            if (!this)
            {
                return;
            }
            this->left->printInOrder();
            std::cout << this->data << " ";
            this->right->printInOrder();
        }

        void printPreOrder() const
        {
            if (!this)
                return;
            std::cout << this->data << " ";
            this->left->printPreOrder();
            this->right->printPreOrder();
        }

        Tree<T> *inorderSuccessor()
        {
            Tree<T> *current = this->right;

            while (current->left != nullptr)
            {
                current = current->left;
            }
            return current;
        }

        Tree<T> *findData(T data) const
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

        void printParent() const
        {
            if ((this->parent) == nullptr)
            {
                std::cout << "no parent" << std::endl;
                return;
            }

            std::cout << "parent is:" << *((this->parent)->Data()) << std::endl;
            return;
        }
    };
}

#endif