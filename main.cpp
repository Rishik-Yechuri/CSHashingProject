#include <iostream>
#include <vector>

using namespace std;

int main() {
    bool keepGoing = true;
    int tableSize = 0;
    std::string initialHashVal;
    int hashMultiplier;
    int relPrimeVal;
    std::cout << "Enter table size:";
    std::cin >> tableSize;
    //std::cout << std::endl;
    std::cout << "Enter initial hash value:";
    std::cin >> initialHashVal;
    //std::cout << std::endl;
    std::cout << "Enter hash multiplier:";
    std::cin >> hashMultiplier;
    //std::cout << std::endl;
    std::cout << "Enter relative prime value:";
    std::cin >> relPrimeVal;
    //std::cout << std::endl;
    std::string choice = "";
    do {
        do {
            std::cout << "1. Search String\n"
                         "2. Add String\n"
                         "3. Remove String\n"
                         "4. Display Table\n"
                         "5. Resize Table\n"
                         "Q. Quit\n"
                         "Choice: ";
            std::cin >> choice;
        } while (!(choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "Q"));
        std::string stringToUse = "";
        if (choice == "1") {
            std::cout << "String to search for:";
            std::cin >> stringToUse;
        } else if (choice == "2") {
            std::cout << "String to add:";
            std::cin >> stringToUse;
        } else if (choice == "3") {
            std::cout << "String to remove:";
            std::cin >> stringToUse;
        } else if (choice == "4") {
            //Display things
        } else if (choice == "5") {
            //Resize things
        } else {
            keepGoing = false;
        }

    } while (keepGoing);
}

class StringHash {
    string *holdVals;
    int permSize;
    int permInitialValue;
    int permHashMultiplier;
    int permRelativePrime;

    StringHash(int size, int initialValue, int hashMultiplier, int relativePrime) {
        //delete[] holdVals;
        holdVals = new string[size];
        permSize = size;
        permInitialValue = initialValue;
        permHashMultiplier = hashMultiplier;
        permRelativePrime = relativePrime;
    }
    vector<vector<int>>* theCoolerContains(string data){
        vector<int> holdVisited;
        bool found = false;
        bool endReached = false;
        int sizeOfList = holdVals->size();
        int x = 0;
        while (!found && !endReached) {
            int firstHash = HashMultiplicative(data);
            int secondHash = permRelativePrime - (firstHash % permRelativePrime);
            int doubleHash = (firstHash + (x * secondHash)) % permSize;
            if(holdVals[doubleHash] == data){
                found = true;
            }
            if(x+1 >= sizeOfList){
                endReached = true;
            }
            holdVisited.push_back(doubleHash);
            x++;
        }
        vector<vector<int>> *dataToReturn = new vector<vector<int>>();
        dataToReturn->push_back(holdVisited);
        vector<int> isTrueOrNot;
        if(found){
            isTrueOrNot.push_back(1);
        }else{
            isTrueOrNot.push_back(0);
        }
        dataToReturn->push_back(isTrueOrNot);
        return dataToReturn;
    }
    bool contains(string data) {
        vector<int> holdVisited;
        bool found = false;
        bool endReached = false;
        int sizeOfList = holdVals->size();
        int x = 0;
        while (!found && !endReached) {
            int firstHash = HashMultiplicative(data);
            int secondHash = permRelativePrime - (firstHash % permRelativePrime);
            int doubleHash = (firstHash + (x * secondHash)) % permSize;
            if(holdVals[doubleHash] == data){
                found = true;
            }
            if(x+1 >= sizeOfList){
                endReached = true;
            }
            holdVisited.push_back(doubleHash);
            x++;
        }
        return found;
    }

    bool add(string data) {
        vector<vector<int>> *receivedData = this->theCoolerContains(data);
        if(receivedData->at(1).at(0) == 1){
            //Print FALSE
            return false;
        }else{
            //Print Adding
            return true;
        }
    }

    bool remove(string data) {
        vector<vector<int>> *receivedData = this->theCoolerContains(data);
        if(receivedData->at(1).at(0) == 0){
            return false;
        }else{
            holdVals[receivedData->at(0).at(receivedData->at(0).size()-1)] = "<REMOVED>";
        }
    }

    void displayTable() {

    };

    void resize() {

    };

    int HashMultiplicative(string key) {
        int stringHash = permInitialValue;
        for (int x = 0; x < key.length(); x++) {
            stringHash = (stringHash * permHashMultiplier) + key[x];
        }
        return stringHash % permSize;
    }
};