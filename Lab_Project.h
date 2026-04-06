#ifndef LAB_PROJECT_H
#define LAB_PROJECT_H

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
using namespace std;


class Passenger{
    string name;
    string surname;
    char gender;
    //my add
    string seatCode;

    public:
        //constructors
        Passenger();
        Passenger(string n, string s, char g);
        //setters && getters
        void setName(string n);
        void setSurname(string s);
        void setGender(char g);
        string getName() const;
        string getSurname() const;
        char getGender() const;
        //my add's
        void setSeat(string s);
        string getSeat() const;
        //overload operators
        bool operator==(const Passenger& other) const;
};

class Flight{
    string flightNo;
    string destination;
    int maxSeats;
    int numPassengers;
    std::vector<Passenger> passengers;
    //my add
    char cols[4] = {'A', 'B', 'C', 'D'};

    public:
        void reserveSeat(const Passenger& passenger);
        void cancelReservation(const Passenger& passenger);
        int numberOfPassengers() const;
        void printPassengers();
        bool isFlyingTo(const string& destination);
        //my add's
        Flight();
        Flight(string fn, string d, int mSeats = 40);
        string getFlightNo() const;
        string getDestination() const;
        int availableSeats() const;
        void printSeatPlan();
        Flight& operator=(const Flight& other);
        bool operator==(const Flight& other)const;
};

class FlightManager{
    std::vector<Flight> flights;
    
    public:
        void addFlight(const Flight& flight);
        void removeFlight(const string& flightNumber);
        void listAllFlights();
        Flight getFlightByNumber(const string& flightNumber);
        Flight getFlightByDestination(const string& destination);
        //my add's
        void updateFlight(const Flight& updatedFlight);
};

#endif