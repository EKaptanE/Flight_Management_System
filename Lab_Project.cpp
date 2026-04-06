#include "202411049_Lab_Project.h"
//Passenger class
    Passenger:: Passenger(){
        name = " ";
        surname = " ";
        gender = ' ';
    }
    Passenger::Passenger(string n, string s, char g): name(n), surname(s), gender(g){}
    //setters && getters
    void Passenger::setName(string n){
        name = n;
    }
    void Passenger::setSurname(string s){
        surname = s;
    }
    void Passenger::setGender(char g){
        gender = g;
    }
    string Passenger::getName() const{
        return name;
    }
    string Passenger::getSurname() const{
        return surname;
    }
    char Passenger::getGender() const{
        return gender;
    }
    //my add's
    void Passenger::setSeat(string s){
        seatCode = s;
    }
    string Passenger::getSeat() const{
        return seatCode;
    }
    //overload operators
    bool Passenger::operator==(const Passenger& other) const{
        return(this->name == other.name && this->surname == other.surname && this->gender == other.gender);
    }
//Flight class
    void Flight::reserveSeat(const Passenger& passenger){
        if(numPassengers >= maxSeats){
            throw out_of_range("These Flight Fully Reserved!");
        }
        string selectedSeat;
        bool validInput = false;
        int totalRows = maxSeats / 4; 
        while(!validInput){
            printSeatPlan();
            cout << "Enter seat: ";
            cin >> selectedSeat;

            if(selectedSeat.length() < 2 || selectedSeat.length() > 3){
                cout << "Invalid Format! Use Row+Letter (e.g., 1A, 14C)!" << endl;
                continue;
            }
            char seatLetter = selectedSeat.back(); //letter check
            if(seatLetter < 'A' || seatLetter > 'D'){
                cout << "Invalid seat Letter! (Only uppercase A, B, C or D works.)" << endl;
                continue;
            }
            string rowPart = selectedSeat.substr(0, selectedSeat.length() - 1);
            int rowNum;
            try{
                rowNum = stoi(rowPart);
            }
            catch(...){
                cout << "Invalid row number! Please enter a valid number." << endl;
                continue;
            }
            if(rowNum < 1 || rowNum > totalRows){
                cout << "Row must be between 1 and " << totalRows << "!" << endl;
                continue;
            }
            string realCode = to_string(rowNum - 1) + seatLetter;
            for(int i = 0; i < passengers.size(); i++){
                if(passengers[i].getSeat() == realCode){
                    throw out_of_range("That seat already taken, start from menu!");
                }
            }
            Passenger newPassenger = passenger;
            newPassenger.setSeat(realCode);
            passengers.push_back(newPassenger);
            numPassengers++;
            validInput = true;
            }
    }
    void Flight::cancelReservation(const Passenger& passenger){
        for (int i = 0; i < passengers.size(); i++){
            if(passengers[i] == passenger){
                passengers.erase(passengers.begin() + i);
                numPassengers--;
                return ;
            }
        }
        throw out_of_range("Error: Passenger not found in this flight!");
    }
    int Flight::numberOfPassengers() const{
        return numPassengers;
    }
    void Flight::printPassengers(){
        cout << left << setw(5) << "Seat " << "|" << setw(15) << "Passenger Name " << "|" << setw(6) << "Gender" << endl;
        cout << "-----|---------------|------" << endl; 
        for(int i = 0; i < passengers.size(); i++){
            string realCode = passengers[i].getSeat(); //system interface

            char seatLetter = realCode.back();
            string rowPart = realCode.substr(0, realCode.length() - 1);

            int displayRow = stoi(rowPart) + 1; //getting output row (+1)

            string displaySeat = to_string(displayRow) + seatLetter; //user interface
            string fullName = passengers[i].getName() + " " + passengers[i].getSurname();
            if(fullName.length() >= 15){
                fullName = fullName.substr(0, 13) + ".";
            }
        cout << left << setw(5) << displaySeat << "|" << setw(15) << fullName << "|" << passengers[i].getGender() << endl;
        }
        cout << "\nThere are " << numberOfPassengers() << " passengers on that flight." << endl;
    }

    bool Flight::isFlyingTo(const string& destination){ //I dont use it but still I write that.
        return this->destination == destination;
    }
    //my add's
    Flight::Flight(){
        flightNo = "";
        destination = "";
        maxSeats = 40;
        numPassengers = 0;
    }
    Flight::Flight(string fn, string d, int mSeats): flightNo(fn), destination(d){
        numPassengers = 0;
        if(mSeats % 2 == 0 && mSeats <=80){
            maxSeats =mSeats;
        }
        else{
            maxSeats = 40;
        }
    }
    string Flight::getFlightNo() const{
        return flightNo;
    }
    string Flight::getDestination() const{
        return destination;
    }
    int Flight::availableSeats() const{
        if(maxSeats < numPassengers){
            return 0;
        }
        return maxSeats - numPassengers;
    }
    void Flight::printSeatPlan(){
        cout << "Legend:\nX- Occupied Seat\nO- Vacant Seat\n" << endl;
        cout << "Seating Plan:\n---------------Front---------------\n";
        int totalRows = maxSeats / 4;
        for (int i = 0; i < totalRows; i++){
            cout << "| ";
            for(int k = 0; k < 4; k++){
                int displayRow = i + 1;
                string currentCode = to_string(i) + cols[k];
                bool occupied = false;
                for(int j = 0; j < passengers.size(); j++){
                    if(passengers[j].getSeat() == currentCode){
                        occupied = true;
                        break;
                    }
                }
                if(displayRow < 10){
                    cout << " ";
                }
                cout << displayRow << cols[k] << (occupied ? " X " : " O ") << "| ";
                if(k == 1) cout << "|";
            }
            cout << endl;
        }
        cout << "\nThere are " << numberOfPassengers() << " Passengers on that flight." << endl;
    }
    Flight& Flight::operator=(const Flight& other){
        if(this!= &other){
        this->flightNo = other.flightNo;
        this->destination = other.destination;
        this->maxSeats = other.maxSeats;
        this->numPassengers = other.numPassengers;
        this->passengers = other.passengers;
        }
        return *this;
    }
    bool Flight::operator==(const Flight& other)const{
        return this->flightNo == other.flightNo;
    }

//FlightManager class
    void FlightManager::addFlight(const Flight& flight){
        for(int i = 0; i < flights.size(); i++){
            if(flights[i] == flight){
                throw out_of_range("These flight number already declared!");
            }
        }
        flights.push_back(flight);
    }
    void FlightManager::removeFlight(const string& flightNumber){
        for(int i = 0; i < flights.size(); i++){
            if(flights[i].getFlightNo() == flightNumber){
                flights.erase(flights.begin() + i);
                return;
            }
        }
        throw out_of_range("No Flight Number matching for remove!");
    }
    void FlightManager::listAllFlights(){
        for(int i = 0; i < flights.size(); i++){
            cout << "\nFlight Number: " << flights[i].getFlightNo() << endl;
            cout << "Destination: " << flights[i].getDestination() << endl;
            cout << "Number of available seats: " << flights[i].availableSeats() << endl;
        }
    }
    Flight FlightManager::getFlightByNumber(const string& flightNumber){
        for(int i = 0; i < flights.size(); i++){
            if(flights[i].getFlightNo() == flightNumber){
                return flights[i];
            }
        }
        throw out_of_range("No matching Flight Number, try again from beginning.");
    }
    Flight FlightManager::getFlightByDestination(const string& destination){ //I dont use it but still I write that
        for(int i = 0; i < flights.size(); i++){
            if(flights[i].getDestination() == destination){
                return flights[i];
            }
        }
        throw out_of_range("No matching Destination, try agai nfrom beginning.");
    }
    //add's
    void FlightManager::updateFlight(const Flight& updatedFlight){
        for(int i = 0; i < flights.size(); i++){
            if(flights[i].getFlightNo() == updatedFlight.getFlightNo()){
                flights[i] = updatedFlight;
                return;    
            }
        }
    }

int main(){
    int tl = 6, sl, capacity;
    string fly, dest, name, surname;
    char gender;
    FlightManager User;
    
    while(tl != 5){
        cout << "Top-Level Menu: Flight Management\n1. Add a Flight\n2. Remove a flight\n3. List All Flights\n4. Select a Flight and Manage Passengers\n5. Exit\nChoose your operation: ";
        cin >> tl;
        switch(tl){
            case 1:{
                try{
                    cout << "Adding Flights:\nEnter Flight Number: ";
                    cin >> fly;
                    if (fly.length() < 3 || fly.length() > 6 || (fly.substr(0, 2) != "TK" && fly.substr(0, 2) != "PG")) {
                        cout << "Invalid flight number! Must start with TK or PG and have 1-4 digits." << endl;
                        cin.clear();
                        cin.ignore(1000, '\n');
                        break;
                    }
                    cout << "Enter Destination: " ;
                    cin.ignore();
                    getline(cin, dest);

                    cout << "Enter Maximum Seats (Even number, max 80, default 40): ";
                    cin >> capacity;
                    if(cin.fail()){
                        cout << "Wrong Input, It must be Number. Capacity automatically set to 40.\n";
                        cin.clear();
                        cin.ignore(1000, '\n');
                        capacity = 40;
                    }
                    else if(capacity%2 != 0 || capacity > 80 || capacity <= 0){
                        cout << "Wrong Input (Odd or out of range), capacity set to 40.\n";
                        capacity = 40;
                    }
                    User.addFlight(Flight(fly, dest, capacity));
                    cout << "Flight successfully added.\n";
                    cin.clear();
                    break;
                }
                catch (const out_of_range& err){
                    cout << "Error: " << err.what() << endl;
                    break;
                }
            }
            case 2:{
                try{
                    cout << "Removing Flights:\nEnter Flight Number: ";
                    cin >> fly;
                    User.removeFlight(fly);
                    cout << "Flight succesfully removed.\n";
                    break;
                }
                catch (const out_of_range& err){
                    cout << "Error: " << err.what() << endl;
                    break;
                } 
            }
            case 3:{
                User.listAllFlights();
                cout << endl;
                break;
            }
            case 4:{
                sl = 0;
                Flight temp;
                try{
                    cout << "Enter Flight Number: ";
                    cin >> fly;
                    temp = User.getFlightByNumber(fly);
                }
                catch (const out_of_range& err){
                    cout << "Error: " << err.what() << endl;
                    break;
                }
                while(sl != 4){
                    cout << "Second-Level Menu: Passenger Management (For a selected Flight)\n1. Reserve a Seat(by displaying seating plan)\n2. Cancel a Reservation\n3. View Passenger List\n4. Back to Flight Management Menu\nChoose your operation: "; 
                    cin >> sl;
                    switch(sl){
                        case 1:{
                            Passenger reserve;
                            cout << "Enter passengers informations in order for reserve a seat (Name->Surname->Gender): ";
                            cin >> name >> surname >> gender;
                            //I make the passenger object with default constructor here because I want to use setters for one time. When case 2, I dont use it because I create the object with parameterized constructor.
                            reserve.setName(name);
                            reserve.setSurname(surname);
                            reserve.setGender(gender);
                            try{
                                temp.reserveSeat(reserve);
                                User.updateFlight(temp);
                                cout << "Seat succcessfully reserved." << endl;
                                break;
                            }
                            catch (const out_of_range& err){
                                cout << "Error: " << err.what() << endl;
                                break;
                            }                               
                        }
                        case 2:{
                            try{
                                cout << "Enter passengers informations in order for cancel a reservation (Name->Surname->Gender): ";
                                cin >> name >> surname >> gender;
                                Passenger deleted(name, surname, gender);
                                temp.cancelReservation(deleted);
                                User.updateFlight(temp);
                                cout << "Seat successfully removed." << endl;
                                break;
                            }
                            catch (const out_of_range& err){
                                cout << "Error: " << err.what() << endl;
                                break;
                            }
                        }
                        case 3:{
                            cout << "Passenger List for Flight " << temp.getFlightNo() << ":\n";
                            temp.printPassengers();
                            cout << endl;
                            break;    
                        }
                        case 4:{
                            break;
                        }
                        default:{
                            cout << "Wrong Input, try again!\n";
                            break;
                        }
                    }   
                }
                break;
            }
            case 5:{
                cout << "Thanks for using our system, goodbye!\n";
                break;
            }
            default:{
                cout << "Wrong Input, try again.\n";
                break;
            }
        }
    }
    return 0;
}