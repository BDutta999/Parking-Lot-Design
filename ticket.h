// ticket.h
#pragma once
#include <ctime>
#include <string>
#include "parking_spot.h"
#include "vehicle.h"

class Ticket {
    std::string  ticketId;
    time_t       entryTime;
    ParkingSpot* spot;
    Vehicle*     vehicle;

public:
    Ticket(const std::string& id, ParkingSpot* s, Vehicle* v)
        : ticketId(id), spot(s), vehicle(v) {
        entryTime = std::time(nullptr);
    }

    std::string  getId()       const { return ticketId; }
    time_t       getEntry()    const { return entryTime; }
    ParkingSpot* getSpot()     const { return spot; }
    Vehicle*     getVehicle()  const { return vehicle; }

    // Duration in hours (fractional)
    double getDurationHours() const {
        return std::difftime(std::time(nullptr), entryTime) / 3600.0;
    }
};