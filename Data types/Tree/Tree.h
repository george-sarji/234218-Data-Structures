#ifndef TREE_H_
#define TREE_H_

namespace structures
{
    template <class T>
    class Tree
    {
    private:
        T data;
        Tree *left;
        Tree *right;
        int& height;

    public:
        Tree(T& data, Tree *left = nullptr, Tree *right = nullptr) : data(data), left(left), right(right) {}
        ~Tree() = default;

        // Operator overloads
        T& operator*();
        Tree& operator=(const Tree& tree);
        bool operator>(const Tree& tree) const;
        bool operator>=(const Tree& tree) const;
        bool operator<(const Tree& tree) const;
        bool operator<=(const Tree& tree) const;
        bool operator==(const Tree& tree) const;

        // Utility methods
        Tree* Left() const;
        Tree* Right() const;
        int& Height();
        Tree* LeftLeft(Tree* father);
        Tree* LeftRight(Tree* father);
        Tree* RightLeft(Tree* father);
        Tree* RightRight(Tree* father);

        // ! Required functions
        // Left, Right, Height, operator* overload, LeftLeft, LeftRight, RightLeft, RightRight, assignment operator overload
    };
}

#endif