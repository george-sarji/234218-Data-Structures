#include "Tree.h"

namespace structures
{

    template<class T>
    Tree<T>* structures::Tree<T>::Left() {
        return this->left;
    }

    template<class T>
    Tree<T>* structures::Tree<T>::Right() {
        return this->right;
    }

    template<class T>
    int& structures::Tree<T>::Height() {
        return this->height;
    }
}