#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int MAX_VEHICLES = 10000;
const int MAX_SIZE = 20;

struct Vehicle {
    int id;
    string brand;
    string model;
    int year;
    double price;
    double mileage;
};

struct Node {
    Vehicle vehicle;
    Node* next;
};

Vehicle vehicleArray[MAX_VEHICLES];
int vehicleCount = 0;
Node* userVehicleHead = nullptr;
string Adminname[MAX_SIZE];
string usernames[MAX_SIZE];
string passwords[MAX_SIZE];
int userCount = 0;

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    cout << "\nPress enter to continue...";
    cin.ignore(); cin.get();
}

void displayVehicleTable(Vehicle vehicles[], int count) {
    cout << "ID\tBrand\tModel\tYear\tPrice\tMileage\n";
    cout << "--------------------------------------------------------------\n";
    for (int i = 0; i < count; ++i) {
        Vehicle v = vehicles[i];
        cout << v.id << "\t" << v.brand << "\t" << v.model << "\t"
             << v.year << "\t" << v.price << "\t" << v.mileage << endl;
    }
}

void displayLinkedList(Node* head) {
    cout << "ID\tBrand\tModel\tYear\tPrice\tMileage\n";
    cout << "--------------------------------------------------------------\n";
    Node* temp = head;
    while (temp) {
        Vehicle v = temp->vehicle;
        cout << v.id << "\t" << v.brand << "\t" << v.model << "\t"
             << v.year << "\t" << v.price << "\t" << v.mileage << endl;
        temp = temp->next;
    }
}

void saveVehiclesToFile() {
    ofstream outFile("vehicles.txt");
    if (!outFile) {
        cerr << "Error: Could not open file for writing.\n";
        return;
    }
    for (int i = 0; i < vehicleCount; ++i) {
        Vehicle v = vehicleArray[i];
        outFile << v.id << " " << v.brand << " " << v.model << " "
                << v.year << " " << v.price << " " << v.mileage << endl;
    }
    outFile.close();
}

void loadVehiclesFromFile() {
    ifstream inFile("vehicles.txt");
    Vehicle v;
    vehicleCount = 0;
    while (inFile >> v.id >> v.brand >> v.model >> v.year >> v.price >> v.mileage) {
        vehicleArray[vehicleCount++] = v;
    }
    inFile.close();
}

void addVehicle() {
    if (vehicleCount >= MAX_VEHICLES) {
        cout << "Vehicle limit reached.\n";
        return;
    }

    Vehicle v;
    cout << "Enter ID: "; cin >> v.id;
    for (int i = 0; i < vehicleCount; ++i) {
        if (vehicleArray[i].id == v.id) {
            cout << "Vehicle ID already exists.\n";
            return;
        }
    }
    cout << "Enter Brand: "; cin >> v.brand;
    cout << "Enter Model: "; cin >> v.model;
    cout << "Enter Year: "; cin >> v.year;
    cout << "Enter Price: "; cin >> v.price;
    cout << "Enter Mileage: "; cin >> v.mileage;

    vehicleArray[vehicleCount++] = v;
    saveVehiclesToFile();
    cout << "Vehicle added successfully!\n";
}

void viewAllVehicles() {
    if (vehicleCount == 0) {
        cout << "No vehicles available.\n";
    } else {
        displayVehicleTable(vehicleArray, vehicleCount);
    }
}

void deleteVehicle() {
    int id;
    cout << "Enter vehicle ID to delete: "; cin >> id;
    for (int i = 0; i < vehicleCount; ++i) {
        if (vehicleArray[i].id == id) {
            for (int j = i; j < vehicleCount - 1; ++j) {
                vehicleArray[j] = vehicleArray[j + 1];
            }
            vehicleCount--;
            saveVehiclesToFile();
            cout << "Vehicle deleted.\n";
            return;
        }
    }
    cout << "Vehicle not found.\n";
}

void updateVehicle() {
    int id;
    cout << "Enter vehicle ID to update: "; cin >> id;
    for (int i = 0; i < vehicleCount; ++i) {
        if (vehicleArray[i].id == id) {
            cout << "Enter new Brand: "; cin >> vehicleArray[i].brand;
            cout << "Enter new Model: "; cin >> vehicleArray[i].model;
            cout << "Enter new Year: "; cin >> vehicleArray[i].year;
            cout << "Enter new Price: "; cin >> vehicleArray[i].price;
            cout << "Enter new Mileage: "; cin >> vehicleArray[i].mileage;
            saveVehiclesToFile();
            cout << "Vehicle updated successfully.\n";
            return;
        }
    }
    cout << "Vehicle not found.\n";
}

void sortVehiclesByPrice() {
    for (int i = 1; i < vehicleCount; ++i) {
        Vehicle key = vehicleArray[i];
        int j = i - 1;
        while (j >= 0 && vehicleArray[j].price > key.price) {
            vehicleArray[j + 1] = vehicleArray[j];
            --j;
        }
        vehicleArray[j + 1] = key;
    }
    cout << "Vehicles sorted by price using insertion sort.\n";
}

void sortVehiclesByYear() {
    for (int i = 0; i < vehicleCount - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < vehicleCount; ++j) {
            if (vehicleArray[j].year < vehicleArray[minIndex].year) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Vehicle temp = vehicleArray[i];
            vehicleArray[i] = vehicleArray[minIndex];
            vehicleArray[minIndex] = temp;
        }
    }
    cout << "Vehicles sorted by year using selection sort.\n";
}

void sortVehiclesByMileage() {
    for (int i = 0; i < vehicleCount - 1; ++i) {
        for (int j = 0; j < vehicleCount - 1 - i; ++j) {
            if (vehicleArray[j].mileage > vehicleArray[j + 1].mileage) {
                Vehicle temp = vehicleArray[j];
                vehicleArray[j] = vehicleArray[j + 1];
                vehicleArray[j + 1] = temp;
            }
        }
    }
    cout << "Vehicles sorted by mileage using bubble sort.\n";
}

void insertIntoUserList() {
    while (userVehicleHead) {
        Node* temp = userVehicleHead;
        userVehicleHead = userVehicleHead->next;
        delete temp;
    }

    for (int i = 0; i < vehicleCount; ++i) {
        Node* newNode = new Node{vehicleArray[i], nullptr};
        if (!userVehicleHead) {
            userVehicleHead = newNode;
        } else {
            Node* temp = userVehicleHead;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }
}

void userSearchByBrand() {
    string brand;
    cout << "Enter brand to search: "; cin >> brand;
    Node* temp = userVehicleHead;
    bool found = false;
    while (temp) {
        if (temp->vehicle.brand == brand) {
            displayVehicleTable(&temp->vehicle, 1);
            found = true;
        }
        temp = temp->next;
    }
    if (!found) cout << "No vehicle found with that brand.\n";
}

void userSearchByModel() {
    string model;
    cout << "Enter model to search: "; cin >> model;
    Node* temp = userVehicleHead;
    bool found = false;
    while (temp) {
        if (temp->vehicle.model == model) {
            displayVehicleTable(&temp->vehicle, 1);
            found = true;
        }
        temp = temp->next;
    }
    if (!found) cout << "No vehicle found with that model.\n";
}

void userBuyVehicle() {
    int id;
    cout << "Enter vehicle ID to buy: ";
    cin >> id;
    for (int i = 0; i < vehicleCount; ++i) {
        if (vehicleArray[i].id == id) {
            cout << "Vehicle Purchased Successfully!\n";
            displayVehicleTable(&vehicleArray[i], 1);
            for (int j = i; j < vehicleCount - 1; ++j) {
                vehicleArray[j] = vehicleArray[j + 1];
            }
            vehicleCount--;
            saveVehiclesToFile();
            insertIntoUserList();
            return;
        }
    }
    cout << "No matching vehicle found with ID " << id << ".\n";
}

bool adminLogin() {
    string Adminname, password;
    cout << "Adminname: "; cin >> Adminname;
    cout << "Password: "; cin >> password;
    return Adminname == "admin" && password == "1234";
}

bool userLogin() {
    string username;
    cout << "Enter Username: "; cin >> username;
    for (int i = 0; i < userCount; ++i) {
        if (usernames[i] == username) {
            string password;
            cout << "Enter Password: "; cin >> password;
            return passwords[i] == password;
        }
    }
    char c;
    cout << "New user detected. Create new account? (y/n): "; cin >> c;
    if (c == 'y' || c == 'Y') {
        cout << "Enter Password for new account: ";
        cin >> passwords[userCount];
        usernames[userCount] = username;
        userCount++;
        return true;
    }
    return false;
}

void adminMenu() {
    int choice;
    do {
        clearConsole();
        cout << "\nAdmin Menu:\n1. Add Vehicle\n2. View All vehicle\n3. Delete Vehicle\n4. Update Vehicle\n5. Sort by Price\n6. Sort by Year\n7. Sort by Mileage\n8. Logout\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: addVehicle(); break;
            case 2: viewAllVehicles(); break;
            case 3: deleteVehicle(); break;
            case 4: updateVehicle(); break;
            case 5: sortVehiclesByPrice(); break;
            case 6: sortVehiclesByYear(); break;
            case 7: sortVehiclesByMileage(); break;
            case 8: return;
        }
        pause();
    } while (true);
}

void userMenu() {
    insertIntoUserList();
    int choice;
    do {
        clearConsole();
        cout << "\nUser Menu:\n1. Buy Vehicle by ID\n2. View All\n3. Search by Brand\n4. Search by Model\n5. Logout\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: userBuyVehicle(); break;
            case 2: displayLinkedList(userVehicleHead); break;
            case 3: userSearchByBrand(); break;
            case 4: userSearchByModel(); break;
            case 5: return;
        }
        pause();
    } while (true);
}

int main() {
    loadVehiclesFromFile();
    int actor;
    clearConsole();
    cout << endl << endl << endl;
    cout << "*******************************************************************************\n";
    cout << "                       WELCOME TO ETHIO VEHICLE SALES\n";
    cout << "*******************************************************************************\n";

    while (true) {
        cout << "\nVehicle Seller Management System\n1. Admin\n2. User\n3. Exit\nChoose actor: ";
        cin >> actor;
        clearConsole();
        if (actor == 1) {
            if (adminLogin()) adminMenu();
            else cout << "Invalid Admin!\n";
        } else if (actor == 2) {
            if (userLogin()) userMenu();
            else cout << "Login failed.\n";
        } else if (actor == 3) break;
        else cout << "invalid actor.";
        pause();
    }

    while (userVehicleHead) {
        Node* temp = userVehicleHead;
        userVehicleHead = userVehicleHead->next;
        delete temp;
    }

    return 0;
}
