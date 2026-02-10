/*-------------------------------------------------------------------------------------------
* Name: Garry Francis
* Project: HashTable
*
* This is the header file for the HashTable and HashTableBucket class. It contains the constructors
* and all the function declarations. This file includes: The HashTable constructor, the insert
* function, the resizeTable the remove function, the contains function, the get function,
* the [] operator override, the keys function, the alpha function, the capacity function, the size
* function, the printMe function, the << operator override, the probe function, the offsetShuffle
* function, the HashTableBucket constructors, the load function, the isEmpty function.
* -----------------------------------------------------------------------------------------*/
#pragma once

#include <optional>
#include <string>
#include <ostream>
#include <vector>

using namespace std;

// enum types for buckets
enum class bucketType {NORMAL, ESS, EAR};

class HashTableBucket {
    public:
        // HashTableBucket variables
        bucketType type;
        std::string bucketKey;
        size_t bucketValue;
        // HashTableBucket default constructor declaration
        HashTableBucket();
        // HashTableBucket parameter constructor declaration
        HashTableBucket(const std::string& key, const size_t& value);
        // HashTableBucket function declarations
        void load(const std::string& key, const size_t& value);
        bool isEmpty() const;
};

class HashTable {
    public:
        // HashTable variables
        vector <size_t> offsets;
        vector <HashTableBucket> table;
        size_t filled;
        size_t max;
        // HashTable constructor declaration
        explicit HashTable(size_t cap = 8);
        // HashTable function Declarations
        bool insert(const std::string& key, const size_t& value);
        bool remove(const std::string& key);
        bool contains(const string& key) const;
        optional<size_t> get(const string& key) const;
        size_t& operator[](const string& key);
        vector<std::string> keys() const;
        double alpha() const;
        size_t capacity() const;
        size_t size() const;
        friend ostream& operator<<(ostream& os, const HashTable& ht);
        size_t probe(size_t home, int i) const;
        std::string printMe(int i) const;
        static vector <size_t> offsetShuffle(size_t newCap) ;
        void resizeTable();
        // Hasher declaration
        std::hash<std::string> hasher;
};