#include "Tree.h"
#define MAX(left, right) (left > right ? left : right)

namespace structures
{
    template <class T>
    structures::Tree<T>::Tree(const Tree &tree)
    {
        data = tree->data;
        left = tree->left;
        right = tree->right;
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
    int &structures::Tree<T>::Height()
    {
        return this->height;
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

        root->height = MAX((root->right)->height, (root->left)->height) + 1;
        new_root->height = MAX((new_root->left)->height, (new_root->right)->height) + 1;

        return new_root;
    }

    template <class T>
    Tree<T> *structures::Tree<T>::RightRight(Tree *root)
    {
        Tree *new_root = root->right;
        root->right = new_root->left;
        new_root->left = root;

        root->height = MAX((root->left)->height, (root->right)->height) + 1;
        new_root->height = MAX((new_root->left)->height, (new_root->right)->height) + 1;

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

        (new_root->left)->height = MAX(((new_root->left)->left)->height, ((new_root->left)->right)->height) + 1;
        (new_root->right)->height = MAX(((new_root->right)->left)->height, ((new_root->right)->right)->height) + 1;
        new_root->height = MAX((new_root->left)->height, (new_root->right)->height) + 1;

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

        (new_root->left)->height = MAX(((new_root->left)->left)->height, ((new_root->left)->right)->height) + 1;
        (new_root->right)->height = MAX(((new_root->right)->left)->height, ((new_root->right)->right)->height) + 1;
        new_root->height = MAX((new_root->left)->height, (new_root->right)->height) + 1;

        return new_root;
    }

    template <class T>
    Tree<T> &structures::Tree<T>::addIntersection(T &new_data)
    {
        // Reached end of recursion, create new leaf.
        if (this == NULL)
        {
            return new Tree(new_data);
        }
        // Check if the data goes to the right subtree
        if (new_data > this->data)
        {
            this->right = this->right->addIntersection(new_data);
        }
        // Check if the data goes to the left subtree
        else if (new_data < this->data)
        {
            this->left = this->left->addIntersection(new_data);
        }
        // AVL does not allow equal keys
        else
        {
            return this;
        }

        this->height = MAX(this->left->height, this->right->height) + 1;

        int balance_factor = this->left->height - this->right->height;

        // Check the balance for each specific rotation
        if (balance_factor > 1 && new_data < this->left->data)
        {
            // Left Left.
            return this->RightRight(this);
        }
        else if (balance_factor < -1 && new_data > this->right->data)
        {
            return this->LeftLeft(this);
        }
        else if (balance_factor > 1 && new_data > this->left->data)
        {
            return this->LeftRight(this);
        }
        else if (balance < -1 && new_data < this->right->data)
        {
            return this->RightLeft(this);
        }

        return this;
    }

    template <class T>
    Tree<T>& structures::Tree<T>::removeIntersection(T& data)
    {
        if(!this)
        {
            return this;
        }

        if(data < this->data)
        {
            this->left = this->left->removeIntersection(data);
        }
        else if(data < this->data)
        {
            this->right = this->right->removeIntersection(data);
        }
        else
        {
            //intersection is a leaf
            if(this->left == NULL && this->right == NULL)
            {
                delete this;
                return NULL;
            }
            //intersection has two children
            else if(this->left != NULL && this->right != NULL)
            {
                Tree<T>* next = this->inorderSuccessor();
                this->data = next->data;
                this->right = this->right->removeIntersection(next->data);
            }
        }
        
    }

    template <class T>
    Tree<T>& structures::Tree<T>::inorderSuccessor()
    {   
        Tree<T> current = this->right;

        while(current->left != NULL)
        {
            current = current->left;
        }
        return current;
    }

}

int main() { return 0; }