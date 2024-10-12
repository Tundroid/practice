# Nana Car Rental Management System

This project simulates a car rental management system using linked lists to manage the company's fleet of cars. It allows users to perform a variety of rental operations via a menu-based interface.

## Features

The system manages three lists of cars:
- **Available-for-rent**: Cars ready for customers, ordered by mileage (least first).
- **Rented**: Cars currently rented out, ordered by expected return date.
- **In-repair**: Cars undergoing repairs.

### Available Transactions
1. **Add a new car** to the available-for-rent list.
2. **Return a car** to the available-for-rent list (from rented).
3. **Return a car** to the in-repair list (from rented).
4. **Transfer a car** from the in-repair list to available-for-rent.
5. **Rent a car** from the available-for-rent list.
6. **Print all car lists** (available, rented, repair).
7. **Quit** the program (saves car data to text files).

### Key Program Features
- **Charge Calculation**: For car returns (transactions 2 & 3), the charge is based on mileage:
  - $80.00 flat rate for up to 200 km
  - $0.15 per km for any additional kilometers
- **Input Validation**:
  - Mileage must be valid and increasing for returns.
  - Plate numbers must be 2-8 characters and contain only letters or numbers.
  - Expected return dates must be valid.
- **Data Persistence**: On quitting, the car lists are saved to text files (`available.txt`, `rented.txt`, `repair.txt`) and loaded when the program restarts.

## How to Run the Program

1. **Compile the program** using a C compiler:
   ```bash
   gcc main.c util.c -o nana_car_rental
2. **Run the program**:
   ```bash
   ./nana_car_rental
