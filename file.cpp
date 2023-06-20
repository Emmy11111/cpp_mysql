#include <iostream>
#include <cstring>
#include <stdio.h>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

bool compareFunction (string a, string b) {return a<b;} 

vector<string> searchDisease(char fileName[200], string key){
	ifstream file;
	file.open(fileName);
	string line;
	vector<string> results;
	
	while(getline(file, line)){
		transform(line.begin(), line.end(), line.begin(), ::tolower);
		transform(key.begin(), key.end(), key.begin(), ::tolower);
		string location,cases,disease;
		
		stringstream ss(line);
		getline(ss,location, ',');
		getline(ss,disease, ',');
		getline(ss,cases, ',');
	
		if((disease.compare(key))==0){
			results.push_back(line);
		}
	}
	return results;
}

void printSummary(){
	ifstream file;
	file.open("records.txt");
	
	string line;
	
	cout<<endl<<endl;
	int space = 15;
	
	cout<<setw(23)<<right<<"Good  Bye !!"<<endl<<endl<<endl;
	
	cout<<setw(space)<<left<<"Loc"<<setw(space)<<left<<"Dis"<<setw(space)<<left<<"Cases"<<endl<<endl;
	cout<<setw(space)<<left<<"----"<<setw(space)<<left<<"-----"<<setw(space)<<left<<"----"<<endl<<endl;
	
	while(getline(file, line)){
		transform(line.begin(), line.end(), line.begin(), ::toupper);
		string location,cases,disease;
		
		stringstream ss(line);
		getline(ss,location, ',');
		getline(ss,disease, ',');
		getline(ss,cases, ',');
 		
		cout<<setw(space)<<left<<location<<setw(space) << left<<disease<<": "<<cases<<endl;
	}
	
	file.close();	
	cout<<endl<<endl<<"Ending Time: Fri Apr 06 00:13:12 CAT 2022"<<endl<<endl;
}

void record(){
		char location[100];
	char disease[100];
	char cases[20];
cout<<endl<<endl<<"Enter location: ";
	cin>>location;
	cout<<"Enter disease: ";
	cin>>disease;
	cout<<"Enter case: ";
	cin>>cases;
	
	FILE *file = fopen("location_disease_case", "a");
	
	if(file!=NULL){
		fprintf(file, location);
		fprintf(file,",");
		fprintf(file, disease);
		fprintf(file,",");
		fprintf(file,cases);
		fprintf(file,"\n");
		fclose(file);
	}
	
	cout<<endl<<endl<<"Data saved successfully"<<endl;
	cout<<"======================="<<endl<<endl;	
}

void helpMenu(){
	      cout <<endl<< "================================================================================"<<endl<<endl;
            cout << "*                            H E L P     M E N U                               *"<<endl;
            cout <<endl<< "================================================================================"<<endl<<endl;
            cout << "add <Location>                              :Add a new location"<<endl;
            cout << "delete <Location>                           :Delete an existing location"<<endl;
            cout << "record <Location> <disease> <cases>         :Record a disease and its cases"<<endl;
            cout << "list locations                              :List all existing locations"<<endl;
            cout << "list diseases                               :List existing diseases in locations"<<endl;
            cout << "where <disease>                             :Find where disease exists"<<endl;
            cout << "cases <Location> <disease>                  :Find cases of a disease in location"<<endl;
            cout << "cases <disease>                             :Find total cases of a given disease"<<endl;
            cout << "help                                        :Prints user manual"<<endl;
            cout << "Exit                                        :Exit the program"<<endl<<endl;
}

//check if location exists in locations file

bool checkLocation(char fileName[200], string data){
ifstream file;
string line;
file.open(fileName);
while(getline(file, line)){
	if(line.compare(data)==0){
		file.close();
		return true;
	}
}
file.close();
return false;
}

void listLocations(char fileName[200]){
	ifstream file;
	string line;
	file.open(fileName);
	vector<string> foundRecords;
	
	while(getline(file, line)){
		transform(line.begin(), line.end(), line.begin(), ::toupper);
		foundRecords.push_back(line);
	}
	
	sort(foundRecords.begin(),foundRecords.end(),compareFunction);
	
	for(int i=0; i<foundRecords.size(); i++){
		cout<<foundRecords.at(i)<<endl;
	}
    file.close();
}

//add new location
bool addData(char fileName[200], string data){
 ofstream file;
 file.open(fileName, ios::app);
 file<<data<<endl;
 file.close();
}

void getUserChoice(){
	
	char locationsFile[200] = "locations.txt";
	char recordsFile[200] = "records.txt";

	string command;
	getline(cin,command);
	
	while(command.compare("exit")!=0){
	transform(command.begin(), command.end(), command.begin(), ::tolower);
	vector<string> splittedCommands;
	string commandCpy = command;
	string delimeter = " ";
	
int pos = commandCpy.find(delimeter);

while(pos>=0){
	splittedCommands.push_back(commandCpy.substr(0,pos));
	commandCpy = commandCpy.substr(pos+1,commandCpy.length());
	pos = commandCpy.find(delimeter);
}

splittedCommands.push_back(commandCpy);

if(splittedCommands.at(0).compare("add")==0){
	string location = splittedCommands.at(1);
	string locationUp = location;
	bool exists = checkLocation(locationsFile,location);
	if(exists){
	cout<<"Location "<<locationUp<<" has been already added!"<<endl;
	}else{
	addData(locationsFile,location);
	transform(locationUp.begin(), locationUp.end(), locationUp.begin(), ::toupper);
	cout<<"Location "<<locationUp<<" is successfully added!"<<endl;
}
}else if((splittedCommands.at(0).compare("help"))==0 && splittedCommands.size()==1){
	helpMenu();
}else if((splittedCommands.at(0).compare("list"))==0 && (splittedCommands.at(1).compare("locations")==0)){
	listLocations(locationsFile);
}else if((splittedCommands.at(0).compare("record"))==0 ){
	if(splittedCommands.size() == 4){
		  if(checkLocation(locationsFile,splittedCommands.at(1)) == 0){
		  	cout<<"Location doesn't exists"<<endl;
		  }else{
		 string recordStr = splittedCommands.at(1)+","+splittedCommands.at(2)+","+splittedCommands.at(3);
		 addData(recordsFile,recordStr);
		 cout<<"Record is successfully added!"<<endl;
	}
}
    else{
    	if(splittedCommands.size() > 4){
    	cout<<"Command is too long"<<endl;
		}else{
		cout<<"Command is not complete"<<endl;
	}
}
}else if((splittedCommands.at(0).compare("where"))==0 && (splittedCommands.size()== 2)){
	vector<string> results = searchDisease(recordsFile,splittedCommands.at(1) );
	
	if(results.size()==0){
		cout<<"No location with this disease"<<endl;
	}else{
	cout<<"[";
	for(int i=0; i<results.size(); i++){
		string line = results.at(i);
		string location;
		stringstream ss(line);
		getline(ss,location, ',');
		cout<<location;
		if(i+1 != results.size()){
		cout<<",";	
		}
	}
	cout<<"]"<<endl;
}
}
else{
	cout<<"command doesn't exists'"<<endl;
}
getline(cin,command);
}
printSummary();
}

void welcome(){
	cout<<"============================================="<<endl<<endl;
	cout<<"*   Welcome to Disease Cases Reporting System!   *"<<endl<<endl;
	cout<<"*  ****************************************  *"<<endl<<endl;
	cout<<"*"<<endl<<endl;
	cout<<"* It is developed by student name as practical *"<<endl<<endl;
	cout<<"* evaluation for the end of year 1."<<endl<<endl;
	cout<<"==============================w==============="<<endl<<endl;
	cout<<"Starting Time: Thu Apr 05 23:59:08 CAT 2022"<<endl<<endl;
	cout<<"Need a help? Type 'help' then press Enter key."<<endl<<endl;
}

int main(){
	welcome();
	getUserChoice();
}
