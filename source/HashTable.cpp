// File: HashTable.cpp
//


#include <iostream>
#include <algorithm>
#include <vector>


// forward declarations

double stringToDouble(std::string, char);

// define a structure to hold record information
struct Record {
    std::string id {"NULL"}, field2{id}, field3{id};
    double field4{0.00};
};


/**
 * @brief Define a class containing data members and methods
 *        to implement a hash table with chaining.
 */
class HashTable {

private:
    struct Node {

        Record record;
        unsigned key;
        Node *next;

        // default constructor
        Node() {
            key = UINT_MAX;
            next = nullptr;
        }

        // overloaded constructor, takes a record;
        explicit Node(Record record) : Node() {
            this->record = std::move(record);
        }

        // overloaded constructor, takes record and key
        Node(Record record, unsigned key) : Node(std::move(record)) {
            this->key = key;
        }
    };

    std::vector<Node> nodes;
    unsigned tableSize = 39500;
    unsigned hash(int) const;

public:
    HashTable();
    virtual ~HashTable();
    void Insert(const Record &);
    void PrintAll();
    void Remove(const std::string &);
    Record Search(const std::string &);
};

/**
 * @brief Default constructor
 */
HashTable::HashTable() {
    nodes.resize(tableSize);
}

/**
 * @brief HashTable Destructor
 */
HashTable::~HashTable() {
    nodes.erase(nodes.begin());
}

/**
 * @brief Calculate the hash value of a given key.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
unsigned int HashTable::hash(int key) const {
    return (key % tableSize);
}

/**
 * @brief Insert a record
 *
 * @param record The record to insert
 */
void HashTable::Insert(const Record &record) {

    unsigned key = hash(atoi(record.id.c_str()));

    // retrieve node address of key
    Node *oldNode = &(nodes.at(key));

    // if oldNode is not null
    if(oldNode == nullptr) {
        Node *newNode = new Node(record, key);
        nodes.insert(nodes.begin() + key, (*newNode));
    }
    else {
        // node found
        if(oldNode->key == UINT_MAX) { // UINT_MAX or 0xffffffff
            oldNode->key = key;
            oldNode->record = record;
            oldNode->next = nullptr;
        }
        else {
            // search for the next open slot
            while(oldNode->next != nullptr)
                oldNode = oldNode->next;

            oldNode->next = new Node(record, key);
        }
    }
}


/**
 * @brief Print all records
 *
 * @warning ALL rows are included in the output!
 */
void HashTable::PrintAll() {
    for(const Node &i : nodes) {
        // if field2 is not empty
        if(!i.record.field2.empty()) {
            std::cout
                    << "Key " << i.key << ": " << i.record.id << " | "
                    << i.record.field2 << " | " << i.record.field4 << " | "
                    << i.record.field3 << std::endl;
        }
    }
}

/**
 * @brief Remove a record
 *
 * @param id The record id to search for
 */
void HashTable::Remove(const std::string &id) {

    unsigned key = hash(atoi(id.c_str()));
    nodes.erase(nodes.begin() + key);
}

/**
 * @brief Search for the specified id
 *
 * @param id The record id to search for
 */
Record HashTable::Search(const std::string &id) {
    Record record;
    unsigned key = hash(atoi(id.c_str()));

    Node *node = &(nodes.at(key));

    // if null pointer or key is UINT_MAX
    if(node == nullptr || node->key == UINT_MAX)
        return (record);

    // if key is not UINT_MAX and both record ids match
    if(node->key != UINT_MAX && node->record.id == id)
        return (node->record);

    // do while loop, continue until break
    do {
        // break on nullptr, no match was found
        if(node == nullptr)
            break;

        // if key does not equal uint_max and both record ids match
        if(node->key != UINT_MAX && node->record.id == id)
            return (node->record);

        // iterate to the next node
        node = node->next;
    }
    while(true);

    // no matching record was found
    return (record);
}

/**
 * @brief Display the record information to the console (std::out)
 *
 * @param record struct containing the record info
 */
void displayRecord(const Record &record) {
    std::cout << record.id << ": " << record.field2 << " | " << record.field4 << " | "
              << record.field3 << std::endl;
}

/**
 * @brief Load a CSV file containing records into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the records read
 */
void loadRecords(const std::string &csvPath, HashTable *hashTable) {
    std::cout << "Loading CSV file " << csvPath << std::endl;

    // initialize the CSV Parser using the given path
    //csv::Parser file = csv::Parser(csvPath);

    // try {
    //     // loop to read rows of a CSV file
    //     for(unsigned int i = 0; i < file.rowCount(); i++) {
    //         // Create a data structure and add to the collection of records
    //         Record record;
    //         record.id = file[i][1];
    //         record.field2 = (file[i][0]);
    //         record.field3 = file[i][19];
    //         record.field4 = strToDouble(file[i][4], '$');
    //         // push this record to the end
    //         hashTable->Insert(record);
    //     }
    // }
    // catch(csv::Error &e) {
    //     std::cerr << e.what() << std::std::endl;
    // }
}

/**
 * @brief Parse a string and return a double by removing invalid characters
 *
 * @param toRemove The character to strip out
 */
double stringToDouble(std::string tmpString, char toRemove) {
    tmpString.erase(remove(tmpString.begin(), tmpString.end(), toRemove), tmpString.end());
    return atof(tmpString.c_str());
}

/**
 * @brief Entry Point
 *
 */
int main(/*int argc, char *argv[]*/) {
    return 0;
}