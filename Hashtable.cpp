#include <iostream>
#include <vector>
#include <list>

class HashTable {
private:
    static const int TABLE_SIZE = 10;
    std::vector<std::list<int>> table;

    // Simple hash function
    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

public:
    HashTable() : table(TABLE_SIZE) {}

    void insert(int data) {
        int index = hashFunction(data);
        table[index].push_back(data);
    }

    bool search(int data) {
        int index = hashFunction(data);
        for (int value : table[index]) {
            if (value == data) {
                return true;
            }
        }
        return false;
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            std::cout << "Bucket " << i << ": ";
            for (int value : table[i]) {
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    HashTable hashTable;
    hashTable.insert(5);
    hashTable.insert(15);
    hashTable.insert(25);
    hashTable.insert(35);
    hashTable.insert(6);
    hashTable.insert(15); // Adding a duplicate to test collision handling ( Allowing duplicates on purpuse ... )

    hashTable.display();

    int searchData = 15;
    if (hashTable.search(searchData)) {
        std::cout << searchData << " found in the hash table." << std::endl;
    } else {
        std::cout << searchData << " not found in the hash table." << std::endl;
    }

    searchData = 50;
    if (hashTable.search(searchData)) {
        std::cout << searchData << " found in the hash table." << std::endl;
    } else {
        std::cout << searchData << " not found in the hash table." << std::endl;
    }

    return 0;
}
