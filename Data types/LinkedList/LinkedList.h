#ifndef LINKED_LIST_H
#define LINKED_LIST_H

namespace structures
{
    template <class T>
    class LinkedList
    {
    private:
        T *data;
        LinkedList *next;

    public:
        LinkedList(T *data, LinkedList *next = nullptr) : data(data), next(next) {}
        ~LinkedList();

        T *getData();
        LinkedList *getNext();
        T& operator*();
        void setData(T *data);
        void setNext(LinkedList *next);
    };
}

#endif