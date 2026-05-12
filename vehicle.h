// vehicle.h
#pragma once
#include "types.h"

class Vehicle {
    protected:
        std::string licensePlate;
        VehicleType type;
    public:
        Vehicle(const std::string& plate, VehicleType t): licensePlate(plate), type(t){}
        virtual ~Vehicle() = default;

        VehicleType getType() const { return type; }
        std::string getPlate() const { return licensePlate; }
};

class Bike  : public Vehicle {
public: Bike(const std::string& p)  : Vehicle(p, VehicleType::BIKE)  {} };

class Car   : public Vehicle {
public: Car(const std::string& p)   : Vehicle(p, VehicleType::CAR)   {} };

class Truck : public Vehicle {
public: Truck(const std::string& p) : Vehicle(p, VehicleType::TRUCK) {} };