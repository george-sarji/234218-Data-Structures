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
        int &height;

    public:
        Tree(T &data, Tree *left = nullptr, Tree *right = nullptr) : data(data), left(left), right(right) {}
        Tree(const Tree &tree);
        ~Tree();

        // Operator overloads
        T &operator*();
        Tree &operator=(const Tree &tree);
        bool operator>(const Tree &tree) const;
        bool operator>=(const Tree &tree) const;
        bool operator<(const Tree &tree) const;
        bool operator<=(const Tree &tree) const;
        bool operator==(const Tree &tree) const;

        // Utility methods
        Tree *Left() const;
        Tree *Right() const;
        int &Height();
        Tree *LeftLeft(Tree *root);
        Tree *LeftRight(Tree *root);
        Tree *RightLeft(Tree *root);
        Tree *RightRight(Tree *root);

        // ! Required functions
        // LeftRight, RightLeft
    };
}

#endif