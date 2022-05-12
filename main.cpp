#include <iostream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <cstring>

using namespace std;

class StringHash {
    string* holdVals = new string[5];
    int permSize;
    int permInitialValue;
    int permHashMultiplier;
    int permRelativePrime;

    vector<vector<int>> *theCoolerContains(string data) {
        vector<int> holdVisited;
        bool found = false;
        bool endReached = false;
        /* stringstream tempHolder;
         tempHolder << holdVals->size();
         int sizeOfList = atoi(tempHolder.str().c_str());*/
        int sizeOfList = holdVals->length();
        int x = 0;
        while (!found && !endReached) {
            int firstHash = HashMultiplicative(data);
            int secondHash = permRelativePrime - (firstHash % permRelativePrime);
            int doubleHash = (firstHash + (x * secondHash)) % permSize;
            if (holdVals[doubleHash] == data) {
                found = true;
            }
            if (x + 1 >= sizeOfList) {
                endReached = true;
            }
            holdVisited.push_back(doubleHash);
            x++;
        }
        vector<vector<int>> *dataToReturn = new vector<vector<int>>();
        dataToReturn->push_back(holdVisited);
        vector<int> isTrueOrNot;
        if (found) {
            isTrueOrNot.push_back(1);
        } else {
            isTrueOrNot.push_back(0);
        }
        dataToReturn->push_back(isTrueOrNot);
        return dataToReturn;
    }

    bool theCoolerAdd(string data, bool coolMode) {
        vector<vector<int>> *receivedData = this->theCoolerContains(data);
        if (coolMode) {
            cout << "Rehashing \"" + data + "\"";
        } else {
            cout << "Adding \"" + data + "\"";
        }
        bool sizeChanged = false;
        bool valFound = false;
        int locAdded = -1;
        stringstream tempHolder5;
        tempHolder5 << receivedData->at(0).size();
        int holdDataSize = atoi(tempHolder5.str().c_str());
        if(holdDataSize > permSize){
            holdDataSize = permSize;
            sizeChanged = true;
        }
        for (int x = 0; x < holdDataSize; x++) {
            if (!valFound) {
                cout << " -> " << receivedData->at(0).at(x);
                if (holdVals[receivedData->at(0).at(x)].compare("<REMOVED>") == 0 ||
                    holdVals[receivedData->at(0).at(x)].compare("<EMPTY>") == 0) {
                    valFound = true;
                    locAdded = receivedData->at(0).at(x);
                }
            }


        }

        if (receivedData->at(1).at(0) == 1 || sizeChanged) {
            //Print FALSE
            cout << " -> FAILED";
            return false;
        } else {
            //Print Adding
            holdVals[locAdded] = data;
            return true;
        }
    };

    int HashMultiplicative(string key) {
        int stringHash = permInitialValue;
        int keyLength = key.length();
        for (int x = 0; x < keyLength; x++) {
            stringHash = (stringHash * permHashMultiplier) + key[x];
        }
        return abs(stringHash % permSize);
    }

public:
    StringHash(int size, int initialValue, int hashMultiplier, int relativePrime) {
        string* tempVals = new string[size];
        for(int x=0;x<size;x++){
            tempVals[x] = "<EMPTY>";
        }
        delete[] holdVals;
        holdVals = tempVals;
        permSize = size;
        permInitialValue = initialValue;
        permHashMultiplier = hashMultiplier;
        permRelativePrime = relativePrime;
    }

    bool contains(string data) {
        vector<int> holdVisited;
        bool found = false;
        bool endReached = false;
        int size = permSize;
        int x = 0;
        while (!found && !endReached) {
            int firstHash = HashMultiplicative(data);
            int secondHash = permRelativePrime - (firstHash % permRelativePrime);
            int doubleHash = (firstHash + (x * secondHash)) % permSize;
           // displayTable();
            if (holdVals[doubleHash].compare(data) == 0) {
                found = true;
            }
            if (x + 1 >= size || holdVals[doubleHash] == "<EMPTY>") {
                endReached = true;
            }
            holdVisited.push_back(doubleHash);
            x++;
        }
        cout << "Searching \"" + data + "\"";
        stringstream tempHolder2;
        tempHolder2 << holdVisited.size();
        int holdVisitedSize = atoi(tempHolder2.str().c_str());

        bool searchDone = false;
        for (int x = 0; x < holdVisitedSize; x++) {
            if(!searchDone){
                cout << " -> " << holdVisited.at(x);
                if(data.compare(holdVals[holdVisited.at(x)]) == 0){
                    searchDone = true;
                }
            }
        }
        cout << " ";
        if (found) {
            cout << "TRUE";
        } else {
            cout << "-> FAILED" << endl << "FALSE";
        }
        return found;
    }

    bool add(string data) {
        return theCoolerAdd(data, false);
    }

    bool remove(string data) {
        vector<vector<int>> *receivedData = this->theCoolerContains(data);

        cout << "Removing \"" + data + "\"";
        stringstream tempHolder5;
        tempHolder5 << receivedData->at(0).size();
        int holdDataSize = atoi(tempHolder5.str().c_str());
        bool keepDisplaying = true;
        for (int x = 0; x < holdDataSize; x++) {
            if (keepDisplaying) {
                cout << " -> " << receivedData->at(0).at(x);
            }
            if (holdVals[receivedData->at(0).at(x)].compare(data) == 0) {
                keepDisplaying = false;
            }
        }
        if (receivedData->at(1).at(0) == 0) {
            cout << " -> FAILED";
        }
        if (receivedData->at(1).at(0) == 0) {
            return false;
        } else {
            holdVals[receivedData->at(0).at(receivedData->at(0).size() - 1)] = "<REMOVED>";
            return true;
        }
    }

    void resize() {
        string* tempVals = new string[permSize*2];
        for(int x=0;x<permSize*2;x++){
            tempVals[x] = "<EMPTY>";
        }
        string* backUpVals = new string[permSize];
        for(int y=0;y<permSize;y++){
            backUpVals[y] = holdVals[y];
        }
        delete[] holdVals;
        holdVals = tempVals;
        permSize = permSize*2;
        for (int x = 0; x < backUpVals->length(); x++) {
            theCoolerAdd(backUpVals[x], true);
            if (x != permSize - 1) {
                cout << endl;
            }
        }
    }

    void displayTable() {
        for (int x = 0; x < permSize; x++) {
            cout << x << " : " << holdVals[x];
            if (x != permSize - 1) {
                cout << endl;
            }
        }
    }
};

int main() {
    bool keepGoing = true;
    int tableSize = 0;
    int initialHashVal;
    int hashMultiplier;
    int relPrimeVal;
    std::cout << "Enter table size:";
    std::cin >> tableSize;
    std::cout << std::endl;
    std::cout << "Enter initial hash value:";
    std::cin >> initialHashVal;
    std::cout << std::endl;
    std::cout << "Enter hash multiplier:";
    std::cin >> hashMultiplier;
    std::cout << std::endl;
    std::cout << "Enter relative prime value:";
    std::cin >> relPrimeVal;
    //std::cout << std::endl;
    StringHash objectToUse = StringHash(tableSize, initialHashVal, hashMultiplier, relPrimeVal);
    std::string choice = "";
    do {
        do {
            cout << endl;
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
            objectToUse.contains(stringToUse);
        } else if (choice == "2") {
            std::cout << "String to add:";
            std::cin >> stringToUse;
            objectToUse.add(stringToUse);
        } else if (choice == "3") {
            std::cout << "String to remove:";
            std::cin >> stringToUse;
            objectToUse.remove(stringToUse);
        } else if (choice == "4") {
            //Display things
            objectToUse.displayTable();
        } else if (choice == "5") {
            //Resize things
            objectToUse.resize();
        } else {
            keepGoing = false;
        }

    } while (keepGoing);
}