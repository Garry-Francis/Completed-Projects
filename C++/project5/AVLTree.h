/*-------------------------------------------------------------------------------------------
* Name: Garry Francis
* Project: AVLTree
*
* This is the header file for the AVLTree and AVLNode classes. It contains all the constructor
* and function declarations. This file includes declarations for: the AVLTree constructor, the
* AVLTree copy constructor, the AVLTree deconstructor, the insert function, the contains
* function, the get function, the findRange function, the keys function, the size function,
* the operator [], =, and << override functions, the getHeight(tree) function, the AVLNode
* constructor, the numChildren function, the isLeaf function, the getHeight(node) function,
* the remove function, the balanceNode function, the calcHeight function, the getBalance
* function, the rotateRight function, the rotateLeft function, the printTree function,
* and any recursive functions that are called by functions previously listed.
* -----------------------------------------------------------------------------------------*/

#ifndef AVLTREE_H
#define AVLTREE_H
#include <optional>
#include <string>
#include <vector>

using namespace std;

class AVLTree {
public:
    //AVLTree class variables
    //vector<string> range;
    size_t num;

    //AVLTree constructor
    AVLTree();

    //AVLTree functions
    bool insert(const string& key, size_t value);
    bool remove(const string& key);
    bool contains(const string& key) const;
    optional<size_t> get(const string& key) const;
    size_t& operator[](const string& key);
    vector<string> findRange(const string& lowKey, const string& highKey) const;
    vector<string> keys() const;
    size_t size() const;
    size_t getHeight() const;
    void operator=(const AVLTree& other);
    friend ostream& operator<<(ostream& os, const AVLTree & avlTree);
    //AVLTree copy constructor
    AVLTree(const AVLTree& other);
    //AVLTree deconstructor
    ~AVLTree();

protected:
    class AVLNode {
    public:
        //AVLNode class variables
        string key;
        size_t value;
        int height;
        AVLNode* left;
        AVLNode* right;

        //AVLNode constructor
        AVLNode(const string& key, size_t value);

        //AVLNode functions
        // 0, 1 or 2
        size_t numChildren() const;
        // true or false
        bool isLeaf() const;
        // number of hops to deepest leaf node
        size_t getHeight() const;
        int getBalance() const;

    };

    public:
        //Recursive functions that needed to be public to work
        AVLNode* recursiveBracket(AVLNode*& current, const string& key);
        void deconstructorRecursion(AVLNode*& current);
        //Not recursive functions just need to be after AVLNode
        int calcHeight(AVLNode*& current);
        void rotateRight(AVLNode*& problem);
        void rotateLeft(AVLNode*& problem);
        friend void printTree(ostream &os, const AVLNode* current, int depth);

    private:
        //Private root variable of AVLTree class
        AVLNode* root;

        //Recursive functions
        bool insert(AVLNode*& current, const string& key, const size_t& value);
        bool contains(AVLNode* current, const string &key) const;
        optional<size_t> get(AVLNode* current, const string& key) const;
        vector<string> findRange(AVLNode* current, const string& lowKey, const string& highKey, vector<string>& result) const;
        vector<string> keys(AVLNode* current, vector<string>& result) const;
        void copyConstructorRecursion(AVLNode*& current, const AVLNode* other);
        void copyEquals(AVLNode*& current, const AVLNode* other);


        /* Helper methods for remove */
        // this overloaded remove will do the recursion to remove the node
        bool remove(AVLNode*& current, const string& key);
        // removeNode contains the logic for actually removing a node based on the number of children
        bool removeNode(AVLNode*& current);
        // You will implement this, but it is needed for removeNode()
        void balanceNode(AVLNode*& node);
};

#endif //AVLTREE_H
