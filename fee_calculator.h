// fee_calculator.h
#pragma once
#include "ticket.h"

class FeeCalculator {
    // Rates per hour by spot type
    static constexpr double SMALL_RATE  = 20.0;
    static constexpr double MEDIUM_RATE = 40.0;
    static constexpr double LARGE_RATE  = 80.0;

public:
    double calculate(const Ticket& t) const {
        double rate = MEDIUM_RATE;
        switch (t.getSpot()->getType()) {
            case SpotType::SMALL:  rate = SMALL_RATE;  break;
            case SpotType::LARGE:  rate = LARGE_RATE;  break;
            default: break;
        }
        // Minimum 1 hour billing
        return rate * std::max(1.0, t.getDurationHours());
    }
};