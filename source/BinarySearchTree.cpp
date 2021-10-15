// File: BinarySearchTree.cpp
//

#include <iostream>
#include <algorithm>

/* forward declaration */


double stringToDouble(std::string, char);



/**
 * @brief Structure to hold record information
 */
struct Record {
    std::string id{"NULL"}, field1{id}, field2{id}, field3{id};
    double field4 {0.00};

    Record() = default;

    /**
     * @brief Overloaded constructor for Record
     *
     * @param id      the id as string
     * @param field2  the second field as string
     * @param field3  the third field as string
     * @param field4  the fourth field as string
     */
    Record(const std::string &id, const std::string &field2, const std::string &field3, const double &field4) {
        this->id = id;
        this->field2 = field2;
        this->field3 = field3;
        this->field4 = field4;
    }


    /**
     * @brief Record ToString() implementation
     * @param os
     * @param record
     * @return formatted output stream of the Record
     */
    friend std::ostream &operator<<(std::ostream &os, const Record &record) {
        os << "id: " << record.id << " field1: " << record.field1 << " field2: " << record.field2 << " field3: " << record.field3 << " field4: " << record.field4;
        return os;
    }
};

struct Node {
    Record record;
    Node *left{nullptr}, *right{nullptr};

    // Overloaded constructor
    explicit Node(Record record) {
        this->record = std::move(record);
    }
};


/**
 * @brief Implementation of a binary tree structure.
 */
class BinaryTree {

private:
    Node *root;
    void addNode(Node *node, const Record &record);
    void inOrder(Node *node);
    Node *removeNode(Node *node, const std::string &id);

public:
    BinaryTree();
    virtual ~BinaryTree();
    void InOrder();
    void Insert(const Record &record);
    void Remove(const std::string &id);
    Record Search(const std::string &id);
};

/**
 * @brief  Default constructor
 */
BinaryTree::BinaryTree() {
    // housekeeping
    root = nullptr;
}

/**
 * @brief Destructor
 */
BinaryTree::~BinaryTree() {
    // recurse from root deleting every node
    root = nullptr;
    delete root;
}

/**
 * @brief Traverse the tree in order
 */
void BinaryTree::InOrder() {
    this->inOrder(root);
}
/**
 * @brief Insert a record
 */
void BinaryTree::Insert(const Record &record) {
    if (root != nullptr) {
        this->addNode(root, record);
    } else  root = new Node(record);
}

/**
 * @brief Remove a record
 *
 * @param id as the record id
 */
void BinaryTree::Remove(const std::string &id) {
    this->removeNode(root, id);
}

Node *BinaryTree::removeNode(Node *node, const std::string &id) {
    // check if node is a null pointer
    if (node == nullptr) { return node; }

    // boolean representations of left and right child
    bool leftChild = (node->left == nullptr);
    bool rightChild = (node->right == nullptr);

    // compare left node first
    if (id.compare(node->record.id) < 0) {
        node->left = removeNode(node->left, id);
    } else if (id.compare(node->record.id) > 0) {
        node->right = removeNode(node->right, id);
    } else {

        // check if node has children, if none exist, remove it.
        if (leftChild && rightChild) {
            delete node;
            node = nullptr;
        }

        // only left child exists
        else if (!leftChild && rightChild) {
            Node *temp = node;
            node = node->left;
            delete temp;
        }
        // only right child exists
        else if (leftChild && !rightChild) {
            Node *temp = node;
            node = node->right;
            delete temp;
        }
        // left and right child exist
        else {
            Node *temp = node->right;

            do {
                temp = temp->left;
            } while (temp->left != nullptr);

            node->record = temp->record;
            node->right = removeNode(node->right, temp->record.id);
        }
    }

    return node;
}

/**
 * @brief Search for a record
 * @param id record id
 * @return Record
 */
Record BinaryTree::Search(const std::string &id) {

    // set index to the root node
    Node *current = root;

    // while current node is not a null pointer
    while(current != nullptr) {
        // if match is found, return the current record
        if(current->record.id == id)
            return current->record;

        // traverse left if current record is less than right
        current = id.compare(current->record.id) < 0 ? current->left : current->right;
    }

    // No record was found, return empty record
    Record record;
    return record;
}

/**
 * @brief  Add a record to some node (recursive)
 *
 * @param node Current node in tree
 * @param record Record to be added
 */
void BinaryTree::addNode(Node *node, const Record &record) {

    // check if new node is larger than previous node
    if(node->record.id.compare(record.id) > 0) {
        // if left node is null, create new node
        if(node->left == nullptr)
            node->left = new Node(record);
        else
            this->addNode(node->left, record);
    }

    // Add a record to the right sub-tree
    else if(node->right == nullptr)
        node->right = new Node(record);
    else
        this->addNode(node->right, record);
}

/**
 * @brief  Print records in order
 */
void BinaryTree::inOrder(Node *node) {
    if(node != nullptr) {
        inOrder(node->left);
        std::cout << node->record;
        inOrder(node->right);
    }
}


/**
 * @brief  Display the record information to the console (std::out)
 *
 * @param record struct containing the record info
 */
void displayBid(const Record &record) {
    std::cout << record;
}

/**
 * @brief Load a CSV file containing records into a container
 *
 * @param csvPath the path to the CSV file to load
 * @param bst the binary tree structure
 */
void loadBids(const std::string &csvPath, BinaryTree *bst) {
    // initialize the CSV Parser using the given path
    // csv::Parser file = csv::Parser(csvPath);

    // try {
    //     // loop to read rows of a CSV file
    //     for(unsigned i = 0; i < file.rowCount(); i++) {
    //         bst->Insert(Record(file[i][1], file[i][0], file[i][19], stringToDouble(file[i][4], '$')));
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
    return 0;
}