// parking_lot.h
#pragma once
#include "floor.h"
#include "ticket.h"
#include "fee_calculator.h"
#include "payment.h"
#include <unordered_map>
#include <vector>
#include <memory>
#include <atomic>

class ParkingLot {
    std::vector<std::unique_ptr<Floor>>          floors;
    std::unordered_map<std::string, std::unique_ptr<Ticket>> activeTickets;
    FeeCalculator                                feeCalc;
    std::atomic<int>                             ticketCounter{0};

    // Singleton
    ParkingLot() = default;

public:
    static ParkingLot& getInstance() {
        static ParkingLot instance;
        return instance;
    }
    ParkingLot(const ParkingLot&) = delete;
    ParkingLot& operator=(const ParkingLot&) = delete;

    void addFloor(std::unique_ptr<Floor> f) {
        floors.push_back(std::move(f));
    }

    // Entry: find spot, issue ticket — O(floors * spots)
    Ticket* parkVehicle(Vehicle* v) {
        for (auto& floor : floors) {
            ParkingSpot* spot = floor->getAvailableSpot(v->getType());
            if (spot) {
                spot->assign(v);
                std::string id = "TKT-" + std::to_string(++ticketCounter);
                auto ticket = std::make_unique<Ticket>(id, spot, v);
                Ticket* raw = ticket.get();
                activeTickets[id] = std::move(ticket);
                std::cout << "[Entry] Issued " << id
                          << " | Spot: " << spot->getId() << "\n";
                return raw;
            }
        }
        std::cout << "[Entry] No available spot for vehicle type.\n";
        return nullptr;
    }

    // Exit: calculate fee, process payment, free spot
    bool exitVehicle(const std::string& ticketId, PaymentMode mode) {
        auto it = activeTickets.find(ticketId);
        if (it == activeTickets.end()) {
            std::cout << "[Exit] Invalid ticket.\n";
            return false;
        }
        Ticket* t = it->second.get();
        double fee = feeCalc.calculate(*t);

        Payment pay(fee, mode);
        if (!pay.process()) return false;

        t->getSpot()->free();
        activeTickets.erase(it);
        std::cout << "[Exit] Spot freed. Thank you!\n";
        return true;
    }
};