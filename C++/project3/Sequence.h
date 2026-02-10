/*-------------------------------------------------------------------------------------------
* Name: Garry Francis
* Project: Sequence
*
* This is the header file for the Sequence class. It contains the declarations the constructor
* and all the functions. This file includes declarations for: the Sequence class, the Sequence
* constructor, the SequenceNode class, the SequenceNode constructor the sequence destructor,
* the = and [] operator overrides, the push_back function, * the pop_back function,
* the insert function, the front function, the back function, the empty function, the size
* function, the clear function, both erase functions, and the ostream integration/override.
* -----------------------------------------------------------------------------------------*/

#include <string>
#include <ostream>

using namespace std;

class SequenceNode {
    public: // to make it easier, we can make the data members public so we don't need
        // getters and setters

        std::string item; // the element being stored in the node

        SequenceNode* next; // pointer to next Node. If node is the tail, next is
        // nullptr

        SequenceNode* prev; // pointer to previous Node. If node is the head, prev is
        // nullptr

        //default constructor, ensure next and prev are nullptr
        SequenceNode() : next(nullptr), prev(nullptr)
        {}

        // parameterized constructor, next and prev are set to nullptr and the
        // node's element is set to the given value
        SequenceNode(std::string item) : next(nullptr), prev(nullptr), item(item)
        {}
};

class Sequence {
    // Declaration of Sequence class
	public:
    SequenceNode *head;
    SequenceNode *tail;
    size_t num;

	// constructor declaration
    Sequence(size_t sz = 0);

    // every function declaration
    Sequence(const Sequence& s);
    ~Sequence();
    Sequence& operator=(const Sequence& s);
    std::string& operator[](size_t position);
    void push_back(std::string item);
    void pop_back();
    void insert(size_t position, std::string item);
    std::string front() const;
    std::string back() const;
    bool empty() const;
    size_t size() const;
    void clear();
    void erase(size_t position);
    void erase(size_t position, size_t count);
    friend ostream& operator<<(ostream& os, const Sequence& s);
};