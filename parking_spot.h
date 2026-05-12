// parking_spot.h
#pragma once
#include "types.h"
#include "vehicle.h"

class ParkingSpot {
    std::string spotId;
    SpotType    spotType;
    bool        occupied = false;
    Vehicle*    parkedVehicle = nullptr;

public:
    ParkingSpot(const std::string& id, SpotType t)
        : spotId(id), spotType(t) {}

    bool isAvailable() const { return !occupied; }
    SpotType getType() const { return spotType; }
    std::string getId() const { return spotId; }

    // O(1) assign/free
    bool assign(Vehicle* v) {
        if (occupied) return false;
        parkedVehicle = v;
        occupied = true;
        return true;
    }

    void free() {
        parkedVehicle = nullptr;
        occupied = false;
    }

    // Compatibility: BIKE→SMALL, CAR→MEDIUM, TRUCK→LARGE
    static bool isCompatible(VehicleType vt, SpotType st) {
        if (vt == VehicleType::BIKE  && st == SpotType::SMALL)  return true;
        if (vt == VehicleType::CAR   && st == SpotType::MEDIUM) return true;
        if (vt == VehicleType::TRUCK && st == SpotType::LARGE)  return true;
        return false;
    }
};