/*-------------------------------------------------------------------------------------------
* Name: Garry Francis
* Project: Sequence
*
* This is the cpp file for the Sequence class. It contains the constructor and all
* the function definitions. This file includes: the Sequence constructor, the sequence
* destructor, the = and [] operator overrides, the push_back function, the pop_back function,
* the insert function, the front function, the back function, the empty function, the size
* function, the clear function, both erase functions, and the ostream integration/override.
* -----------------------------------------------------------------------------------------*/

#include "Sequence.h"
#include <cstdlib>
#include <iostream>
#include <exception>

using namespace std;

// Creates an empty sequence (num == 0) or a sequence of num items
// indexed from 0 ... (num - 1).
Sequence::Sequence(size_t sz) {
    // Creates an empty sequence (sz = 0)
    head = nullptr;
    tail = nullptr;
    num = 0;

    // For if you didn't make an empty sequence
    // For a sequence of 1 item
    if (sz != 0) {
        // Make a new node
        SequenceNode *newNode = new SequenceNode("0");
        // Make that node head and tail of the sequence
        head = newNode;
        tail = newNode;
        // Increase num by one
        num++;

        // For a sequence of more than one item
        if (sz > 1) {
            while (num < sz) {
                // Make a new node
                newNode = new SequenceNode(to_string(num));
                // Make the tail have newNode as next
                tail->next = newNode;
                // Make newNode have the tail as previous
                newNode->prev = tail;
                // Make newNode the tail
                tail = newNode;
                num++;
            }
        }
    }
}

// Creates a (deep) copy of sequence s
Sequence::Sequence(const Sequence& s) {
    // Makes the sequence empty
    head = nullptr;
    tail = nullptr;
    num = 0;

    // Makes a pointer for copying values
    SequenceNode* copier = s.head;

    // Copies every value from the original sequence
    while (copier) {
        push_back(copier->item);
        copier = copier->next;
    }
}

// Destroys all items in the sequence and release the memory
// associated with the sequence
Sequence::~Sequence() {
    // Calls the clear function
    clear();
}

// The current sequence is released and replaced by a (deep) copy of sequence
// s. A reference to the copied sequence is returned (return *this;).
Sequence& Sequence::operator=(const Sequence& s) {
    // Clears the sequence that called the function
    clear();
    // Makes a pointer for copying values
    SequenceNode* copier = s.head;

    // Copies every value from the original sequence
    while (copier) {
        push_back(copier->item);
        copier = copier->next;
    }
    // Returns the new sequence
    return *this;
}

// The position satisfies ( position >= 0 && position <= last_index() ).
// The return value is a reference to the item at index position in the
// sequence. Throws an exception if the position is outside the bounds
// of the sequence
std::string& Sequence::operator[](size_t position) {
    // For when you try to go outside the sequence
    if (position > num) {
        throw exception();
    }
    // Makes a pointer for finding the desired value
    SequenceNode *finder = head;

    // Moves through the sequence until the value is reached
    for (int i = 0; i < position; i++) {
        finder = finder->next;
    }
    // Returns the reached value
    return finder->item;
}

// The value of item is appended to the sequence.
void Sequence::push_back(std::string item) {
    // Has to do a special construction for if the sequence is empty
    if (num == 0) {
        // Makes a new node
        SequenceNode *newNode = new SequenceNode(item);
        // Makes newNode head and tail
        head = newNode;
        tail = newNode;
        // Increase num by one
        num++;
        return;
    }
    // Makes a new node
    SequenceNode *newNode = new SequenceNode(item);
    // Make the tail have newNode as next
    tail->next = newNode;
    // Make newNode have the tail as previous
    newNode->prev = tail;
    // Make newNode the tail
    tail = newNode;
    // Increase num by one
    num++;
}

// The item at the end of the sequence is deleted and size of the sequence is
// reduced by one. If sequence was empty, throws an exception
void Sequence::pop_back() {
    // For when you try to delete from an empty sequence
    if (num == 0) {
        throw exception();
    }
    // Make a pointer at the tail
    SequenceNode* current = tail;
    // Make a pointer at the node before the tail
    SequenceNode* toBeTail = current->prev;
    // Delete the tail
    delete current;
    // Change the previous node to tail
    tail = toBeTail;
    tail->next = nullptr;
    // Decrease num by one
    num--;
}

// The position satisfies ( position >= 0 && position <= last_index() ). The
// value of item is inserted at position and the size of sequence is increased
// by one. Throws an exception if the position is outside the bounds of the
// sequence
void Sequence::insert(size_t position, std::string item) {
    // For when you try to insert out of bounds
    if (position > num) {
        throw exception();
    }
    SequenceNode* inserter = new SequenceNode(item);
    // For when we are inserting at the head
    if (position == 0) {
        // Empty sequence, it is both head and tail
        if (num == 0) {
            // Make the node both head and tail
            head = inserter;
            tail = inserter;
        }
        // Not empty, but it is at the head
        else {
            // Make the inserters next the head
            inserter->next = head;
            // Make the heads previous the inserter
            head->prev = inserter;
            // Make the inserter the head
            head = inserter;
        }
    }
    // For when we are inserting at the tail
    else if (position == num) {
        // Make the tails next the inserter
        tail->next = inserter;
        // Make the inserters previous the tail
        inserter->prev = tail;
        // Make the inserter the tail
        tail = inserter;
    }
    // For when we are inserting at literally anywhere else
    else {
        // Make a pointer for tracking position
        SequenceNode* current = head;
        // Move through the sequence until position is reached
        for (int i = 0; i < position; i++) {
            current = current->next;
        }
        // There's a lot of pointers being moved here but the inserter gets
        // Put between the two values around the current pointer.
        inserter->prev = current->prev;
        inserter->next = current;
        current->prev->next = inserter;
        current->prev = inserter;
    }
    // Increase num by 1
    num++;
}

// Returns the first element in the sequence. If the sequence is empty, throw an
// exception.
std::string Sequence::front() const {
    // For when you try to get a value from an empty sequence
    if (num == 0) {
        throw exception();
    }
    // Returns the head
    return head->item;
}

// Return the last element in the sequence. If the sequence is empty, throw an
// exception.
std::string Sequence::back() const {
    // For when you try to get a value from an empty sequence
    if (num == 0) {
        throw exception();
    }
    // Returns the tail
    return tail->item;
}

// Return true if the sequence has no elements, otherwise false.
bool Sequence::empty() const {
    // Checks if the sequence is empty
    if (num == 0) {
        // Returns true if it is
        return true;
    }
    // Returns false if it isn't
    return false;
}

// Return the number of elements in the sequence.
size_t Sequence::size() const {
    // Returns the size
    return this->num;
}

// All items in the sequence are deleted and the memory associated with the
// sequence is released, resetting the sequence to an empty state that can have
// items re-inserted.
void Sequence::clear() {
    // Makes a pointer at the head
    SequenceNode* current = head;
    // Deletes every item in the sequence
    while (current != nullptr) {
        SequenceNode* toBeDeleted = current->next;
        delete current;
        current = toBeDeleted;
    }
    // Sets head and tail to null and num to 0
    head = nullptr;
    tail = nullptr;
    num = 0;
}

// The item at position is removed from the sequence, and the memory
// is released. If called with an invalid position throws an exception.
void Sequence::erase(size_t position) {
    // For when you try to delete out of bounds
    if (position >= num) {
        throw exception();
    }
    // Make a pointer for the position
    SequenceNode* current;
    // For when we are deleting the head
    if (position == 0) {
        current = head;
        // For when the head is the only item in the list
        if (num == 1) {
            // Set head and tail to null
            head = nullptr;
            tail = nullptr;
        }
        // Not empty after deletion, move head forward
        else {
            // set head to the next item and set previous to null
            head = current->next;
            head->prev = nullptr;
        }
    }
    // For when we are deleting the tail
    else if (position == num - 1) {
        current = tail;
        // set tail to the previous item and set next to null
        tail = current->prev;
        tail->next = nullptr;
    }
    // For when we are deleting literally anywhere else
    else {
        current = head;
        // Move to the position in the list
        for (size_t i = 0; i < position; i++) {
            current = current->next;
        }
        // More pointers moving around but the items before and after current
        // are set to point at each other instead of current
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }
    // Delete the item and decrease num by 1
    delete current;
    num--;
}

// The items in the sequence at ( position ... (position + count - 1) ) are
// deleted and their memory released. If called with invalid position and/or
// count throws an exception.
void Sequence::erase(size_t position, size_t count) {
    // For when you try to delete out of bounds
    if (position >= num || position + count > num) {
        throw exception();
    }
    // Reuse the singular erase function to remove each item
    for (size_t i = 0; i < count; i++) {
        erase(position);
    }
}

// Outputs all elements (ex: <4, 8, 15, 16, 23, 42>) as a string to the output
// stream. This is *not* a method of the Sequence class, but instead it is a
// friend function
ostream& operator<<(ostream& os, const Sequence& s) {
    SequenceNode *printer = s.head;
    // Prints out each item in the sequence
    for (int i = 0; i < s.num; i++) {
        cout << printer->item << " ";
        printer = printer->next;
    }
    return os;
}