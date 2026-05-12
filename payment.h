// payment.h
#pragma once
#include "types.h"
#include <iostream>

class Payment {
    double      amount;
    PaymentMode mode;
    bool        paid = false;

public:
    Payment(double amt, PaymentMode m) : amount(amt), mode(m) {}

    bool process() {
        // Plug in real gateway here; stub for now
        std::cout << "[Payment] ₹" << amount
                  << " via " << modeName() << " — SUCCESS\n";
        paid = true;
        return true;
    }

    bool isPaid() const { return paid; }

private:
    std::string modeName() const {
        switch (mode) {
            case PaymentMode::CASH: return "Cash";
            case PaymentMode::CARD: return "Card";
            case PaymentMode::UPI:  return "UPI";
        }
        return "Unknown";
    }
};