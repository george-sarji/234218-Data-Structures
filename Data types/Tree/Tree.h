#ifndef TREE_H_
#define TREE_H_

namespace structures
{
    template <class T>
    class Tree
    {
    private:
        T *data;
        Tree *left;
        Tree *right;
        int& height;

    public:
        Tree(T *data, Tree *left = nullptr, Tree *right = nullptr) : data(data), left(left), right(right) {}
        ~Tree() = default;

        // Operator overloads
        T& operator*();
        Tree* operator=(Tree* tree);

        // Utility methods
        Tree* Left();
        Tree* Right();
        int& Height();
        void LeftLeft();
        void LeftRight();
        void RightLeft();
        void RightRight();

        // ! Required functions
        // Left, Right, Height, operator* overload, LeftLeft, LeftRight, RightLeft, RightRight, assignment operator overload
    };
}

#endif