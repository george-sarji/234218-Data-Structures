#ifndef DYN_ARRAY_H
#define DYN_ARRRAY_H
#include <exception>

namespace structures
{
    template <class T>
    class DynamicArray
    {
    private:
        T **elements;
        int size;
        int count;
        void resizeArray();

    public:
        DynamicArray();
        ~DynamicArray();

        // * Getters/Setters
        int getSize() const;
        T **getElements() const;
        int getCount() const;

        // * Utility functions
        void addElement(T *);
        void removeElement(const int i);
    };

    template <class T>
    structures::DynamicArray<T>::DynamicArray()
    {
        this->size = 1;
        this->elements = new T *[this->size];
        this->count = 0;
    }

    template <class T>
    structures::DynamicArray<T>::~DynamicArray()
    {
        for (int i = 0; i < this->count; i++)
        {
            delete this->elements[i];
        }
        delete[] this->elements;
    }

    template <class T>
    void structures::DynamicArray<T>::resizeArray()
    {
        // We want to resize the array completely. Grab a new pointer with the new size.
        T **new_array = nullptr;
        try
        {
            new_array = new T *[size * 2];
            // Check if we had a successful memory allocation.
        }
        catch (const std::bad_alloc &)
        {
            throw std::bad_alloc();
        }
        // We had a successful memory allocation. We now need to move the items into the proper cells.
        for (int i = 0; i < this->size; i++)
        {
            new_array[i] = this->elements[i];
        }
        // Now we have to change the size of the array, and set the new array.
        this->size *= 2;
        T **temp = this->elements;
        this->elements = new_array;
        delete[] temp;
    }

    template <class T>
    void structures::DynamicArray<T>::addElement(T *item)
    {
        // Check if we have to resize the array.
        if (count == size)
        {
            // Resize the array.
            this->resizeArray();
        }
        // We need to add the element into count cell and increase count now.
        this->elements[count] = item;
        count++;
    }

    template <class T>
    void structures::DynamicArray<T>::removeElement(const int i)
    {
        // Check if in bounds
        if (i > count)
            return;
        // We need to remove the element at i and shift the rest of the array.
        delete this->elements[i];
        for (int j = i; j < count - 1; j++)
        {
            this->elements[j] = this->elements[j + 1];
        }
        this->count--;
    }

    template <class T>
    int structures::DynamicArray<T>::getCount() const
    {
        return this->count;
    }

    template <class T>
    int structures::DynamicArray<T>::getSize() const
    {
        return this->size;
    }

    template <class T>
    T **structures::DynamicArray<T>::getElements() const
    {
        return this->elements;
    }
}

#endif