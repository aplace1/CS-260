// File: LinkedList.cpp
//


#include <iostream>
#include <algorithm>

// Forward declarations

double stringToDouble(std::string, char);

// define a structure to hold record information
struct Record {
    std::string ID {"NULL"}, field1{ID}, field2{ID};
    double field3 {0.00};
    Record() {
        field3 = 0.00;
    }
    friend std::ostream &operator<<(std::ostream &os, const Record &record) {
        os << "ID: " << record.ID << " field1: " << record.field1 << " field2: " << record.field2 << " field3: " << record.field3 <<std::endl;
        return os;
    }
};

/**
 * @brief Define a class containing data members and
 *   methods to implement a linked-list.
 *
 */
class LinkedList {
private:
    // create a struct for Node
    struct Node {
        Record record;
        Node *next{nullptr};

        // Default Node constructor
        Node() = default;

        // Overloaded constructor taking a record
        explicit Node(Record record) {
            this->record = std::move(record);
        }
    };

    Node *head;
    Node *tail;
    int size = 0;

public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Record);
    void Prepend(Record);
    void PrintList();
    void Remove(const std::string &);
    Record Search(const std::string &);
    int Size();
};

/**
 * @brief Default constructor
 */
LinkedList::LinkedList() {
    // set head and tail to null pointers
    head = tail = nullptr;
}

/**
 * @brief Destructor
 */
LinkedList::~LinkedList() = default;

/**
 * @brief Append a new record to the end of the list
 */
void LinkedList::Append(Record record) {

    Node *node = new Node(std::move(record));

    // if null pointer, set head equal to node
    if(head == nullptr)
        head = node;
    else {

        // if tail is not equal to a null pointer,
        // set the tail to next node
        if(tail != nullptr)
            tail->next = node;
    }

    tail = node; // set tail to last node
    size++;      // increment size by one
}

/**
 * @brief Prepend a new record to the start of the list
 */
void LinkedList::Prepend(Record record) {

    Node *node = new Node(std::move(record));

    if(head != nullptr)
        node->next = head;

    head = node;
    size++;
}

/**
 * @brief Output of all records in the list
 */
void LinkedList::PrintList() {
    Node *current = head;

    while(current != nullptr) {
        std::cout << current;
        current = current->next;
    }
}

/**
 * @brief Remove a specified record
 *
 * @param ID The record id to remove from the list
 */
void LinkedList::Remove(const std::string &ID) {

    // if head is not a null pointer
    if(head != nullptr) {

        // if std::string.compare is match
        if(head->record.ID == ID) {

            delete head; // delete head

            // set head and tail to null pointers
            head = nullptr;
            tail = nullptr;
        }
    }

    Node *current = head;

    // while current node is not a null pointer
    if(current != nullptr)
        while(current->next) {

        // if current node's ID matches parameter ID
        if(current->next->record.ID == ID) {

            Node *tempNode = current->next;
            current->next = tempNode->next;

            delete tempNode; // delete the temporary node
            size--;          // decrement the size by one
            return;          // exit loop
        }

        current = current->next;
    }
}

/**
 * @brief Search for the specified ID
 *
 * @param ID The record id to search for
 */
Record LinkedList::Search(const std::string &ID) {

    Node *current = head;

    while(current != nullptr) {
        if(current->record.ID == ID)
            return (current->record);

        current = current->next;
    }

    return Record();
}

/**
 * @brief  Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
    return (size);
}

/**
 * @brief Display the record information
 *
 * @param record struct containing the record info
 */
void displayRecord(const Record &record) {
    std::cout << record.ID << ": " << record.field1 << " | " << record.field3 << " | "
              << record.field2 << std::endl;
}

/**
 * @brief  Retrieves a record id
 * @return Record struct containing the record info
 */
Record getRecord() {
    Record record;
    record.field1 = "default";
    record.field2 = "default";
    record.field3 = 0.00;
    return (record);
}

/**
 * @brief Load a CSV file containing records into a LinkedList
 *
 * @return a LinkedList containing all the records read
 */
void loadRecords(const std::string &csvPath, LinkedList *list) {
    std::cout << "Loading CSV file " << csvPath << std::endl;

    // initialize the CSV Parser
    // csv::Parser file = csv::Parser(csvPath);
    // try {
    //     // loop to read rows of a CSV file
    //     for(unsigned int i = 0; i < file.rowCount(); i++) {

    //         // initialize a record using data from current row (i)
    //         Record record;
    //         record.ID = file[i][1];
    //         record.field1 = file[i][0];
    //         record.field2 = file[i][19];
    //         record.field3 = strToDouble(file[i][4], '$');
    //         // add this record to the end
    //         list->Append(record);
    //     }
    // }
    // catch(csv::Error &e) {
    //     std::cerr << e.what() << std::endl;
    // }
}

/**
 * @brief Parse a string and return a double by removing invalid characters
 *
 * @param tmpString string to modify
 * @param toRemove character to remove from string
 * @return Parsed string as double
 */
double stringToDouble(std::string tmpString, char toRemove) {
    tmpString.erase(remove(tmpString.begin(), tmpString.end(), toRemove), tmpString.end());
    return atof(tmpString.c_str());
}

/**
 * @brief Entry Point
 */
int main(/*int argc, char *argv[]*/) {
    return (0);
}