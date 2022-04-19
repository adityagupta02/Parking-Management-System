// Author: Aditya Bal Gupta

#include <iostream>
#include <vector>

using namespace std;

typedef struct Date {
    int day;
    int month;
    int year;
} Date;

typedef struct Time {
    int hour;
    int minute;
    int second;
} Time;


class vehicle {
    string reg_number;
    int type;
    Date dt;
    Time arrival;
    Time departure;
public:
    void add_vehicle();
    void vehicle_departure();
    void disp_vehicles();
};

vector<vehicle> veh(1000);
int static vehicle_count = 0, car_count = 0, bike_count = 0, money_collected = 0, i = 0;

void vehicle::add_vehicle() {
    vehicle *v = new vehicle;
    char c1, c2;
    cout << "Enter type of vehicle (1 for Car, 2 for Bike) : ";
    cin >> v->type;
    cout << "Enter vehicle registration number : ";
    cin >> v->reg_number;
    cout << "Enter arrival time (HH.MM.SS) : ";
    cin >> v->arrival.hour >> c1 >> v->arrival.minute >> c2 >> v->arrival.second;
    cout << "Enter Date (DD/MM/YYYY): ";
    cin >> v->dt.day >> c1 >> v->dt.month >> c2 >> v->dt.year;

    veh.at(i).reg_number = v->reg_number;
    veh.at(i).type = v->type;
    veh.at(i).arrival.hour = v->arrival.hour;
    veh.at(i).arrival.minute = v->arrival.minute;
    veh.at(i).arrival.second = v->arrival.second;
    veh.at(i).dt.day = v->dt.day;
    veh.at(i).dt.month = v->dt.month;
    veh.at(i).dt.year = v->dt.year;

    i++;
    vehicle_count++;

    if (v->type == 1)
        car_count++;
    else
        bike_count++;

    cout << "\nVehicle added" << endl;
}

int TimeDifference(Time arr, Time dep){
    int arr_sec, dep_sec, diff_sec;        
    arr_sec = arr.hour * 3600 + arr.minute * 60 + arr.second;
    dep_sec = dep.hour * 3600 + dep.minute * 60 + dep.second;
    diff_sec = dep_sec - arr_sec;
    return (diff_sec /60)/60;
}

void vehicle:: vehicle_departure() {
    string reg_num;
    int typ;
    Time depart;
    int Time_diff;
    int charge = 0;
    char c1,c2;

    cout << "Enter vehicle type(1 for Car/2 for Bike) : ";
    cin >> typ;
    cout << "Enter vehicle number : ";
    cin >> reg_num;
    cout << "Enter departure Time (HH.MM.SS) : ";
    cin >> depart.hour >> c1 >> depart.minute >> c2 >> depart.second;


    for (int j = 0; j <= i; j++){
        if ((veh.at(j).reg_number == reg_num) && (veh.at(j).type == typ)){
            veh.at(j).departure.hour = depart.hour;
            veh.at(j).departure.minute = depart.minute;
            veh.at(j).departure.second = depart.second;

            Time_diff = TimeDifference(veh.at(j).arrival, depart);

            if (veh.at(j).type == 1){
                car_count--;
                if (Time_diff < 2)
                    charge = 30;
                else{
                    if ((Time_diff > 2) && ((Time_diff < 5)))  
                        charge = 40;
                    else
                        charge = 60;
                }
            }
            else{
                bike_count--;

                if ( Time_diff < 2)
                    charge = 10;
                else{
                    if ((Time_diff > 2) && ((Time_diff < 5)))
                        charge = 15;
                    else
                        charge = 20;
                }

            }

            cout << "\nVehicle having vehicle number  : " << veh.at(j).reg_number << " has left the parking after paying Rs. " << charge << endl;
            
            veh.erase(veh.begin() + j);
            i--;
            vehicle_count--;
            money_collected = money_collected + charge;
            break;
        }

        if (j == i){
            cout << "\nWrong Entry , Try Again " << endl << endl;
            cout << "Departure : " << endl;
            vehicle_departure();
        }
    }
}

void vehicle::disp_vehicles(){
    cout << "Vehicle Type\t\tVehicle Reg. Number\t\t\tArrival Date\t\t\tArrival Time" << endl;
    for (int j = 0; j < i; j++){
        cout << veh[j].type << "\t\t\t" << veh[j].reg_number << "\t\t\t\t" << veh[j].dt.day << "/" << veh[j].dt.month << "/" << veh[j].dt.year << "\t\t\t" << veh[j].arrival.hour << ":" << veh[j].arrival.minute << ":" << veh[j].arrival.second << endl;
    }
}

void disp_tot_veh(){
    cout << "Number of vehicles parked currently : " << vehicle_count << endl;
    cout << "Number of cars parked currently : " << car_count << endl;
    cout << "Number of bikes parked currently : " <<  bike_count << endl;
}

void disp_tot_amount(){
    cout << "Total amount of money collected : " << money_collected << endl;
}

int main() {
    int choice;
    char ans;
    system ( "cls" ) ;

    do{
        system ( "cls" ) ;
        cout << "________________________________________________________" << endl;
        cout << "                 VEHICLE PARKING SYSTEM                 " << endl;
        cout << "Available choices: "<<endl;
        cout << "1. To add a new vehicle" << endl
             << "2. To get total number of vehicles parked" << endl
             << "3. For departure of vehicle" << endl
             << "4. To get total amount of money collected " << endl
             << "5. Display vehicles parked currently " << endl
             << "6. Exit" << endl
             << "________________________________________________________" << endl
             << "Enter your choice: ";
        cin >> choice;

        if(choice==1){
            system ( "cls" );
            cout << "Add new behicle: " << endl;
            veh.at(i).add_vehicle();
        }

        else if(choice == 2){
            system ( "cls" );
            disp_tot_veh();
        }

        else if(choice == 3){
            system ( "cls" );
            cout << "Departure of vehicle: " << endl;
            veh.at(i).vehicle_departure();
        }

        else if(choice == 4){
            system ( "cls" );
            disp_tot_amount(); 
        }       

        else if(choice == 5){
            system ( "cls" );
            veh.at(i).disp_vehicles();
        }

        else if(choice == 6) 
            exit(0);
        

        cout << "\nPress Y to continue, N to exit: " << endl;
        cin >> ans;
        if (ans == 'N' || ans == 'n'){
            system ( "cls" );
            break;
        }
        else
            continue;

    }while (1);

    return 0;
}

