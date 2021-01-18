/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

#include <iostream>

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork() {
    // TODO
    this->head = NULL;
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
    // TODO: Complete the definition
    if (previous == NULL) {
        Country* new_Country = new Country;
        new_Country->name = countryName;
        new_Country->next = head;
        head = new_Country;
        cout << "adding: " << countryName << " (HEAD)" << endl;
    } else {
        Country* new_Country = new Country;
        new_Country->name = countryName;
        new_Country->next = previous->next;
        previous->next = new_Country;
        cout << "adding: " << countryName << " (prev: " << previous->name << ")"
             << endl;
    }
}

/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup() {
    // TODO
    insertCountry(NULL, "United States");
    string countries[] = {"Canada", "Brazil", "India", "China", "Australia"};
    Country* temp = this->head;
    for (int i = 0; i < 5; i++) {
        insertCountry(temp, countries[i]);
        temp = temp->next;
    }
}

/*
 * Purpose: Search the network for the specified country and return a pointer to
 * that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 */
Country* CountryNetwork::searchNetwork(string countryName) {
    // TODO
    Country* nextTemp = this->head;
    while (nextTemp != NULL || nextTemp->name != countryName) {
        nextTemp = nextTemp->next;
    }
    if (nextTemp != NULL) {
        return nextTemp;
    } else {
        return NULL;
    }
}

/*
 * Purpose: Transmit a message across the network to the
 *   receiver. Msg should be stored in each country it arrives
 *   at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
void CountryNetwork::transmitMsg(string receiver, string message) {
    // TODO
    Country* temp = this->head;
    if (this->head == NULL) {
        cout << "Empty List" << endl;
    } else if (searchNetwork(receiver) == NULL) {
        cout << "Country not found" << endl;
    } else {
        while (temp != NULL && temp->name != receiver) {
            temp->message = message;
            temp->numberMessages++;
            cout << temp->name
                 << " [# messages received: " << temp->numberMessages
                 << "] received: " << temp->message << endl;
            temp = temp->next;
        }
        temp->message = message;
        temp->numberMessages++;
        cout << temp->name << " [# messages received: " << temp->numberMessages
             << "] received: " << temp->message << endl;
    }
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath() {
    // TODO
    if (this->head == NULL) {
        cout << "nothing in path" << endl;
    } else {
        Country* temp = this->head;
        cout << "== CURRENT PATH ==" << endl;
        while (temp != NULL) {
            cout << temp->name << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl << "===" << endl;
    }
}
