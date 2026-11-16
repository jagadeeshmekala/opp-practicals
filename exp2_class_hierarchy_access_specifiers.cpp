// Experiment 2: Class hierarchy (Vehicle -> Car -> ElectricCar)
// Demonstrates access specifiers and member functions
#include <iostream>
#include <string>
using namespace std;

class Vehicle {
private:                         // only Vehicle can access
    int number;

protected:                       // Vehicle and child classes can access
    string brand;

public:                          // everyone can access
    void setVehicle() {
        number = 101;
        brand = "Toyota";
    }

    void displayVehicle() {
        cout << "Vehicle Number: " << number << endl;
        cout << "Brand: " << brand << endl;
    }
};

class Car : public Vehicle {
private:
    int seats;

public:
    void setCar() {
        seats = 5;
    }

    void displayCar() {
        displayVehicle();        // reuse parent's function
        cout << "Number of Seats: " << seats << endl;
    }
};

class ElectricCar : public Car {
private:
    int battery;

public:
    void setElectricCar() {
        battery = 75;
    }

    void displayElectricCar() {
        displayCar();            // reuse Car's function
        cout << "Battery Capacity: " << battery << " kWh" << endl;
    }
};

int main() {
    ElectricCar e;

    e.setVehicle();
    e.setCar();
    e.setElectricCar();

    e.displayElectricCar();

    return 0;
}
