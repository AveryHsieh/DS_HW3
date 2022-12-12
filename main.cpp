#pragma warning( disable : 4996 )
// C++ program to demonstrate search, insert and delete in Treap

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <unordered_set>

//#include <bits/stdc++.h>
using namespace std;

// A Treap Node
struct TreapNode
{
    int key, priority;
    TreapNode* left, * right;
};

/* T1, T2 and T3 are subtrees of the tree rooted with y
  (on left side) or x (on right side)
                y                               x
               / \     Right Rotation          /  \
              x   T3   – – – – – – – >        T1   y
             / \       < - - - - - - -            / \
            T1  T2     Left Rotation            T2  T3 */

            // A utility function to right rotate subtree rooted with y
            // See the diagram given above.
TreapNode* rightRotate(TreapNode* y)
{
    TreapNode* x = y->left, * T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
TreapNode* leftRotate(TreapNode* x)
{
    TreapNode* y = x->right, * T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Return new root
    return y;
}

/* Utility function to add a new key */
TreapNode* newNode(int key)
{
    TreapNode* temp = new TreapNode;
    temp->key = key;
    temp->priority = rand() % 100;
    temp->left = temp->right = NULL;
    return temp;
}

// C function to search a given key in a given BST
TreapNode* search(TreapNode* root, int key)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->key == key)
        return root;

    // Key is greater than root's key
    if (root->key < key)
        return search(root->right, key);

    // Key is smaller than root's key
    return search(root->left, key);
}

/* Recursive implementation of insertion in Treap */
TreapNode* insert(TreapNode* root, int key)
{
    // If root is NULL, create a new node and return it
    if (!root)
        return newNode(key);

    // If key is smaller than root
    if (key <= root->key)
    {
        // Insert in left subtree
        root->left = insert(root->left, key);

        // Fix Heap property if it is violated
        if (root->left->priority > root->priority)
            root = rightRotate(root);
    }
    else  // If key is greater
    {
        // Insert in right subtree
        root->right = insert(root->right, key);

        // Fix Heap property if it is violated
        if (root->right->priority > root->priority)
            root = leftRotate(root);
    }
    return root;
}

/* Recursive implementation of Delete() */
TreapNode* deleteNode(TreapNode* root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    // IF KEY IS AT ROOT

    // If left is NULL
    else if (root->left == NULL)
    {
        TreapNode* temp = root->right;
        delete(root);
        root = temp;  // Make right child as root
    }

    // If Right is NULL
    else if (root->right == NULL)
    {
        TreapNode* temp = root->left;
        delete(root);
        root = temp;  // Make left child as root
    }

    // If key is at root and both left and right are not NULL
    else if (root->left->priority < root->right->priority)
    {
        root = leftRotate(root);
        root->left = deleteNode(root->left, key);
    }
    else
    {
        root = rightRotate(root);
        root->right = deleteNode(root->right, key);
    }

    return root;
}

// A utility function to print tree
void inorder(TreapNode* root)
{
    if (root)
    {
        inorder(root->left);
        cout << "key: " << root->key << " | priority: %d "
            << root->priority;
        if (root->left)
            cout << " | left child: " << root->left->key;
        if (root->right)
            cout << " | right child: " << root->right->key;
        cout << endl;
        inorder(root->right);
    }
}


// Driver Program to test above functions
int example()
{
    srand(time(NULL));

    struct TreapNode* root = NULL;
    root = insert(root, 50);



    TreapNode* res = search(root, 50);
    (res == NULL) ? cout << "\n50 Not Found " :
        cout << "\n50 found";

    return 0;
}


//Treap Test
int main() {
    srand(time(NULL));

    int start, end, repeat;
    cin >> start >> end >> repeat;

    cout << "重複 " << repeat << " 次取平均" << "\n";
    for (int k = start; k < (end + 1); k++)
    {
        double addTotalSpendTime = 0;
        double searchTotalSpendTime = 0;
        for (int n = 0; n < repeat; n++)
        {
            struct TreapNode* root = NULL;//initial Treap

            double START, END;
            START = clock();

            for (int i = 0; i < pow(2, k); i++)
            {
                root = insert(root, rand() % 1073741824 + 1);//update Treap
            }

            END = clock();

            addTotalSpendTime += ((END - START) / CLOCKS_PER_SEC);


            double search_START, search_END;
            search_START = clock();
            int sum = 0;
            for (int i = 0; i < pow(10, 5); i++)
            {
                search(root, rand() % 1073741824 + 1);//search in Treap
            }
            search_END = clock();
            searchTotalSpendTime += ((search_END - search_START) / CLOCKS_PER_SEC);
        }
        double addAvrgSpendTime = addTotalSpendTime / repeat;
        double searchAvrgSpendTime = searchTotalSpendTime / repeat;
        cout << endl << "Treap新增2^" << k << "個隨機數所需的時間:" << addAvrgSpendTime << " sec" << endl;
        cout << endl << "在存了2^" << k << "筆資料的Treap中搜尋十萬筆資料所需的時間:" << searchAvrgSpendTime << " sec" << endl << endl;
    }
    return 0;
}