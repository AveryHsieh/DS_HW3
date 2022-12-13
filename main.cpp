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

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <cmath>
#include <time.h>
#include <conio.h>
#include <unordered_map>

using namespace std;


// Searching on a B+ tree in C++

#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
//int MAX = 3;
#define MAX 3

// BP node
class Node {
    bool IS_LEAF;
    int* key, size;
    Node** ptr;
    friend class BPTree;

public:
    Node();
};

// BP tree
class BPTree {
    Node* root;
    void insertInternal(int, Node*, Node*);
    Node* findParent(Node*, Node*);

public:
    BPTree();
    void search(int);
    void insert(int);
    void display(Node*);
    Node* getRoot();
};

Node::Node() {
    key = new int[MAX];
    ptr = new Node * [MAX + 1];
}

BPTree::BPTree() {
    root = NULL;
}

// Search operation
void BPTree::search(int x) {
    if (root == NULL) {
        //cout << "Tree is empty\n";
    }
    else {
        Node* cursor = root;
        while (cursor->IS_LEAF == false) {
            for (int i = 0; i < cursor->size; i++) {
                if (x < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }
                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }
        for (int i = 0; i < cursor->size; i++) {
            if (cursor->key[i] == x) {
                //cout << "Found\n";
                return;
            }
        }
        //cout << "Not found\n";
    }
}

// Insert Operation
void BPTree::insert(int x) {
    if (root == NULL) {
        root = new Node;
        root->key[0] = x;
        root->IS_LEAF = true;
        root->size = 1;
    }
    else {
        Node* cursor = root;
        Node* parent = NULL;
        while (cursor->IS_LEAF == false) {
            parent = cursor;
            for (int i = 0; i < cursor->size; i++) {
                if (x < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }
                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }
        if (cursor->size < MAX) {
            int i = 0;
            while (x > cursor->key[i] && i < cursor->size)
                i++;
            for (int j = cursor->size; j > i; j--) {
                cursor->key[j] = cursor->key[j - 1];
            }
            cursor->key[i] = x;
            cursor->size++;
            cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
            cursor->ptr[cursor->size - 1] = NULL;
        }
        else {
            Node* newLeaf = new Node;
            int virtualNode[MAX + 1];
            for (int i = 0; i < MAX; i++) {
                virtualNode[i] = cursor->key[i];
            }
            int i = 0, j;
            while (x > virtualNode[i] && i < MAX)
                i++;
            for (int j = MAX + 1; j > i; j--) {
                virtualNode[j] = virtualNode[j - 1];
            }
            virtualNode[i] = x;
            newLeaf->IS_LEAF = true;
            cursor->size = (MAX + 1) / 2;
            newLeaf->size = MAX + 1 - (MAX + 1) / 2;
            cursor->ptr[cursor->size] = newLeaf;
            newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX];
            cursor->ptr[MAX] = NULL;
            for (i = 0; i < cursor->size; i++) {
                cursor->key[i] = virtualNode[i];
            }
            for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++) {
                newLeaf->key[i] = virtualNode[j];
            }
            if (cursor == root) {
                Node* newRoot = new Node;
                newRoot->key[0] = newLeaf->key[0];
                newRoot->ptr[0] = cursor;
                newRoot->ptr[1] = newLeaf;
                newRoot->IS_LEAF = false;
                newRoot->size = 1;
                root = newRoot;
            }
            else {
                insertInternal(newLeaf->key[0], parent, newLeaf);
            }
        }
    }
}

// Insert Operation
void BPTree::insertInternal(int x, Node* cursor, Node* child) {
    if (cursor->size < MAX) {
        int i = 0;
        while (x > cursor->key[i] && i < cursor->size)
            i++;
        for (int j = cursor->size; j > i; j--) {
            cursor->key[j] = cursor->key[j - 1];
        }
        for (int j = cursor->size + 1; j > i + 1; j--) {
            cursor->ptr[j] = cursor->ptr[j - 1];
        }
        cursor->key[i] = x;
        cursor->size++;
        cursor->ptr[i + 1] = child;
    }
    else {
        Node* newInternal = new Node;
        int virtualKey[MAX + 1];
        Node* virtualPtr[MAX + 2];
        for (int i = 0; i < MAX; i++) {
            virtualKey[i] = cursor->key[i];
        }
        for (int i = 0; i < MAX + 1; i++) {
            virtualPtr[i] = cursor->ptr[i];
        }
        int i = 0, j;
        while (x > virtualKey[i] && i < MAX)
            i++;
        for (int j = MAX + 1; j > i; j--) {
            virtualKey[j] = virtualKey[j - 1];
        }
        virtualKey[i] = x;
        for (int j = MAX + 2; j > i + 1; j--) {
            virtualPtr[j] = virtualPtr[j - 1];
        }
        virtualPtr[i + 1] = child;
        newInternal->IS_LEAF = false;
        cursor->size = (MAX + 1) / 2;
        newInternal->size = MAX - (MAX + 1) / 2;
        for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++) {
            newInternal->key[i] = virtualKey[j];
        }
        for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++) {
            newInternal->ptr[i] = virtualPtr[j];
        }
        if (cursor == root) {
            Node* newRoot = new Node;
            newRoot->key[0] = cursor->key[cursor->size];
            newRoot->ptr[0] = cursor;
            newRoot->ptr[1] = newInternal;
            newRoot->IS_LEAF = false;
            newRoot->size = 1;
            root = newRoot;
        }
        else {
            insertInternal(cursor->key[cursor->size], findParent(root, cursor), newInternal);
        }
    }
}

// Find the parent
Node* BPTree::findParent(Node* cursor, Node* child) {
    Node* parent;
    if (cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF) {
        return NULL;
    }
    for (int i = 0; i < cursor->size + 1; i++) {
        if (cursor->ptr[i] == child) {
            parent = cursor;
            return parent;
        }
        else {
            parent = findParent(cursor->ptr[i], child);
            if (parent != NULL)
                return parent;
        }
    }
    return NULL;
}

// Print the tree
void BPTree::display(Node* cursor) {
    if (cursor != NULL) {
        for (int i = 0; i < cursor->size; i++) {
            cout << cursor->key[i] << " ";
        }
        cout << "\n";
        if (cursor->IS_LEAF != true) {
            for (int i = 0; i < cursor->size + 1; i++) {
                display(cursor->ptr[i]);
            }
        }
    }
}

// Get the root
Node* BPTree::getRoot() {
    return root;
}

int example() {
    BPTree node;
    node.insert(5);
    node.insert(15);
    node.insert(25);
    node.insert(35);
    node.insert(45);
    node.insert(55);
    node.insert(40);
    node.insert(30);
    node.insert(20);
    node.display(node.getRoot());

    node.search(15);
    return 0;
}



//B+ Tree Test
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
            BPTree node;//initial B+ Tree

            double START, END;
            START = clock();

            for (int i = 0; i < pow(2, k); i++)
            {
                node.insert(rand() % 1073741824 + 1);//update B+ Tree
            }

            END = clock();

            addTotalSpendTime += ((END - START) / CLOCKS_PER_SEC);


            double search_START, search_END;
            search_START = clock();
            int sum = 0;
            for (int i = 0; i < pow(10, 5); i++)
            {
                node.search(rand() % 1073741824 + 1);//search in B+ Tree
            }
            search_END = clock();
            searchTotalSpendTime += ((search_END - search_START) / CLOCKS_PER_SEC);
        }
        double addAvrgSpendTime = addTotalSpendTime / repeat;
        double searchAvrgSpendTime = searchTotalSpendTime / repeat;
        cout << endl << "B+ Tree新增2^" << k << "個隨機數所需的時間:" << addAvrgSpendTime << " sec" << endl;
        cout << endl << "在存了2^" << k << "筆資料的B+ Tree中搜尋十萬筆資料所需的時間:" << searchAvrgSpendTime << " sec" << endl << endl;
    }
    return 0;
}