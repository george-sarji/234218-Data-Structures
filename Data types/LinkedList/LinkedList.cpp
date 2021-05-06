#include "LinkedList.h"

namespace structures
{
    template <class T>
    structures::LinkedList<T>::~LinkedList()
    {
        delete this->data;
        delete this->next;
    }

    template <class T>
    T *structures::LinkedList<T>::getData()
    {
        return this->data;
    }

    template <class T>
    structures::LinkedList<T> *structures::LinkedList<T>::getNext()
    {
        return this->next;
    }

    template <class T>
    T &structures::LinkedList<T>::operator*()
    {
        return this->data;
    }

    template <class T>
    void structures::LinkedList<T>::setData(T *data)
    {
        this->data = data;
    }

    template <class T>
    void structures::LinkedList<T>::setNext(LinkedList<T> *next)
    {
        this->next = next;
    }
}

int main()
{
    return 0;
}