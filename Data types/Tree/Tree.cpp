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
    structures::Tree<T>::~Tree()
    {
        delete left;
        delete right;
        delete data;
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
        Tree *new_root = root->Left();
        root->left = new_root->Right();
        new_root->right = root;

        root->Height() = MAX((root->Right())->Height(), (root->Left())->Height()) + 1;
        (new_root->left)->Height() = (new_root->Left())->Height() + 1;
        new_root->Height() = MAX((new_root->left)->Height(), (new_root->Right())->Height()) + 1;

        return new_root;
    }

    template <class T>
    Tree<T> *structures::Tree<T>::RightRight(Tree *root)
    {
        Tree *new_root = root->Right();
        root->right = new_root->Left();
        new_root->left = root;
        return new_root;
    }

    template <class T>
    Tree<T> *structures::Tree<T>::LeftRight(Tree *root)
    {
        Tree *new_root = root->left->Right();
        Tree *tmp_left = new_root->Left();
        Tree *tmp_right = new_root->Right();

        new_root->left = root->Left();
        new_root->right = root;
        (new_root->Left())->right = tmp_left;
        (new_root->Right())->left = tmp_right;

        return new_root;
    }

    template <class T>
    Tree<T> *structures::Tree<T>::RightLeft(Tree *root)
    {
        Tree *new_root = root->right->Left();
        Tree *tmp_left = new_root->Left();
        Tree *tmp_right = new_root->Right();

        new_root->left = root;
        new_root->right = root->Right();
        (new_root->Left())->right = tmp_left;
        (new_root->Right())->left = tmp_right;

        return new_root;
    }
}

int main() { return 0; }