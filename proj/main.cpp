#include <iostream>
#include <cstring>
using namespace std;

struct Customer {
    char name[50];
    char address[50];
    int idNumber;
    bool carRentedOrReserved;
    int carID;
    char status[20];
    int startDate;
    int endDate;
};

struct Car {
    char modelName[50];
    char vehicleType[20];
    char gearShiftType[20];
    int yearOfManufacture;
    double pricePerDay;
    int carID;
    bool availability;
    int renterID;
};

void addNewCustomer(Customer customers[], int customerCount, int maxCustomers);
void addNewCar(Car cars[], int carCount, int maxCars);
int returnNumberOfCustomers(int customerCount);
int findCustomer(Customer customers[], int customerCount, int idNumber);
int findCarByID(Car cars[], int carCount, int carID);
void printCustomerDetails(Customer customers[], int customerCount, Car cars[], int carCount);
int rentCar(Car cars[], int carCount, Customer customers[], int customerCount);
int reserveCar(Car cars[], int carCount, Customer customers[], int customerCount);
int returnCar(Car cars[], int carCount, Customer customers[], int customerCount);
void calculateFines(Car cars[], int carCount, Customer customers[], int customerCount, int currentDate);

int main() {
    const int MAX_CARS = 100;
    const int MAX_CUSTOMERS = 100;
    Car cars[MAX_CARS];
    Customer customers[MAX_CUSTOMERS];
    int carCount = 0, customerCount = 0;
    int choice, currentDate;

    cout << "Enter todays day : ";
    cin >> currentDate;

    do {
        cout << "\nCar Rental System Menu\n";
        cout << "1. Add a new customer\n";
        cout << "2. Add a new car\n";
        cout << "3. Return the number of customers\n";
        cout << "4. Find customer\n";
        cout << "5. Print customer details\n";
        cout << "6. Rent a car\n";
        cout << "7. Reserve a car\n";
        cout << "8. Return a car\n";
        cout << "9. Calculate fines\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addNewCustomer(customers, customerCount, MAX_CUSTOMERS);
                break;
            case 2:
                addNewCar(cars, carCount, MAX_CARS);
                break;
            case 3: {
                int numCustomers = returnNumberOfCustomers(customerCount);
                cout << "Total number of customers: " << numCustomers << endl;
                break;
            }
            case 4: {
                int idNumber;
                cout << "Enter Customer ID Number:\n ";
                cin >> idNumber;
                int customerIndex = findCustomer(customers, customerCount, idNumber);
                if (customerIndex != -1) {
                    cout << "Customer Found: Name: " << customers[customerIndex].name
                         << ", ID: " << customers[customerIndex].idNumber << endl;
                } else {
                    cout << "Customer not found.\n";
                }
                break;
            }
            case 5:
                printCustomerDetails(customers, customerCount, cars, carCount);
                break;
            case 6:
                if (rentCar(cars, carCount, customers, customerCount) == 0) {
                    cout << "Car is now rented\n ";
                } else {
                    cout << "failed to rent .\n";
                }
                break;
            case 7:
                if (reserveCar(cars, carCount, customers, customerCount) == 0) {
                    cout << "car is reserved successfully.\n";
                } else {
                    cout << "failed to reserve car.\n";
                }
                break;
            case 8:
                if (returnCar(cars, carCount, customers, customerCount) == 0) {
                    cout << "car is  returned .\n";
                } else {
                    cout << "failed to return car.\n";
                }
                break;
            case 9:
                calculateFines(cars, carCount, customers, customerCount, currentDate);
                break;
            case 10:
                cout << "Exit \n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 10);

    return 0;
}

void addNewCustomer(Customer customers[], int& customerCount, int maxCustomers) {
    if (customerCount < maxCustomers) {
        Customer newCustomer;
        cout << "Enter Customer Name:\n";
        cin >> newCustomer.name;
        cout << "Enter Customer Address:\n ";
        cin >> newCustomer.address;
        cout << "Enter Customer ID Number: ";
        cin >> newCustomer.idNumber;
        if (findCustomer(customers, customerCount, newCustomer.idNumber) > 0) {
            cout << " Customer ID already exists.\n";
        } else {
            newCustomer.carRentedOrReserved = false;
            newCustomer.carID = 0;
            strcpy(newCustomer.status, "");
            newCustomer.startDate = 0;
            newCustomer.endDate = 0;
            customers[customerCount] = newCustomer;
            customerCount++;
            cout << "Customer added ";
        }
    } else {
        cout << "Cannot add more customers";
    }
}

void addNewCar(Car cars[], int& carCount, int maxCars) {
    if (carCount < maxCars) {
        Car newCar;
        cout << "Enter Car ID:\n ";
        cin >> newCar.carID;
        if (findCarByID(cars, carCount, newCar.carID) != -1) {
            cout << "Car ID already exists.";
        } else {
            cout << "Enter Model Name ";
            cin >> newCar.modelName;
            cout << "Enter Vehicle Type (e.g., SUV, Sedan): ";
            cin >> newCar.vehicleType;
            cout << "Enter Gear Shift Type (Automatic/Manual):  ";
            cin >> newCar.gearShiftType;
            cout << "Enter Year of Manufacture: ";
            cin >> newCar.yearOfManufacture;
            cout << "Enter Price per Day:  ";
            cin >> newCar.pricePerDay;
            newCar.availability = true;
            newCar.renterID = 0;
            cars[carCount] = newCar;
            carCount++;
            cout << "Car added successfuly";
        }
    } else {
        cout << "Cannot add more cars.\n";
    }
}

int returnNumberOfCustomers(int customerCount) {
    return customerCount;
}

int findCustomer(Customer customers[], int customerCount, int idNumber) {
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].idNumber == idNumber) {
            return i;
        }
    }
    return -1;
}

int findCarByID(Car cars[], int carCount, int carID) {
    for (int i = 0; i < carCount; i++) {
        if (cars[i].carID == carID) {
            return i;
        }
    }
    return -1;
}

void printCustomerDetails(Customer customers[], int customerCount, Car cars[], int carCount) {
    if (customerCount == 0) {
        cout << "No customers available";
        return;
    }
    for (int i = 0; i < customerCount; i++) {
        cout << "Customer Name: " << customers[i].name << ", Address: " << customers[i].address
             << ", ID: " << customers[i].idNumber << ", Car rented /Reserved: ";
        if (customers[i].carRentedOrReserved) {
            cout << "Yes" << endl;
            int carIndex = findCarByID(cars, carCount, customers[i].carID);
            if (carIndex != -1) {
                cout << "  Car ID: " << cars[carIndex].carID << ", Model: " << cars[carIndex].modelName
                     << ", Status: " << customers[i].status << ", From: " << customers[i].startDate
                     << ", To: " << customers[i].endDate << endl;
            }
        } else {
            cout << "No" << endl;
        }
    }
}
int rentCar(Car cars[], int carCount, Customer customers[], int customerCount) {
    int carID, startDate, endDate, idNumber;
    cout << "Enter Customer ID Number: ";
    cin >> idNumber;
    
    int customerIndex = findCustomer(customers, customerCount, idNumber);
    if (customerIndex == -1 || customers[customerIndex].carRentedOrReserved) {
        return -1;
    }

    cout << "Enter Car ID: ";
    cin >> carID;
    int carIndex = findCarByID(cars, carCount, carID);
    
    if (carIndex == -1 || !cars[carIndex].availability) {
        return -1;
    }

    cout << "Enter Start Date: ";
    cin >> startDate;
    cout << "Enter end Date:  ";
    cin >> endDate;

    if (startDate >= endDate) {
       cout <<" Not possible dates";
       return -1;
        }
    

    cars[carIndex].availability = false;
    cars[carIndex].renterID = idNumber;
    customers[customerIndex].carRentedOrReserved = true;
    customers[customerIndex].carID = carID;
    strcpy(customers[customerIndex].status, "rented");

    return 0;
}

}

int reserveCar(Car cars[], int carCount, Customer customers[], int customerCount) {
    int carID, startDate, endDate, idNumber;
    cout << "Enter Customer ID Number: ";
    cin >> idNumber;

    int customerIndex = findCustomer(customers, customerCount, idNumber);
    if (customerIndex == -1 || customers[customerIndex].carRentedOrReserved) {
        return -1;
    }

    cout << "Enter Car ID: ";
    cin >> carID;
    int carIndex = findCarByID(cars, carCount, carID);
    
    if (carIndex == -1 || !cars[carIndex].availability) {
        return -1;
    }

    cout << "Enter Start Date: ";
    cin >> startDate;
    cout << "Enter End Date: ";
    cin >> endDate;

    if (startDate <= endDate) {
    
    }

    cars[carIndex].availability = false;
    cars[carIndex].renterID = idNumber;
    customers[customerIndex].carRentedOrReserved = true;
    customers[customerIndex].carID = carID;
    strcpy(customers[customerIndex].status, "Reserved");
    customers[customerIndex].startDate = startDate;
    customers[customerIndex].endDate = endDate;

    return 0;
}


int returnCar(Car cars[], int carCount, Customer customers[], int customerCount) {
    int carID;
    cout << "Enter Car ID: ";
    cin >> carID;
    int carIndex = findCarByID(cars, carCount, carID);

    if (carIndex == -1 || cars[carIndex].availability) {
        return -1;
    }

    int customerIndex = findCustomer(customers, customerCount, cars[carIndex].renterID);
    if (customerIndex != -1) {
        cars[carIndex].availability = true;
        customers[customerIndex].carRentedOrReserved = false;
        customers[customerIndex].carID = 0;
        strcpy(customers[customerIndex].status, "");
        customers[customerIndex].startDate = 0;
        customers[customerIndex].endDate = 0;
        return 0;
    }

    return -1;
}
