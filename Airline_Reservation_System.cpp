#include<iostream>
#include<mysql.h>
#include<mysqld_error.h>
#include<windows.h>
#include<sstream>
using namespace std;

const char* HOST = "localhost";
const char* USER = "root";
const char* PW = "17122002";
const char* DB = "mydb";


class Flight {
	private:
		string Fnum, Dep, Des;
		int Seat;
	public:
		Flight(string Fnum, string Dep, string Des, int Seat){
			Fnum = fnum;
			Dep = dep;
			Des = des;
			Seat = seat;
		}
		
		string getFnum(){
			return Fnum;
		}
		
		string getDep(){
			return Dep;
		}
		
		string getDes(){
			return Des;
		}
		
		int getSeat(){
			return Seat;
		}
};


int main() {
	
	MYSQL* conn;
	conn = mysql_init(NULL);
	
	if(!mysql_real_connect(conn, HOST, USER, PW, DB, 3306, NULL, 0)){
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else{
		cout << "Loged In Database!" << endl;
	}
	Sleep(3000);
	
	Flight f1("Flight101", "UAE", "Canada", 50);
	Flight f2("Flight102", "UAE", "USA", 40);
	Flight f3("Flight103", "UAE", "India", 30);
	Flight f4("Flight104", "Delhi", "Kolkata", 60);
	Flight f5("Flight105", "Kolkata", "Bangalore", 70);
	Flight f6("Flight106", "Pune", "Guwahati", 35); 
	
	stringstream ss1, ss2, ss3, ss4, ss5, ss6;
	
	int intS1 = f1.getSeat();
	ss1 << intS1;
	string strS1 = ss1.str();
	
	int intS2 = f2.getSeat();
	ss2 << intS2;
	string strS2 = ss2.str();
	
	int intS3 = f3.getSeat();
	ss3 << intS3;
	string strS3 = ss3.str();
	
	int intS4 = f4.getSeat();
	ss4 << intS4;
	string strS4 = ss4.str();
	
	int intS5 = f5.getSeat();
	ss5 << intS5;
	string strS5 = ss5.str();
	
	int intS6 = f6.getSeat();
	ss6 << intS6;
	string strS6 = ss6.str();
	
	string insert1 = "INSERT INTO Airline (Fnumber, Departure, Destination, Seat) VALUES('"+f1.getFnum()+"', '"+f1.getDep()+"', '"+f1.getDes()+"', '"+strS1+"')";
	string insert2 = "INSERT INTO Airline (Fnumber, Departure, Destination, Seat) VALUES('"+f2.getFnum()+"', '"+f2.getDep()+"', '"+f2.getDes()+"', '"+strS2+"')";
	string insert3 = "INSERT INTO Airline (Fnumber, Departure, Destination, Seat) VALUES('"+f3.getFnum()+"', '"+f3.getDep()+"', '"+f3.getDes()+"', '"+strS3+"')";
	string insert4 = "INSERT INTO Airline (Fnumber, Departure, Destination, Seat) VALUES('"+f4.getFnum()+"', '"+f4.getDep()+"', '"+f4.getDes()+"', '"+strS4+"')";
	string insert5 = "INSERT INTO Airline (Fnumber, Departure, Destination, Seat) VALUES('"+f5.getFnum()+"', '"+f5.getDep()+"', '"+f5.getDes()+"', '"+strS5+"')";
	string insert6 = "INSERT INTO Airline (Fnumber, Departure, Destination, Seat) VALUES('"+f6.getFnum()+"', '"+f6.getDep()+"', '"+f6.getDes()+"', '"+strS6+"')";
	
	if(mysql_query(conn, insert1.c_str()) || mysql_query(conn, insert2.c_str()) || mysql_query(conn, insert3.c_str()) || mysql_query(conn, insert4.c_str()) || mysql_query(conn, insert5.c_str()) || mysql_query(conn, insert6.c_str())){
		cout << "Error: " << mysql_error(conn) << endl;
	}
	else{
		cout << "Inserted Successfully!" << endl;
	}
	Sleep(3000);
	
	bool exit = false;
	while(!exit){
		system("cls");
		cout << endl;
		
		cout << "Welcome to Airlene Reservation System" << endl;
		cout << "***********************************" << endl;
		cout << "1. Reserve a Seat In Flight" << endl;
		cout << "2. Exit" << endl;
		cout << "Enter your choice: ";
		int val;
		cin >> val;
		
		if(val == 1){
			string flight;
			cout << endl;
			cout << "Enter Flioght Number: ";
			cin >> flight;
			
			string checkSeat = "SELECT Seat FROM Airline WHERE = '"+flight+"'";
			if(mysql_query(conn, checkSeat.c_str())){
				cout << "Error: " << mysql_error(conn) << endl;
			}
			else{
				MYSQL_RES* res;
				res = mysql_store_result(conn);
				if(res){
					MYSQL_ROW row = mysql_fetch_row(res);
					total = atoi(row[0]);
				}
			}
			if(total > 0){
				total--;
				stringstream sst;
				sst << total;
				string strT = sst.str();
				
				string update = "UPDATE Airline SET Seat = '"+strT+"' WHERE = '"+flight+"'";
				if(mysql_query(conn, update.c_str())){
					cout << "Error: " << mysql_error(conn) << endl;
				}
				else{
					cout << "Your Seat is Reserved Successfully in " << flight << endl;
				}
				if(total == 0){
					cout << "Sorry! No Seat Available..." << endl;
				}
			}
		}
		
		else if(val == 2){
			exit = true;
			cout << "Good luck!" << endl;
			Sleep(3000);
		}
		
		else{
			cout << "Invalid Input..." << endl;
			Sleep(3000);
		}
	}
		
	return 0;
}
