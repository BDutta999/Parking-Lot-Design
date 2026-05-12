// main.cpp
#include "parking_lot.h"

int main() {
    ParkingLot& lot = ParkingLot::getInstance();

    // Setup: 2 floors
    auto f1 = std::make_unique<Floor>(1);
    f1->addSpot(std::make_unique<ParkingSpot>("F1-S1", SpotType::SMALL));
    f1->addSpot(std::make_unique<ParkingSpot>("F1-M1", SpotType::MEDIUM));
    f1->addSpot(std::make_unique<ParkingSpot>("F1-L1", SpotType::LARGE));

    auto f2 = std::make_unique<Floor>(2);
    f2->addSpot(std::make_unique<ParkingSpot>("F2-M1", SpotType::MEDIUM));

    lot.addFloor(std::move(f1));
    lot.addFloor(std::move(f2));

    // Vehicles
    Car   car("KA-01-AB-1234");
    Bike  bike("MH-02-CD-5678");
    Truck truck("DL-03-EF-9012");

    // Park
    Ticket* t1 = lot.parkVehicle(&car);
    Ticket* t2 = lot.parkVehicle(&bike);
    Ticket* t3 = lot.parkVehicle(&truck);

    // Exit
    if (t1) lot.exitVehicle(t1->getId(), PaymentMode::UPI);
    if (t2) lot.exitVehicle(t2->getId(), PaymentMode::CASH);
    if (t3) lot.exitVehicle(t3->getId(), PaymentMode::CARD);

    return 0;
}