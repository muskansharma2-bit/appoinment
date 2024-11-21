#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Function to read appointments from the file
map<char, string> readAppointments(const string& filename) {
    map<char, string> appointments;
    ifstream read(filename);

    if (read) {
        string line;
        while (getline(read, line)) {
            char slot = line[0];
            string name = line.substr(2);
            appointments[slot] = name;
        }
        read.close();
    }
    return appointments;
}

// Function to display available and booked slots
void displaySlots(const map<char, string>& appointments) {
    cout << "\n Appointment Summary by hours:\n";
    char key = 'A';
    int hours = 9;

    for (int i = 0; i < 13; i++) {
        if (appointments.find(key) == appointments.end())
            cout << " " << key << " -> " << (hours < 10 ? "0" : "") << hours << " - Available\n";
        else
            cout << " " << key << " -> " << (hours < 10 ? "0" : "") << hours << " - Booked (" << appointments.at(key) << ")\n";
        hours++;
        key++;
    }
}

// Function to book an appointment
void bookAppointment(const string& filename) {
    system("cls");
    cout << "\n ----- Book Your Appointment ---- \n";
    map<char, string> appointments = readAppointments(filename);
    displaySlots(appointments);

    char choice;
    cout << "\n\n Input your choice (A-M): ";
    cin >> choice;

    if (!(choice >= 'A' && choice <= 'M')) {
        cout << "\n Error: Invalid Selection. Please select a valid slot (A-M).\n";
        return;
    }

    if (appointments.find(choice) != appointments.end()) {
        cout << "\n Error: Appointment is already booked for this hour.\n";
        return;
    }

    string name;
    cout << "\n Enter your first name: ";
    cin >> name;

    ofstream out(filename, ios::app);
    if (out) {
        out << choice << ":" << name << "\n";
        out.close();
        cout << "\n Appointment booked for Hour: " << (choice - 'A') + 9 << " successfully!\n";
    } else {
        cout << "\n Error: Unable to save the booking.\n";
    }
}

// Function to view existing appointments
void existingAppointment(const string& filename) {
    system("cls");
    cout << "\n ----- Appointments Summary ---- \n";
    map<char, string> appointments = readAppointments(filename);
    displaySlots(appointments);
}

int main() {
    string filename = "appointment.dat";
    int choice;

    do {
        system("cls");
        cout << "\n ----- Appointment Booking System ---- \n";
        cout << " 1. Book an Appointment\n";
        cout << " 2. View Existing Appointments\n";
        cout << " 0. Exit\n";
        cout << " Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bookAppointment(filename);
                break;
            case 2:
                existingAppointment(filename);
                break;
            case 0:
                cout << "\n Exiting...\n";
                break;
            default:
                cout << "\n Invalid choice. Please try again.\n";
        }

        cout << "\n Press any key to continue...";
        cin.ignore();
        cin.get();

    } while (choice != 0);

    return 0;
}
