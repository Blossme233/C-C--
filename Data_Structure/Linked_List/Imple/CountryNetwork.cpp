/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represent communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork() {
    /* finished. do not touch. */
    head = NULL;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CountryNetwork::isEmpty() {
    /* finished. do not touch. */
    return (head == NULL);
}

/*
 * Purpose: Add a new Country to the network
 *   between the Country *previous and the Country that follows it in the
 * network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName) {
    // if we are passed an empty list, just create a new head node, and return
    if (head == NULL) {
        cout << "adding: " << countryName << " (HEAD)" << endl;
        head = new Country;
        head->name = countryName;
        head->numberMessages = 0;
        head->next = NULL;
    }
    // if it's not empty, we need to search for previous and append our node
    // there.
    else if (previous == NULL) {
        // case where it's a new head Country
        cout << "adding: " << countryName << " (HEAD)" << endl;
        Country* c = new Country;
        c->name = countryName;
        c->numberMessages = 0;
        c->next = head;
        head = c;
    } else {
        cout << "adding: " << countryName << " (prev: " << previous->name << ")"
             << endl;
        Country* newCountry = new Country;
        newCountry->name = countryName;
        newCountry->numberMessages = 0;
        newCountry->next = previous->next;
        previous->next = newCountry;
    }
}

/*
 * Purpose: delete the country in the network with the specified name.
 * @param countryName name of the country to delete in the network
 * @return none
 */
void CountryNetwork::deleteCountry(string countryName) {
    // TODO: Complete this function
    Country* temp = head;
    Country* prev = head;
    while (temp != NULL) {
        if (temp->name == countryName) {
            if (temp == head) {
                head = temp->next;
                delete temp;
            } else {
                prev->next = temp->next;
                delete temp;
            }
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        cout << "Country does not exist." << endl;
    }
}

/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup() {
    int num_countries = 6;
    string countries[] = {"United States", "Canada", "Brazil",
                          "India",         "China",  "Australia"};
    // deleteEntireNetwork();
    Country* prev = NULL;
    for (int i = 0; i < num_countries; i++) {
        insertCountry(prev, countries[i]);
        prev = searchNetwork(countries[i]);
    }
}

/*
 * Purpose: Search the network for the specified country and return a pointer to
 * that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 * @see insertCountry, deletecountry
 */
Country* CountryNetwork::searchNetwork(string countryName) {
    // Search until the head is NULL, or we find the country
    Country* ptr = head;
    while (ptr != NULL && ptr->name != countryName) {
        ptr = ptr->next;
    }
    // Return the node, or NULL
    return ptr;
}

/*
 * Purpose: Creates a loop from last node to the country specified.
 * @param countryName name of the country to loop back
 * returns pointer to last node before loop creation (to break the loop)
 */
Country* CountryNetwork::createLoop(string countryName) {
    // TODO: Complete this function
    Country* loopTemp = head;
    Country* lastNode = head;
    while (lastNode->next != NULL) {
        lastNode = lastNode->next;
    }
    while (loopTemp != NULL) {
        if (loopTemp->name == countryName) {
            lastNode->next = loopTemp;
            break;
        }
        loopTemp = loopTemp->next;
    }

    return lastNode;
}

/*
 * Purpose: deletes all countries in the network starting at the head country.
 * @param none
 * @return none
 */
void CountryNetwork::deleteEntireNetwork() {
    // TODO: Complete this function
    Country* temp = head;

    while (temp != NULL) {
        Country* current = temp;
        cout << "deleting: " << temp->name << endl;
        delete current;
        temp = temp->next;
    }
    cout << "Deleted network" << endl;
    head = NULL;
}

/*
 *Purpose: to detect loop in the linkedlist
 * @param
 * returns true if loop is detected. Otherwise return false.
 */
bool CountryNetwork::detectLoop() {
    // TODO: Complete this function
    Country* temp = head;
    Country* loopTemp = temp->next;
    while (loopTemp->next != NULL && loopTemp != NULL) {
        if (temp == loopTemp) {
            return true;
            break;
        }
        temp = temp->next;
        loopTemp = loopTemp->next->next;
    }
    return false;
}

/*
 * Purpose: Take the chunk of nodes from start index to end index
 *          Move that chunk at the end of the List
 *@param: start index
 *@param: end index
 * return none
 */
void CountryNetwork::readjustNetwork(int start_index, int end_index) {
    // TODO: Complete this function
    if (head == NULL) {
        cout << "Linked List is Empty" << endl;
    } else {
        Country* lastNode = head;
        Country* temp;
        Country* prev;
        int count = 0;
        while (lastNode->next != NULL) {
            if (count == start_index - 1) {
                prev = lastNode;
            }
            if (count == start_index) {
                temp = lastNode;
            }
            lastNode = lastNode->next;
            count++;
        }
        if (end_index > count || end_index < 0 || end_index < start_index) {
            cout << "Invalid end index" << endl;
        } else if (start_index > count || start_index < 0) {
            cout << "Invalid start index" << endl;
        } else if (start_index > end_index) {
            cout << "Invalid indices" << endl;
        } else {
            int numRead = end_index - start_index;
            Country* endNode = temp;
            for (int i = 0; i < numRead; i++) {
                endNode = endNode->next;
            }
            if (temp == head) {
                head = endNode->next;
            }
            prev->next = endNode->next;
            lastNode->next = temp;
            endNode->next = NULL;
        }
    }
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath() {
    cout << "== CURRENT PATH ==" << endl;
    // If the head is NULL
    Country* ptr = head;
    if (ptr == NULL) cout << "nothing in path" << endl;

    // Otherwise print each node, and then a NULL
    else {
        while (ptr->next != NULL) {
            cout << ptr->name << " -> ";
            ptr = ptr->next;
        }
        cout << ptr->name << " -> ";
        cout << "NULL" << endl;
    }
    cout << "===" << endl;
}
