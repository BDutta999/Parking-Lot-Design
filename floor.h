// floor.h
#pragma once
#include "parking_spot.h"
#include <vector>
#include <memory>

class Floor {
    int floorNum;
    std::vector<std::unique_ptr<ParkingSpot>> spots;

public:
    Floor(int num) : floorNum(num) {}

    void addSpot(std::unique_ptr<ParkingSpot> spot) {
        spots.push_back(std::move(spot));
    }

    // O(n) scan — can be optimized with per-type free-lists
    ParkingSpot* getAvailableSpot(VehicleType vt) {
        for (auto& s : spots)
            if (s->isAvailable() && ParkingSpot::isCompatible(vt, s->getType()))
                return s.get();
        return nullptr;
    }

    int getFloorNum() const { return floorNum; }
};