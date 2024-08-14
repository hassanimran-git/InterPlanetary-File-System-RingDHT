#include <iostream>
#include <vector>
#include <string>

#include <iomanip>

using namespace std;

class Menu {
private:
    using MenuItem = pair<string, void (Menu::*)()>;
    vector<MenuItem> items;

    void SetupRingDHT() { 
        cout << "Setting up RingDHT,\n"; 
        //Input:
        //Specify Number of Bits in Identifier space
        // Number of Machines
        //Manual or AutoAssignID

        //setup machines and their Routing Tables etc
    }

    void InsertData() { 
        cout << "InsertData\n"; 
        //Specify from which machine The data storage request is sent
        //identify key value pair 
        //show the complete path taken by the request to arrive from source to destination machine 
        //store data in BTree

    }
    void DeleteData() { 
        cout << "DeleteData\n";
        //Specify from which machine The data deletion request is sent
        //identify which machine stores this data using the Content ID povided by user
        //(show the complete path taken by the request to arrive from source to destination machine) not specified 
        //Delete Data
    }
    void AddMachine() { 
        cout << "AddMachine\n"; 
        //Add a Machine to the Ring
        //increment number of Machines in the system
        //Auto Assign or Manual ID 
        //place machine in correct position
        //make adjustments to BTrees & Routing Tables
    }
    void RemoveMachine() { 
        cout << "RemoveMachine\n"; 
        //source to destination path 
        //make djustments to BTrees & Routing Tables
        //decrement number of Machines in the system
    }
    void PrintRoutingTable() { 
        cout << "PrintRoutingTable\n"; 
        //call PrintRoutingTable Function for Current or Specified Machine Node based on ID
    }
    void PrintBTree() { 
        cout << "PrintBTree\n"; 
        //call Print BTree Function for Current or Specified Machine Node based on ID
    }
    void RetrieveData() { 
        cout << "RetrieveData\n"; 
        //Use Content ID to Traverse Ring to get to data
        //return the data  (path to file or String Data itself) based on the key
    }
    void ListMachines() { 
        cout << "ListMachines\n"; 
        //Print the Ring 
        //Machine Names & ID's -> easier for user to use and manage
    }

public:
    Menu() {
        items = {
            {"Setup New IPFS", &Menu::SetupRingDHT},
            {"Insert Data", &Menu::InsertData},
            {"Delete Data", &Menu::DeleteData},
            {"Add Machine", &Menu::AddMachine},
            {"Remove Machine", &Menu::RemoveMachine},
            {"Print Routing Table", &Menu::PrintRoutingTable},
            {"Print BTree", &Menu::PrintBTree},
            {"Retrieve Data", &Menu::RetrieveData},
            {"List Machines", &Menu::ListMachines},
        };
    }

    void display() {
        int choice;

        do {
            cout << "\033[1;31m***********************************************************\n"; // red color
            cout << "              InterPlanetary File System \n";
            cout << "\033[1;31m***********************************************************\n"; // red color
            int index = 1;

            cout << "\033[0m"; // Reset color
            for (const auto& item : items) {
                cout << "\033[1;36m                 " << index << ". " << item.first << "\n"; //cyan
                index++;
            }
            cout << "\033[0m"; // Reset color
            cout << "                 0. Exit\n";
            cout << "\033[1;31m***********************************************************\n"; // red color
            cout << "\033[0m"; // Reset color
            cout << "Enter your choice: ";
            cin >> choice;

            system("cls");

            if (choice > 0 && choice <= items.size()) {
                cout << "\033[1;32m***********************************************************\n"; // Green color
                cout << "                   "; //indent
                (this->*items[choice - 1].second)(); // Execute the selected item's function

                //function ouput -> list etc

                cout << "\033[1;32m***********************************************************\n"; // Green color
            }
            else if (choice != 0) {
                cout << "\033[1;32m***********************************************************\n"; // Green color
                cout << "\033[1;31m          Invalid choice. Please try again.\n"; //red color
                cout << "\033[1;32m***********************************************************\n"; // Green color
            }

        } while (choice != 0);
    }
};


//int main() {
//    Menu menu;
//    menu.display();
//
//    return 0;
//}
