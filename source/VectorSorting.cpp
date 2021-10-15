// File: VectorSorting.cpp
//


#include <iostream>
#include <algorithm>
#include <vector>

// forward declarations

double stringToDouble(std::string, char);

// define a structure to hold record information
struct Record {
    std::string id {"NULL"}, field2{id}, field3{id};
    double field4;
    Record() {
        field4 = 0.00;
    }

    friend std::ostream &operator<<(std::ostream &os, const Record &record) {
        os << "id: " << record.id << " field2: " << record.field2 << " field3: " << record.field3 << " field4: " << record.field4 << std::endl;
        return os;
    }
};

/**
 * @brief Display the record information
 *
 * @param record struct containing the record info
 */
void displayRecord(const Record &record) {
    std::cout << (record);
}

/**
 * @brief Prompt user for record information
 *
 * @return Record struct containing the record info
 */
Record getRecord() {
    Record record;
    return (record);
}

/**
 * @brief Load a CSV file containing records into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the records read
 */
std::vector<Record> loadRecords(const std::string &csvPath) {
    // std::cout << "Loading CSV file " << csvPath << std::endl;

    // Define a std::vector data structure to hold a collection of records.
    std::vector<Record> records;

    /*
    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file

        for(unsigned index = 0; index < file.rowCount(); index++) {

            // Create a data structure and add to the collection of records
            Record record;
            record.id = file[index][1];
            record.field2 = file[index][0];
            record.field3 = file[index][8];
            record.field4 = strToDouble(file[index][4],'$');

            // push this record to the end
            records.push_back(record);
        }
    }
    catch(csv::Error &e) {
        std::cerr << e.what() << std::endl;
    } */

    return (records);
}

/**
 * @brief Partition the std::vector of records into two parts, low and high
 *
 * @param records Address of the std::vector<Record> instance to be partitioned
 * @param begin Beginning index to partition
 * @param end Ending index to partition
 */
int partition(std::vector<Record> &records, int begin, int end) {
    int low = begin;
    int high = end;

    int pivot = (begin + (end - begin) / 2);

    bool done = false;

    // while not done
    while(!done) {

        // increment low while less than pivot
        while(records.at(low).field3.compare(records.at(pivot).field3) < 0) {
            ++low;
        }

        // decrement high while less than pivot
        while(records.at(pivot).field3.compare(records.at(high).field3) < 0) {
            --high;
        }

        if(high <= low) {
            done = true;
        }
        else {
            // swap the lower and higher records
            std::swap(records.at(low), records.at(high));
            ++low;
            --high;
        }
    } // end outer while loop;

    return (high);
} // end partition function

/**
 * @brief Perform a quick sort on record field2
 *
 * @param records address of the std::vector<Record> instance to be sorted
 * @param begin the beginning index to sort on
 * @param end the ending index to sort on
 */
void quickSort(std::vector<Record> &records, int begin, int end) {
    int mid;

    // if end is less than or equal to mid then
    // return;
    if(begin >= end) {
        return;
    }

    // partition records lowest/highest
    mid = partition(records, begin, end);

    // recursive call quicksort using mid
    quickSort(records, begin, mid);

    // recursively call quickSort incrementing mid by one for each call.
    quickSort(records, mid + 1, end);
}

/**
 * @brief Perform a selection sort on record field2
 *
 * @param record address of the std::vector<Record> instance to be sorted
 */
void selectionSort(std::vector<Record> &records) {
    static unsigned int min;
    static unsigned index = 0;
    static unsigned j = index;
    for(index = 0; index < records.size(); ++index) {
        min = index;
        for(j = index; j < records.size(); ++j) {
            if(records.at(j).field3.compare(records.at(min).field3) < 0) {
                min = j;
            }
        }

        if(min != index) {
            std::swap(records.at(index), records.at(min));
        }

    } // end of outer loop
} // end of selectionSort function

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
 */
int main(/*int argc, char *argv[]*/) {

    return (0);
}