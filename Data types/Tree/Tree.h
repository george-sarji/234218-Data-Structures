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
        int height;

    public:
        Tree() = default;
        Tree(T data, Tree *left = nullptr, Tree *right = nullptr) : data(data), left(left), right(right), height(1) {}
        Tree(const Tree &tree);
        ~Tree() = default;
        void clearTree();

        // Operator overloads
        T &operator*();
        Tree &operator=(const Tree &tree);
        bool operator>(const Tree &tree) const;
        bool operator>=(const Tree &tree) const;
        bool operator<(const Tree &tree) const;
        bool operator<=(const Tree &tree) const;
        bool operator==(const Tree &tree) const;
        Tree* findData(T data) const;

        // Utility methods
        T* Data() const;
        Tree *Left() const;
        Tree *Right() const;
        int Height();
        int getBalanceFactor() const;
        Tree *LeftLeft(Tree *root);
        Tree *LeftRight(Tree *root);
        Tree *RightLeft(Tree *root);
        Tree *RightRight(Tree *root);
        void printInOrder() const;
        void printPreOrder() const;

        // Addition/removal functions
        Tree *addIntersection(T data);
        Tree *removeIntersection(T data);
        Tree *inorderSuccessor();

        // ! Required functions
        // LeftRight, RightLeft
    };
}

#endif