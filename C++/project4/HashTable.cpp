/*-------------------------------------------------------------------------------------------
* Name: Garry Francis
* Project: HashTable
*
* This is the cpp file for the HashTable and HashTableBucket class. It contains the constructors
* and all the function definitions. This file includes: The HashTable constructor, the insert
* function, the resizeTable the remove function, the contains function, the get function,
* the [] operator override, the keys function, the alpha function, the capacity function, the size
* function, the printMe function, the << operator override, the probe function, the offsetShuffle
* function, the HashTableBucket constructors, the load function, the isEmpty function.
* -----------------------------------------------------------------------------------------*/

#include "HashTable.h"
#include <exception>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

using namespace std;

/**
* Only a single constructor that takes an initial capacity for the table is
* necessary. If no capacity is given, it defaults to 8 initially
*/

// Constructor for the HashTable
HashTable::HashTable(size_t cap) {
    // Sets capacity
    table.resize(cap);
    // Tracks size
    filled = 0;
    // Tracks capacity
    max = cap;
    // Makes offsets vector
    offsets = offsetShuffle(cap);
}

/**
* Insert a new key-value pair into the table. Duplicate keys are NOT allowed. The
* method should return true if the insertion was successful. If the insertion was
* unsuccessful, such as when a duplicate is attempted to be inserted, the method
* should return false
*/

bool HashTable::insert(const std::string& key, const size_t& value) {
    // If key is in the table, it doesn't get added
    if (contains(key)) {
        return false;
    }
    // If the table is half full it gets expanded
    if (alpha() >= 0.5) {
        resizeTable();
    }
    // Hash the key
    size_t home = hasher(key) % max;
    // If the home index is open
    if (table[home].isEmpty()) {
        // Load in the key pair
        table[home].load(key, value);
        // Increase size counter
        filled++;
        return true;
    }
    // You can't insert at the home index
    for (int i = 0; i < max - 1; i++) {
        // Begin the probe
        auto hole = probe(home, i);
        // If the probed index is open
        if (table[hole].isEmpty()) {
            // Load in the key pair
            table[hole].load(key, value);
            // Increase size counter
            filled++;
            return true;
        }
    }
    // I'm not sure that it's possible to reach this return but if it's not here I get a warning
    // and I don't like warnings
    return false;
}

void HashTable::resizeTable() {
    // Increase capacity counter
    max *= 2;
    // Increase capacity
    vector <HashTableBucket> oldTable = table;
    // Shuffle the offset values
    offsets = offsetShuffle(max);
    // Clear the table
    table.clear();
    // Set the table capacity
    table.resize(max);
    // Set filled to 0
    filled = 0;
    // Re-hash every value from the old table into the expanded one
    for (int i = 0; i < oldTable.size(); i++) { // NOLINT(*-loop-convert)
        if (!oldTable[i].isEmpty()) {
            this->insert(oldTable[i].bucketKey, oldTable[i].bucketValue);
        }
    }
}

/**
* If the key is in the table, remove will “erase” the key-value pair from the
* table. This might just be marking a bucket as empty-after-remove
*/

bool HashTable::remove(const std::string& key) {
    // If the key is in the table it gets removed
    if (contains(key)) {
        // Hash the key
        size_t home = hasher(key) % max;
        // If the key is at the home index
        if (table[home].bucketKey == key) {
            // Set the key to a blank string and the value to 0
            table[home].load("", 0);
            // Set the bucket type to Empty After Removal
            table[home].type = bucketType::EAR;
            // Decrease size counter
            filled--;
            return true;
        }
        // If EES, stop trying
        if (table[home].type == bucketType::ESS) {
            return false;
        }
        // If the key is not at the home index
        for (int i = 0; i < max - 1; i++) {
            // Begin the probe
            auto hole = probe(home, i);
            // If the key is at the probed index
            if (table[hole].bucketKey == key) {
                // Set the key to a blank string and the value to 0
                table[hole].load("", 0);
                // Set the bucket type to Empty After Removal
                table[hole].type = bucketType::EAR;
                // Decrease size counter
                filled--;
                return true;
            }
            // If ESS, stop trying
            if (table[hole].type == bucketType::ESS) {
                return false;
            }
        }
    }
    // The key was not in the table
    return false;
}

/**
* contains returns true if the key is in the table and false if the key is not in
* the table.
*/

bool HashTable::contains(const string& key) const {
    // Hash the key
    size_t home = hasher(key) % max;
    // If the key is at the home index
    if (table[home].bucketKey == key) {
        return true;
    }
    // If ESS, stop trying
    if (table[home].type == bucketType::ESS) {
        return false;
    }
    // If the key is not at the home index
    for (int i = 0; i < max - 1; i++) {
        // Begin the probe
        auto hole = probe(home, i);
        // If the key is at the probed index
        if (table[hole].bucketKey == key) {
            return true;
        }
        // If ESS, stop trying
        if (table[hole].type == bucketType::ESS) {
            return false;
        }
    }
    // The key was not in the table
    return false;
}

/**
* If the key is found in the table, find will return the value associated with
* that key. If the key is not in the table, find will return something called
* nullopt, which is a special value in C++. The find method returns an
* optional<size_t>, which is a way to denote a method might not have a valid value
* to return. This approach is nicer than designating a special value, like -1, to
* signify the return value is invalid. It's also much better than throwing an
* exception if the key is not found.
*/

std::optional<size_t> HashTable::get(const string& key) const {
    // If the key is in the table the value is retrieved
    if (contains(key)) {
        // Hash the key
        size_t home = hasher(key) % max;
        // If the key is at the home index
        if (table[home].bucketKey == key) {
            // Return the key value
            return table[home].bucketValue;
        }
        // If ESS, stop trying
        if (table[home].type == bucketType::ESS) {
            return nullopt;
        }
        // If the key is not at the home index
        for (int i = 0; i < max - 1; i++) {
            // Begin the probe
            auto hole = probe(home, i);
            // If the key is at the probed index
            if (table[hole].bucketKey == key) {
                // Return the key value
                return table[hole].bucketValue;
            }
            // If ESS, stop trying
            if (table[hole].type == bucketType::ESS) {
                return nullopt;
            }
        }
    }
    // The key was not in the table, return nullopt
    return nullopt;
}

/**
* The bracket operator lets us access values in the map using a familiar syntax,
* similar to C++ std::map or Python dictionaries. It behaves like get, returning
* the value associated with a given key:
* int idNum = hashTable[“James”];
* Unlike get, however, the bracket operator returns a reference to the value,
* which allows assignment:
* hashTable[“James”] = 1234;
* If the key is not in the table, returning a valid reference is impossible. You may choose to
* throw an exception in this case, but for our implementation, the situation
* results in undefined behavior. Simply put, you do not need to address attempts
* to access keys not in the table inside the bracket operator method.
*/

size_t& HashTable::operator[](const string& key) {
    // If the table contains the key, reference the value
    if (contains(key)) {
        // Hash the key
        size_t home = hasher(key) % max;
        // If the key is at the home index
        if (table[home].bucketKey == key) {
            // Return the key value
            return table[home].bucketValue;
        }
        // If ESS, stop trying
        if (table[home].type == bucketType::ESS) {
            throw exception();
        }
        // If the key is not at the home index
        for (int i = 0; i < max - 1; i++) {
            // Begin the probe
            auto hole = probe(home, i);
            // If the key is at the probed index
            if (table[hole].bucketKey == key) {
                // Return the key value
                return table[hole].bucketValue;
            }
            // If ESS, stop trying
            if (table[home].type == bucketType::ESS) {
                throw exception();
            }
        }
    }
    // The key is not in the table, throw exception
    throw exception();
}

/**
* keys returns a std::vector (C++ version of ArrayList, or simply list/array)
* with all the keys currently in the table. The length of the vector should be
* the same as the size of the hash table.
*/

std::vector<std::string> HashTable::keys() const {
    // Make a vector for the keys
    vector<string> keys;
    // Give the vector space for the keys
    keys.reserve(max);
    // Check each bucket for a key
    for (int i = 0; i < max; i++) {
        // If the bucket is not empty
        if (!table[i].isEmpty()) {
            // Add key to the vector
            keys.push_back(table[i].bucketKey);
        }
    }
    // Return the vector of keys
    return keys;
}

/**
* alpha returns the current load factor of the table, or size/capacity. Since
* alpha returns a double,make sure to properly cast the size and capacity, which
* are size_t, to avoid size_t division. You can cast a size_t num to a double
* in C++ like:
* static_cast<double>(num)
* The time complexity for this method must be O(1).
*/

double HashTable::alpha() const {
    // Divide size by capacity
    return static_cast<double>(filled) / static_cast<double>(max);
}

/**
* capacity returns how many buckets in total are in the hash table. The time
* complexity for this algorithm must be O(1).
*/

size_t HashTable::capacity() const {
    // Return capacity
    return max;
}

/**
* The size method returns how many key-value pairs are in the hash table. The
* time complexity for this method must be O(1)
*/

size_t HashTable::size() const {
    // Return size
    return filled;
}

/**
* operator<< is another example of operator overloading in C++, similar to
* operator[]. The friend keyword only needs to appear in the class declaration,
* but not the definition. In addition, operator<< is not a method of HashTable,
* so do not put HashTable:: before it when defining it. operator<< will allow us
* to print the contents of our hash table using the normal syntax:
* cout << myHashTable << endl;
* You should only print the buckets which are occupied,
* and along with each item you will print which bucket (the index of the bucket)
* the item is in. To make it easy, I suggest creating a helper method called
* something like printMe() that returns a string of everything in the table. An
* example which uses open addressing for collision resolution could print
* something like:
* Bucket 5: <James, 4815>
* Bucket 2: <Juliet, 1623>
* Bucket 11: <Hugo, 42108>
*/

std::string HashTable::printMe(int i) const {
    // If the bucket is not empty
    if (!table[i].isEmpty()) {
        // Incredibly long line that puts a whole bucket into a string
        string s = "Bucket " + to_string(i) + ": <" + table[i].bucketKey + ", " + to_string(table[i].bucketValue) + ">";
        // Return the string
        return s;
    }
    // The bucket was empty, return an empty string
    return "";
}

ostream& operator<<(ostream& os, const HashTable& hashTable) {
    // For the capacity of the table
    for (int i = 0; i < hashTable.capacity(); i++) {
        // If the printMe string isn't empty
        if (!hashTable.printMe(i).empty()) {
            // Print the printMe string
            os << hashTable.printMe(i) << endl;
        }
    }
    // Returns the ostream... I guess.
    return os;
}

size_t HashTable::probe(size_t home, int i) const {
    return (home + offsets[i]) % table.size();
}

vector <size_t> HashTable::offsetShuffle(size_t newCap) {
    // Make a new offsets vector
    vector <size_t> newOffsets;
    // Set the vector size to cap - 1
    newOffsets.resize(newCap - 1);
    // Add numbers to the vector up to the cap starting from 1
    for (int i = 0; i < newCap - 1; i++) {
        newOffsets[i] = i + 1;
    }
    // I'm not sure what these next three lines actually do, but it ends with the vector being shuffled
    random_device rd;
    mt19937 g(rd());
    // ReSharper disable once CppUseRangeAlgorithm
    shuffle(newOffsets.begin(), newOffsets.end(), g);
    // Return shuffled offsets
    return newOffsets;
}

//BUCKET

/**
* The default constructor can simply set the bucket type to ESS.
*/

HashTableBucket::HashTableBucket() {
    // Sets value to zero
    bucketValue = 0;
    // Sets type to Empty Since Start
    type = bucketType::ESS;
}

/**
* A parameterized constructor could initialize the key and value, as
* well as set the bucket type to NORMAL.
*/

HashTableBucket::HashTableBucket(const std::string& key, const size_t& value) {
    // Sets the key
    bucketKey = key;
    // Sets the value
    bucketValue = value;
    // Sets the type to normal
    type = bucketType::NORMAL;
}

/**
* A load method could load the key-value pair into the bucket, which
* should then also mark the bucket as NORMAL.
*/

void HashTableBucket::load(const std::string& key, const size_t& value) {
    // Sets the key
    bucketKey = key;
    // Sets the value
    bucketValue = value;
    // Sets the type to normal
    type = bucketType::NORMAL;
}

/**
* This method would return whether the bucket is empty, regardless of
* if it has had data placed in it or not.
*/

bool HashTableBucket::isEmpty() const {
    // If the type is not normal then its either ESS or EAR, both of which are empty
    if (type != bucketType::NORMAL) {
        // It's empty
        return true;
    }
    // Its normal, so not empty
    return false;
}