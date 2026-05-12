<div align="center">

<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 860 120" width="860" height="120">
  <rect width="860" height="120" fill="#0d1117" rx="10"/>
  <text x="50%" y="72" font-family="'Courier New', Courier, monospace" font-size="62" font-weight="bold" fill="#ffffff" text-anchor="middle" letter-spacing="8">PARKLOT</text>
  <text x="50%" y="105" font-family="'Courier New', Courier, monospace" font-size="13" fill="#58a6ff" text-anchor="middle" letter-spacing="6">MANAGEMENT SYSTEM</text>
</svg>

# 🅿️ Parking Lot Management System

**A production-grade, thread-safe parking management engine — built with modern C++.**

[![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-22C55E?style=for-the-badge)](LICENSE)
[![Build: Passing](https://img.shields.io/badge/Build-Passing-22C55E?style=for-the-badge&logo=github-actions&logoColor=white)]()
[![Pattern: Singleton](https://img.shields.io/badge/Pattern-Singleton%20%7C%20Strategy%20%7C%20Facade-F59E0B?style=for-the-badge)]()
[![Thread Safe](https://img.shields.io/badge/Thread-Safe-8B5CF6?style=for-the-badge&logo=data:image/svg+xml;base64,)]()

<br/>

> *Engineered for scale. Designed for clarity. Built to last.*

</div>

---

## ✦ Overview

This project is a fully object-oriented **Parking Lot Management System** written in modern C++17. It models a real-world multi-floor parking facility with smart spot allocation, time-based billing, and thread-safe operations — all packaged behind a clean, extensible architecture.

Whether you're studying system design, exploring design patterns, or building a foundation for a real parking backend, this codebase is structured to scale.

---

## ✦ Architecture at a Glance

```
┌─────────────────────────────────────────────────────────┐
│                    ParkingLot  (Singleton + Facade)      │
│                                                          │
│   ┌──────────────┐      ┌──────────────────────────┐    │
│   │   Floor[ ]   │      │   TicketRegistry (Map)   │    │
│   │              │      │   atomic<int> ticketID   │    │
│   │ ┌──────────┐ │      └──────────────────────────┘    │
│   │ │  Spot[ ] │ │                                       │
│   │ │ BIKE/CAR │ │      ┌──────────────────────────┐    │
│   │ │  TRUCK   │ │      │   FeeCalculator           │    │
│   │ └──────────┘ │      │   (Strategy Pattern)      │    │
│   └──────────────┘      └──────────────────────────┘    │
└─────────────────────────────────────────────────────────┘
```

---

## ✦ Design Patterns Used

| Pattern | Applied To | Purpose |
|:--|:--|:--|
| 🔒 **Singleton** | `ParkingLot` | One globally accessible instance |
| 🎭 **Facade** | `ParkingLot` | Simplified interface over complex subsystems |
| ♟️ **Strategy** | `FeeCalculator` | Swappable billing & payment logic |
| 🧩 **Composition** | `Lot → Floor → Spot` | Hierarchical ownership model |
| 🧬 **Inheritance** | `Vehicle` hierarchy | Polymorphic vehicle types |

---

## ✦ Features

- 🚗 &nbsp;**Multi-vehicle support** — Bike, Car, and Truck with type-compatible spot allocation
- 🔍 &nbsp;**Smart spot allocation** — Automatically finds the nearest available compatible spot
- 🧵 &nbsp;**Thread-safe ticketing** — `std::atomic<int>` ensures race-condition-free ticket ID generation
- 🧠 &nbsp;**Memory safe** — Exclusively uses `std::unique_ptr` throughout the ownership hierarchy
- 💰 &nbsp;**Time-based billing** — Minimum 1-hour billing with extensible rate rules per spot type
- 🏗️ &nbsp;**Scalable floor model** — Add floors and spots without touching core logic

---

## ✦ Project Structure

```
parking-lot/
│
├── 📁 src/
│   ├── ParkingLot.h / .cpp       ← Singleton + Facade core
│   ├── Floor.h / .cpp            ← Floor model with spot registry
│   ├── ParkingSpot.h / .cpp      ← Spot types: BIKE, CAR, TRUCK
│   ├── Vehicle.h / .cpp          ← Vehicle hierarchy (Bike, Car, Truck)
│   ├── Ticket.h / .cpp           ← Ticket generation & timestamps
│   └── FeeCalculator.h / .cpp    ← Strategy-based billing engine
│
├── 📁 tests/
│   └── parking_tests.cpp         ← Unit tests
│
├── CMakeLists.txt
└── README.md
```

---

## ✦ Getting Started

### Prerequisites

- C++17 compatible compiler (`g++ 9+`, `clang++ 10+`, or MSVC 2019+)
- CMake 3.14+

### Build

```bash
git clone https://github.com/yourusername/parking-lot.git
cd parking-lot

mkdir build && cd build
cmake ..
make
```

### Run

```bash
./parking_lot
```

---

## ✦ Usage Example

```cpp
// Get the singleton instance
ParkingLot& lot = ParkingLot::getInstance();

// Park a vehicle
auto car = std::make_unique<Car>("KA-01-HH-1234");
Ticket ticket = lot.parkVehicle(std::move(car));

std::cout << "Parked! Ticket ID: " << ticket.getId() << std::endl;

// ... time passes ...

// Unpark and calculate fee
double fee = lot.unparkVehicle(ticket.getId());
std::cout << "Total fee: ₹" << fee << std::endl;
```

---

## ✦ Billing Logic

Fees are computed by `FeeCalculator` based on spot type and duration:

| Spot Type | Rate | Minimum |
|:--|:--|:--|
| 🏍️ Bike | ₹20 / hr | 1 hour |
| 🚗 Car | ₹40 / hr | 1 hour |
| 🚛 Truck | ₹80 / hr | 1 hour |

> Billing is always rounded **up** to the nearest hour. A vehicle parked for 1h 5m is billed for 2 hours.

---

## ✦ Class Hierarchy

```
Vehicle  (abstract)
 ├── Bike
 ├── Car
 └── Truck

ParkingSpot  (abstract)
 ├── BikeSpot
 ├── CarSpot
 └── TruckSpot
```

---

## ✦ Key Technical Decisions

<details>
<summary><b>Why Singleton for ParkingLot?</b></summary>
<br/>
A parking lot is a real-world resource — there must be exactly one authoritative source of truth for spot availability and ticketing. The Singleton pattern enforces this guarantee and provides a global access point without polluting function signatures.
</details>

<details>
<summary><b>Why std::atomic for ticket IDs?</b></summary>
<br/>
In a concurrent environment (multiple entry gates processing vehicles simultaneously), naive integer increments create race conditions. <code>std::atomic&lt;int&gt;</code> guarantees lock-free, sequentially consistent increments without mutexes.
</details>

<details>
<summary><b>Why the Strategy pattern for fees?</b></summary>
<br/>
Billing rules change — weekday vs weekend rates, premium spots, EV discounts. Encapsulating fee logic in a <code>FeeCalculator</code> strategy means new billing models can be added without modifying the core parking logic (Open/Closed Principle).
</details>

<details>
<summary><b>Why unique_ptr throughout?</b></summary>
<br/>
Clear, deterministic ownership. The ParkingLot owns its Floors; each Floor owns its Spots. When a ParkingLot is destroyed, the entire ownership chain is cleaned up automatically — no manual deletes, no leaks.
</details>

---

## ✦ Roadmap

- [ ] Persistent storage (SQLite / file-based)
- [ ] REST API layer (via Crow or Drogon)
- [ ] Real-time spot availability dashboard
- [ ] EV charging spot support
- [ ] Reservation system with advance booking

---

## ✦ Contributing

Contributions are welcome! Please open an issue first to discuss what you'd like to change.

```bash
# Fork → Clone → Branch → PR
git checkout -b feature/your-feature-name
```

---

## ✦ License

Distributed under the **MIT License**. See [`LICENSE`](LICENSE) for details.

---

<div align="center">

**Built with precision in C++17**

*If this helped you — a ⭐ star goes a long way.*

</div>
