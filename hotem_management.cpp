#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Room {
    int roomNumber;
    bool isBooked;
    string guestName;
    double pricePerNight;

    Room(int num = 0, double price = 0.0) {
        roomNumber = num;
        pricePerNight = price;
        isBooked = false;
        guestName = "";
    }
};

class Hotel {
private:
    vector<Room> rooms;
    double totalMoney;

public:
    Hotel(int roomCount) {
        totalMoney = 0.0;

        // Create rooms
        for (int i = 1; i <= roomCount; i++) {
            rooms.push_back(Room(i, 1000.0)); // each room price = 1000
        }
    }

    void showAvailableRooms() {
        cout << "\nAvailable Rooms:\n";
        for (int i = 0; i < rooms.size(); i++) {
            if (!rooms[i].isBooked) {
                cout << "Room " << rooms[i].roomNumber
                     << " | Price: " << rooms[i].pricePerNight << endl;
            }
        }
    }

    void showBookedRooms() {
        cout << "\nBooked Rooms:\n";
        for (int i = 0; i < rooms.size(); i++) {
            if (rooms[i].isBooked) {
                cout << "Room " << rooms[i].roomNumber
                     << " | Guest: " << rooms[i].guestName << endl;
            }
        }
    }

    void bookRoom(int roomNumber, string guestName) {
        if (roomNumber < 1 || roomNumber > rooms.size()) {
            cout << "Invalid room number!\n";
            return;
        }

        Room &room = rooms[roomNumber - 1];

        if (room.isBooked) {
            cout << "Room already booked!\n";
        } else {
            room.isBooked = true;
            room.guestName = guestName;
            cout << "Room " << roomNumber << " booked successfully for " 
                 << guestName << "!\n";
        }
    }

    void checkoutRoom(int roomNumber, int nights) {
        if (roomNumber < 1 || roomNumber > rooms.size()) {
            cout << "Invalid room number!\n";
            return;
        }

        Room &room = rooms[roomNumber - 1];

        if (!room.isBooked) {
            cout << "Room is not booked!\n";
        } else {
            double bill = room.pricePerNight * nights;
            totalMoney += bill;

            cout << "Guest " << room.guestName << " checked out.\n";
            cout << "Bill: " << bill << endl;

            room.isBooked = false;
            room.guestName = "";
        }
    }

    void showHotelStatus() {
        int booked = 0;
        for (int i = 0; i < rooms.size(); i++) {
            if (rooms[i].isBooked) booked++;
        }

        cout << "\nHotel Status:\n";
        cout << "Total Rooms: " << rooms.size() << endl;
        cout << "Booked Rooms: " << booked << endl;
        cout << "Available Rooms: " << rooms.size() - booked << endl;
        cout << "Total Money Earned: " << totalMoney << endl;
    }
};

int main() {
    int roomCount;
    cout << "Enter total number of rooms in hotel: ";
    cin >> roomCount;

    Hotel hotel(roomCount);

    int choice;
    do {
        cout << "\n===== HOTEL MANAGEMENT SYSTEM =====\n";
        cout << "1. Show Available Rooms\n";
        cout << "2. Show Booked Rooms\n";
        cout << "3. Book Room\n";
        cout << "4. Checkout Room\n";
        cout << "5. Hotel Status\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            hotel.showAvailableRooms();
        } else if (choice == 2) {
            hotel.showBookedRooms();
        } else if (choice == 3) {
            int roomNo;
            string name;
            cout << "Enter room number: ";
            cin >> roomNo;
            cout << "Enter guest name: ";
            cin.ignore();
            getline(cin, name);
            hotel.bookRoom(roomNo, name);
        } else if (choice == 4) {
            int roomNo, nights;
            cout << "Enter room number: ";
            cin >> roomNo;
            cout << "Enter number of nights: ";
            cin >> nights;
            hotel.checkoutRoom(roomNo, nights);
        } else if (choice == 5) {
            hotel.showHotelStatus();
        } else if (choice == 6) {
            cout << "Exiting system...\n";
        } else {
            cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}
