#ifndef VECTOR_H
#define VECTOR_H

namespace structures
{
    template <class T>
    class vector
    {
    private:
        T* data;
        int index, max_size;

    public:
        vector(int size) : max_size(size), index(0) ,data(new T[size]) {}
        vector(const vector& vec) : data(new T[vec->max_size]), index(vec->index), max_size(vec->max_size)
        {
            for(int i = 0; i < max_size; i++)
            {
                data[i] = vec->data[i];
            }
        }
        ~vector();
    };
}

#endif