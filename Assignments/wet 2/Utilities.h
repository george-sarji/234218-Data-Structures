#include "Tree.h"
#include "RankTree.h"

namespace structures
{

    template <class T>
    T **mergeArrays(T **left, T **right, int left_size, int right_size)
    {
        // Create a new array.
        T **new_array = new T *[left_size + right_size];
        // Start merging according to order.
        int i = 0, j = 0, k = 0;
        while (i < left_size && j < right_size)
        {
            T* current_left = left[i], *current_right = right[j];
            if (*current_left < *current_right)
            {
                new_array[k] = current_left;
                i++;
            }
            else
            {
                new_array[k] = current_right;
                j++;
            }
            k++;
        }
        // Check if we have leftover elements.
        while (i < left_size)
        {
            // Add the leftovers.
            new_array[k] = left[i];
            i++;
            k++;
        }
        while (j < right_size)
        {
            new_array[k] = right[j];
            j++;
            k++;
        }

        return new_array;
    }

    template <class T>
    Tree<T> *createAVLFromArray(T **arr, int begin, int end)
    {
        if (begin > end)
            return nullptr;

        int middle = (begin + end) / 2;
        // Start a new tree.
        Tree<T> *root = new Tree<T>(arr[middle]);

        // Create the left child.
        root->setLeft(createAVLFromArray(arr, begin, middle - 1));
        // Create the right child.
        root->setRight(createAVLFromArray(arr, middle + 1, end));

        return root;
    }

    template <class T>
    RankTree<T> *createRankTreeFromArray(T **arr, int begin, int end)
    {
        if (begin > end)
            return NULL;

        int middle = (begin + end) / 2;
        // Start a new tree.
        RankTree<T> *root = new RankTree<T>(arr[middle]);

        // Create the left child.
        root->setLeft(createRankTreeFromArray(arr, begin, middle - 1));
        // Create the right child.
        root->setRight(createRankTreeFromArray(arr, middle + 1, end));

        return root;
    }
}