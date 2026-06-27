#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// ─────────────────────────────────────────
//  ROOM CLASS
// ─────────────────────────────────────────
class Room {
private:
    int roomNumber;
    string roomType;
    long pricePerNight;
    bool isAvailable;

public:
    Room(int number, string type, long price) {
        roomNumber   = number;
        roomType     = type;
        pricePerNight = price;
        isAvailable  = true;
    }

    int    get_RoomNumber()    { return roomNumber; }
    string get_RoomType()      { return roomType; }
    long   get_Price()         { return pricePerNight; }
    bool   get_Availability()  { return isAvailable; }

    void setAvailability(bool status) {
        isAvailable = status;
    }

    void showRoom() {
        cout << left
             << setw(10) << roomNumber
             << setw(10) << roomType
             << setw(10) << pricePerNight
             << setw(10) << (isAvailable ? "Available" : "Booked")
             << endl;
    }
};

// ─────────────────────────────────────────
//  GUEST CLASS
// ─────────────────────────────────────────
class Guest {
private:
    string guestID;
    string name;
    string phone;

public:
    Guest(string id, string nm, string ph) {
        guestID = id;
        name    = nm;
        phone   = ph;
    }

    string get_GuestID() { return guestID; }
    string get_Name()    { return name; }
    string get_Phone()   { return phone; }
};

// ─────────────────────────────────────────
//  BOOKING CLASS
// ─────────────────────────────────────────
class Booking {
private:
    string bookingID;
    string guestID;
    string guestName;
    int    roomNumber;
    string roomType;
    int    checkInDay;
    int    checkOutDay;
    long   totalBill;

public:
    Booking(string bID, string gID, string gName,
            int rNum, string rType,
            int inDay, int outDay, long price) {
        bookingID  = bID;
        guestID    = gID;
        guestName  = gName;
        roomNumber = rNum;
        roomType   = rType;
        checkInDay  = inDay;
        checkOutDay = outDay;
        totalBill  = (outDay - inDay) * price;
    }

    string get_BookingID()  { return bookingID; }
    string get_GuestID()    { return guestID; }
    int    get_RoomNumber() { return roomNumber; }
    long   get_TotalBill()  { return totalBill; }

    void showBooking() {
        cout << "\n===== Booking Details =====" << endl;
        cout << "Booking ID   : " << bookingID         << endl;
        cout << "Guest Name   : " << guestName         << endl;
        cout << "Room Number  : " << roomNumber        << endl;
        cout << "Room Type    : " << roomType          << endl;
        cout << "Check-In     : Day " << checkInDay    << endl;
        cout << "Check-Out    : Day " << checkOutDay   << endl;
        cout << "Total Bill   : " << totalBill         << endl;
        cout << "===========================" << endl;
    }
};

// ─────────────────────────────────────────
//  HOTEL SYSTEM CLASS
// ─────────────────────────────────────────
class HotelSystem {
private:
    vector<Room>    rooms;
    vector<Guest>   guests;
    vector<Booking> bookings;

    long totalRevenue = 0;
    int  totalRooms   = 10;   // max room limit
    int  nextGuest    = 1;
    int  nextBooking  = 1;

    // ── helpers ──────────────────────────
    string generateGuestID() {
        return "G" + to_string(100 + nextGuest++);
    }

    string generateBookingID() {
        return "B" + to_string(200 + nextBooking++);
    }

    Room* findRoom(int roomNumber) {
        for (auto &room : rooms) {
            if (room.get_RoomNumber() == roomNumber)
                return &room;
        }
        return nullptr;
    }

    Booking* findBooking(string bookingID) {
        for (auto &booking : bookings) {
            if (booking.get_BookingID() == bookingID)
                return &booking;
        }
        return nullptr;
    }

public:
    // ── setup rooms ──────────────────────
    void setupRooms() {
        // Single rooms
        for (int i = 101; i <= 104; i++)
            rooms.emplace_back(i, "Single", 1000);
        // Double rooms
        for (int i = 201; i <= 204; i++)
            rooms.emplace_back(i, "Double", 2000);
        // Suite rooms
        for (int i = 301; i <= 302; i++)
            rooms.emplace_back(i, "Suite",  5000);

        cout << "Hotel setup done. Total rooms: "
             << rooms.size() << endl;
    }

    // ── show all rooms ───────────────────
    void showAllRooms() {
        cout << "\n===== All Rooms =====" << endl;
        cout << left
             << setw(10) << "Room No"
             << setw(10) << "Type"
             << setw(10) << "Price"
             << setw(10) << "Status"
             << endl;
        cout << string(40, '-') << endl;
        for (auto &room : rooms)
            room.showRoom();
    }

    // ── show available rooms ─────────────
    void showAvailableRooms() {
        cout << "\n===== Available Rooms =====" << endl;
        cout << left
             << setw(10) << "Room No"
             << setw(10) << "Type"
             << setw(10) << "Price"
             << setw(10) << "Status"
             << endl;
        cout << string(40, '-') << endl;
        for (auto &room : rooms) {
            if (room.get_Availability())
                room.showRoom();
        }
    }

    // ── book room ────────────────────────
    void bookRoom() {
        // check room limit
        int bookedCount = 0;
        for (auto &room : rooms)
            if (!room.get_Availability()) bookedCount++;

        if (bookedCount >= totalRooms) {
            cout << "Hotel is Full! No rooms available.\n";
            return;
        }

        string name, phone;
        int roomNum, inDay, outDay;

        cout << "\n===== Book a Room =====" << endl;
        cout << "Enter Guest Name  : ";
        getline(cin >> ws, name);
        cout << "Enter Phone       : ";
        cin  >> phone;

        showAvailableRooms();

        cout << "Enter Room Number : ";
        cin  >> roomNum;

        Room* room = findRoom(roomNum);
        if (room == nullptr) {
            cout << "Room not found!\n";
            return;
        }
        if (!room->get_Availability()) {
            cout << "Room is already booked!\n";
            return;
        }

        cout << "Enter Check-In Day  : ";
        cin  >> inDay;
        cout << "Enter Check-Out Day : ";
        cin  >> outDay;

        if (outDay <= inDay) {
            cout << "Invalid days!\n";
            return;
        }

        string gID = generateGuestID();
        string bID = generateBookingID();

        guests.emplace_back(gID, name, phone);
        bookings.emplace_back(bID, gID, name,
                              roomNum, room->get_RoomType(),
                              inDay, outDay, room->get_Price());

        room->setAvailability(false);

        cout << "\nBooking Successful!" << endl;
        cout << "Your Booking ID : " << bID << endl;

        findBooking(bID)->showBooking();
    }

    // ── check out ────────────────────────
    void checkOut() {
        string bID;
        cout << "\n===== Check Out =====" << endl;
        cout << "Enter Booking ID : ";
        cin  >> bID;

        Booking* booking = findBooking(bID);
        if (booking == nullptr) {
            cout << "Booking not found!\n";
            return;
        }

        booking->showBooking();

        long bill = booking->get_TotalBill();
        cout << "\nTotal Amount to Pay : " << bill << endl;
        cout << "Payment Collected Successfully!" << endl;

        // free the room
        Room* room = findRoom(booking->get_RoomNumber());
        if (room != nullptr)
            room->setAvailability(true);

        totalRevenue += bill;

        // remove booking
        for (int i = 0; i < bookings.size(); i++) {
            if (bookings[i].get_BookingID() == bID) {
                bookings.erase(bookings.begin() + i);
                break;
            }
        }

        cout << "Check-Out Successful! Room is now available.\n";
    }

    // ── show all bookings ────────────────
    void showAllBookings() {
        if (bookings.empty()) {
            cout << "No active bookings.\n";
            return;
        }
        cout << "\n===== Active Bookings =====" << endl;
        for (auto &booking : bookings)
            booking.showBooking();
    }

    // ── revenue report ───────────────────
    void showRevenue() {
        cout << "\n===== Revenue Report =====" << endl;
        cout << "Total Rooms      : " << totalRooms        << endl;
        cout << "Active Bookings  : " << bookings.size()   << endl;
        cout << "Total Revenue    : " << totalRevenue      << endl;
        cout << "===========================" << endl;
    }
};

// ─────────────────────────────────────────
//  MAIN MENU
// ─────────────────────────────────────────
int main() {
    HotelSystem hotel;
    hotel.setupRooms();

    int choice;
    do {
        cout << "\n===== Hotel Management System =====" << endl;
        cout << "1. Show All Rooms"       << endl;
        cout << "2. Show Available Rooms" << endl;
        cout << "3. Book a Room"          << endl;
        cout << "4. Check Out"            << endl;
        cout << "5. Show All Bookings"    << endl;
        cout << "6. Revenue Report"       << endl;
        cout << "0. Exit"                 << endl;
        cout << "Enter Choice : ";
        cin  >> choice;

        switch (choice) {
            case 1: hotel.showAllRooms();      break;
            case 2: hotel.showAvailableRooms(); break;
            case 3: hotel.bookRoom();           break;
            case 4: hotel.checkOut();           break;
            case 5: hotel.showAllBookings();    break;
            case 6: hotel.showRevenue();        break;
            case 0: cout << "Goodbye!\n";       break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
