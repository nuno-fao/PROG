#include "TypeStruDef.h"
#include "Allfuncs.h"
#include <iostream>
#include <locale>
#include <cstddef>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

//func to clear input buffer when needed
void clearInput(void) {
	cin.clear();
	cin.ignore(1000, '\n');
}

//func to show initial menu, deal with potential invalid inputs and return what the user wants to do

opChoose mainmenu(void) {
	opChoose op;
	bool invalidinp;
	cout << endl;
	do {
		invalidinp = false;
		cout << "Input..." << endl;
		cout << "[1] - To manage clients." << endl << "[2] - To manage packs." << endl << "[3] - To view the info about clients or packs." << endl << "[4] - To view the total sales." << endl;
		cout << "[CTRL+Z] - To end execution and save all changes (if any)." << endl;
		cout << "What would you like to do? ";
		cin >> op;
		if (cin.eof()) {
			return 0;
		}
		else if (cin.fail() || op < 1 || op>4) {
			clearInput();
			invalidinp = true;
		}
	} while (invalidinp);
	return op;
}

//func to read all clients data to a vector and return it
vector<Client> readClients(void) {
	vector<Client> out;
	Client aux;
	string auxstr;
	size_t startPos, endPos;
	ifstream in_stream;
	in_stream.open("clients.txt");
	while (!in_stream.eof()) {
		startPos = endPos = 0;
		aux.adress.clear();
		aux.packsbought.clear();
		getline(in_stream, aux.name);
		getline(in_stream, aux.nif);
		getline(in_stream, aux.famsize);
		getline(in_stream, auxstr);
		while (endPos < auxstr.length()) {
			endPos = auxstr.find(" / ", startPos);
			if (endPos == string::npos) {
				aux.adress.push_back(auxstr.substr(startPos));
				break;
			}
			else {
				aux.adress.push_back(auxstr.substr(startPos, endPos - startPos));
				startPos = endPos + 3;
			}
		}
		getline(in_stream, auxstr);
		startPos = endPos = 0;
		while (endPos < auxstr.length()) {
			endPos = auxstr.find(" ; ", startPos);
			if (endPos == string::npos) {
				aux.packsbought.push_back(auxstr.substr(startPos));
				break;
			}
			else {
				aux.packsbought.push_back(auxstr.substr(startPos, endPos - startPos));
				startPos = endPos + 3;
			}
		}
		getline(in_stream, auxstr);			//jump the :::::::::: line
		out.push_back(aux);
	}
	in_stream.close();
	return out;
}

//func to read all info about TravelPacks, store it in a vector and return it

vector<TravelPack> readPacks(void) {
	vector<TravelPack> out;
	TravelPack aux;
	string auxstr;
	size_t startPos, endPos;
	ifstream in_stream;
	in_stream.open("packs.txt");
	getline(in_stream, auxstr);			//jump the first line that contains the id of the last created pack
	while (!in_stream.eof()) {
		startPos = endPos = 0;
		aux.places.clear();
		aux.beg.clear();
		aux.end.clear();
		getline(in_stream, aux.id);
		getline(in_stream, auxstr);
		endPos = auxstr.find(" - ", startPos);
		aux.places.push_back(auxstr.substr(startPos, endPos - startPos));
		startPos = endPos + 3;
		while (endPos < auxstr.length()) {
			endPos = auxstr.find(", ", startPos);
			if (endPos == string::npos) {
				aux.places.push_back(auxstr.substr(startPos));
				break;
			}
			else {
				aux.places.push_back(auxstr.substr(startPos, endPos - startPos));
				startPos = endPos + 2;
			}
		}
		getline(in_stream, auxstr);
		startPos = endPos = 0;
		while (endPos < auxstr.length()) {
			endPos = auxstr.find("/", startPos);
			if (endPos == string::npos) {
				aux.beg.push_back(auxstr.substr(startPos));
				break;
			}
			else {
				aux.beg.push_back(auxstr.substr(startPos, endPos - startPos));
				startPos = endPos + 1;
			}
		}
		getline(in_stream, auxstr);
		startPos = endPos = 0;
		while (endPos < auxstr.length()) {
			endPos = auxstr.find("/", startPos);
			if (endPos == string::npos) {
				aux.end.push_back(auxstr.substr(startPos));
				break;
			}
			else {
				aux.end.push_back(auxstr.substr(startPos, endPos - startPos));
				startPos = endPos + 1;
			}
		}
		getline(in_stream, aux.price);
		getline(in_stream, aux.maxpeeps);
		getline(in_stream, aux.sold);
		getline(in_stream, auxstr);			//jump the :::::::::: line
		out.push_back(aux);
	}
	in_stream.close();
	return out;
}

//func to write back the packlist to packs.txt 

void writePacks(vector<TravelPack> packlist) {
	ofstream out_stream;
	string separator = "::::::::::", lastPackID = packlist.back().id;
	out_stream.open("packs.txt", ios::trunc);			//clear the existing content to exchange with the new one
	out_stream << lastPackID << endl;
	for (incri i = 0; i < packlist.size(); i++) {
		out_stream << packlist[i].id << endl;
		if (packlist[i].places.size() > 1) {
			out_stream << packlist[i].places[0] << " - ";
			for (incri i2 = 1; i2 < packlist[i].places.size(); i2++) {
				out_stream << packlist[i].places[i2];
				if (i2 == packlist[i].places.size() - 1) {
					out_stream << endl;
				}
				else {
					out_stream << ", ";
				}
			}
		}
		else {
			out_stream << packlist[i].places[0] << endl;
		}
		for (incri i2 = 0; i2 < 3; i2++) {
			out_stream << packlist[i].beg[i2];
			if (i2 == packlist[i].beg.size() - 1) {
				out_stream << endl;
			}
			else {
				out_stream << "/";
			}
		}
		for (incri i2 = 0; i2 < 3; i2++) {
			out_stream << packlist[i].end[i2];
			if (i2 == packlist[i].end.size() - 1) {
				out_stream << endl;
			}
			else {
				out_stream << "/";
			}
		}
		out_stream << packlist[i].price << endl << packlist[i].maxpeeps << endl << packlist[i].sold;
		if (i != packlist.size() - 1) {
			out_stream << endl << separator << endl;
		}
	}
	out_stream.close();
}

//func to write back the clientlist to clients.txt

void writeClients(vector<Client> clientlist) {
	ofstream out_stream;
	string separator = "::::::::::";
	out_stream.open("clients.txt", ios::trunc);			//clear the existing content to exchange with the new one
	for (incri i = 0; i < clientlist.size(); i++) {
		out_stream << clientlist[i].name << endl << clientlist[i].nif << endl << clientlist[i].famsize << endl;
		for (incri i2 = 0; i2 < 5; i2++) {
			out_stream << clientlist[i].adress[i2];
			if (i2 == 4) {
				out_stream << endl;
			}
			else {
				out_stream << " / ";
			}
		}
		for (incri i2 = 0; i2 < clientlist[i].packsbought.size(); i2++) {
			out_stream << clientlist[i].packsbought[i2];
			if (i2 != clientlist[i].packsbought.size() - 1) {
				out_stream << " ; ";
			}
		}
		if (i != clientlist.size() - 1) {
			out_stream << endl << separator << endl;
		}
	}
	out_stream.close();
}


//func to remove a pack from the list

void removePack(vector<TravelPack> &packlist) {
	string packID, negID, confirmstr;
	bool cont = true, confirm;
	do {
		negID = "-";
		cout << endl << "So what is the id of the pack you wish to remove (0 to turn back)? ";
		cin >> packID;
		negID += packID;
		if (packID == "0") {
			cont = false;
		}
		else {
			for (incri i = 0; i < packlist.size(); i++) {
				if (packID == packlist[i].id || negID==packlist[i].id) {	//look for the pack
					cout << endl << "Pack found." << endl;
					printpackinfo(packlist[i]);
					do {
						cout << "Are you sure you want to remove this pack from the agency database (you will not be able to get it back)?" << endl;
						cout << "Y/N: ";
						cin >> confirmstr;
					} while (confirmstr != "Y" && confirmstr != "N" && confirmstr != "y" && confirmstr != "n");	//confirm or cancel
					(confirmstr == "Y" || confirmstr == "y") ? confirm = true : confirm = false;
					if (confirm) {
						packlist.erase(packlist.begin() + i);
						cout << endl << "Pack was successfully removed." << endl;
						cont = false;
						break;
					}
				}
			}
			if (cont && confirm) {
				cout << endl << "There is no such pack with that ID." << endl;
			}
		}
	} while (cont);
}

//func to remove a client from the list

void removeClient(vector<Client> &clientlist) {
	string clientnif, confirmstr;
	bool cont = true, confirm;
	do {
		cout << endl << "So what is the id of the client you wish to remove (0 to turn back)? ";
		cin >> clientnif;
		if (clientnif == "0") {
			cont = false;
		}
		else if (clientnif.length() != 9) {
			cout << endl << "Invalid NIF. It has to cointain exactly 9 numbers." << endl;
		}
		else {
			for (incri i = 0; i < clientlist.size(); i++) {
				if (clientnif == clientlist[i].nif) {			//look for the client
					cout << endl << "Client found." << endl;
					printclientinfo(clientlist[i]);
					do {
						cout << "Are you sure you want to remove this client from the agency database (you will not be able to get it back)?" << endl;
						cout << "Y/N: ";
						cin >> confirmstr;
					} while (confirmstr != "Y" && confirmstr != "N" && confirmstr != "y" && confirmstr != "n");		//confirm or cancel
					(confirmstr == "Y" || confirmstr == "y") ? confirm = true : confirm = false;
					if (confirm) {
						clientlist.erase(clientlist.begin() + i);
						cout << endl << "Client was successfully removed." << endl;
						cont = false;
						break;
					}
				}
			}
			if (cont && confirm) {
				cout << endl << "An error occured, either than person is not a client or the NIF: "<<clientnif<<" contains invalid characters." << endl;
			}
		}
	} while (cont);
}


void addClient(vector<Client> &clientlist, vector<TravelPack> packlist) {
	Client aux;
	string auxstr;
	bool invalidnif, cancel;

	cout << "You will now enter the client's information." << endl << "Name: ";
	cin >> aux.name;
	do {
		invalidnif = cancel = false;
		cout << endl << "NIF (CTRL+Z to cancel the op): ";
		cin >> aux.nif;
		if (!cin.eof()) {
			if (aux.nif.length() != 9) {
				cout << endl << "Wrong nif length, please try again.";
				invalidnif = true;
			}
			else {
				for (unsigned int i = 0; i < aux.nif.size(); i++) {
					if (!isdigit(aux.nif[i])) {
						cout << endl << "Client nif contains characters that aren't numbers.";
						invalidnif = true;
						break;
					}
				}
				if (!invalidnif) {
					for (incri i = 0; i < clientlist.size(); i++) {
						if (clientlist[i].nif == aux.nif) {
							cout << endl << "A client with that NIF already exists. Please try again.";
							invalidnif = true;
							break;
						}
					}
				}
			}
		}
		else {
			cancel = true;
		}
	} while (invalidnif);
	if (cancel) {
		cin.clear();
		return;
	}
	clearInput();
	cout << endl << "Household size: ";
	getline(cin, aux.famsize);
	cout << endl << "Adress' street: ";
	getline(cin, auxstr);
	aux.adress.push_back(auxstr);
	cout << endl << "Adress' door number: ";
	cin >> auxstr;
	aux.adress.push_back(auxstr);
	cout << endl << "Adress' floor (do not separate floor from orientation; '-' if non-existent): ";
	cin >> auxstr;
	aux.adress.push_back(auxstr);
	cout << endl << "Adress' postal code: ";
	cin >> auxstr;
	aux.adress.push_back(auxstr);
	clearInput();
	cout << endl << "Adress' locality: ";
	getline(cin, auxstr);
	aux.adress.push_back(auxstr);
	aux.packsbought.push_back("");
	clientlist.push_back(aux);
	cout << endl << "The client was registed successfully." << endl;
}

void addPack(vector<TravelPack> &packlist) {		//get all the info needed it will not change what has an empty input
	TravelPack aux;
	string auxstr, confirmstr;
	size_t endPos, startPos;
	bool redo, confirm;
	aux.sold = "0";
	do {
		redo = false;
		startPos = endPos = 0;
		cout << "Insert the pack's ID (it must be a positive integer): ";
		cin >> aux.id;
		cout << endl << "Main destiny followed by turing sugestions, if any (IN THIS FORMAT: Main - Sugestion, Sugestion, etc): " << endl;
		cin >> auxstr;
		endPos = auxstr.find(" - ", startPos);
		aux.places.push_back(auxstr.substr(startPos, endPos - startPos));
		startPos = endPos + 3;
		while (endPos < auxstr.length()) {
			endPos = auxstr.find(", ", startPos);
			if (endPos == string::npos) {
				aux.places.push_back(auxstr.substr(startPos));
				break;
			}
			else {
				aux.places.push_back(auxstr.substr(startPos, endPos - startPos));
				startPos = endPos + 2;
			}
		}
		cout << "In the format YYYY/MM/DD what is the starting date: ";
		cin >> auxstr;
		startPos = endPos = 0;
		while (endPos < auxstr.length()) {
			endPos = auxstr.find("/", startPos);
			if (endPos == string::npos) {
				aux.beg.push_back(auxstr.substr(startPos));
				break;
			}
			else {
				aux.beg.push_back(auxstr.substr(startPos, endPos - startPos));
				startPos = endPos + 1;
			}
		}
		cout << endl << "In the format YYYY/MM/DD what is the ending date: ";
		cin >> auxstr;
		startPos = endPos = 0;
		while (endPos < auxstr.length()) {
			endPos = auxstr.find("/", startPos);
			if (endPos == string::npos) {
				aux.end.push_back(auxstr.substr(startPos));
				break;
			}
			else {
				aux.end.push_back(auxstr.substr(startPos, endPos - startPos));
				startPos = endPos + 1;
			}
		}
		cout << endl << "What is the price per person in euros: ";
		cin >> aux.price;
		cout << endl << "How many seats are initially available: ";
		cin >> aux.maxpeeps;
		cout << endl << "This is the pack you will register." << endl;
		printpackinfo(aux);
		do {
			cout << "Do you want to add this pack the pack like this?" << endl;
			cout << "Y/N: ";
			cin >> confirmstr;
		} while (confirmstr != "Y" && confirmstr != "N" && confirmstr != "y" && confirmstr != "n");	//confirmation
		(confirmstr == "Y" || confirmstr == "y") ? confirm = true : confirm = false;
		if (!confirm) {
			do {
				cout << "So you want to do redo the specifications?" << endl;
				cout << "Y/N: ";
				cin >> confirmstr;
			} while (confirmstr != "Y" && confirmstr != "N" && confirmstr != "y" && confirmstr != "n");		//redo or cancel
			(confirmstr == "Y" || confirmstr == "y") ? redo = true : redo = false;
		}
	} while (redo);
	if (confirm) {
		packlist.push_back(aux);
		cout << "The pack has been added successfully." << endl;
	}
}

void printclientinfo(Client client) {	//print client info vertically, easier to read for smaller sized client lists
	cout << "Name: " << client.name << endl;
	cout << "NIF: " << client.nif << endl;
	cout << "Household: " << client.famsize << endl;
	cout << "Adress: " << client.adress[0] << " N " << client.adress[1];
	if (client.adress[2] != "-") {
		cout << " " << client.adress[2];
	}
	cout << endl << "Postal code: " << client.adress[3] << " - " << client.adress[4] << endl;
	cout << "Id of all the packs bought: ";
	for (incri i = 0; i < client.packsbought.size(); i++) {
		if (i != client.packsbought.size() - 1) {
			cout << client.packsbought[i] << " ; ";
		}
		else {
			cout << client.packsbought[i] << endl;
		}
	}
}

void printpackinfo(TravelPack pack) {	//print pack info vertically, easier to read for smaller sized client lists
	cout << "ID: " << pack.id << endl;
	cout << "Main turistic place followed by other recomendations (if any): ";
	if (pack.places.size() == 1) {
		cout << pack.places[0] << endl;
	}
	else {
		cout << endl << pack.places[0] << " - ";
		for (incri i = 1; i < pack.places.size(); i++) {
			if (i != pack.places.size() - 1) {
				cout << pack.places[i] << ", ";
			}
			else {
				cout << pack.places[i] << endl;
			}
		}

	}
	cout << "Beginng: " << pack.beg[0] << "/" << pack.beg[1] << "/" << pack.beg[2] << endl;
	cout << "Ending: " << pack.end[0] << "/" << pack.end[1] << "/" << pack.end[2] << endl;
	cout << "Price per person: " << pack.price << endl << "Initially available seats: " << pack.maxpeeps << endl << "Sold seats: " << pack.sold << endl;
}

//func to change any information about the client which is called by indexation because if there were mistakes and the nif is wrong it is needed to check if there are conflits with nif from other clients
void ChangeClientData(vector<Client> &clientlist, opChoose index) {
	string auxstr, confirmstr;
	Client aux;
	bool invalidnif, confirm;
	aux = clientlist[index];
	clearInput();
	cout << "Here is the actual info about the client." << endl;
	printclientinfo(clientlist[index]);
	cout << "If you do not wish to change certain aspects just press ENTER without any input when prompted." << endl;
	cout << "Name: "; getline(cin, auxstr); if (auxstr.length() != 0) aux.name = auxstr;
	do {		//overall problems with nif
		invalidnif = false;
		cout << "NIF: ";
		getline(cin,auxstr);
		
		if (auxstr.length() != 9 && auxstr.length()!=0) {
			cout << endl << "Wrong nif length, please try again." << endl;
			invalidnif = true;
		}
		else {
			for (incri i = 0; i < auxstr.size(); i++) {
				if (!isdigit(auxstr[i])) {
					cout << endl << "Client nif contains characters that aren't numbers." << endl;
					invalidnif = true;
					break;
				}
			}
			if (!invalidnif) {
				for (incri i = 0; i < clientlist.size(); i++) {
					if (clientlist[i].nif == auxstr) {
						cout << endl << "A client with that NIF already exists. Please try again." << endl;
						invalidnif = true;
						break;
					}
				}
			}
		}
	} while (invalidnif);
	if (auxstr.length() != 0) aux.nif = auxstr;
	cout << "Adress' street: "; getline(cin, auxstr); if (auxstr.length() != 0) aux.adress[0] = auxstr;
	cout << "Adress' door number: "; getline(cin, auxstr); if (auxstr.length() != 0) aux.adress[1] = auxstr;
	cout << "Adress' floor (i.e. 5Esq): "; getline(cin, auxstr); if (auxstr.length() != 0) aux.adress[2] = auxstr;
	cout << "Adress' postal code: "; getline(cin, auxstr); if (auxstr.length() != 0) aux.adress[3] = auxstr;
	cout << "Adress' locality: "; getline(cin, auxstr); if (auxstr.length() != 0) aux.adress[4] = auxstr;
	cout << "These is the new information about the client." << endl;
	printclientinfo(aux);
	do {
		cout << "Do you want to save these changes?" << endl;
		cout << "Y/N: ";
		cin >> confirmstr;
	} while (confirmstr != "Y" && confirmstr != "N" && confirmstr != "y" && confirmstr != "n");	//confirmation
	(confirmstr == "Y" || confirmstr == "y") ? confirm = true : confirm = false;
	if (confirm) {
		clientlist[index] = aux;
		cout << endl << "Changes saved successfully." << endl;
	}
}

//function to change info about the packs, it cant change packs bought so there are no returns :)
void ChangePackData(TravelPack &pack) {
	string auxstr, confirmstr;
	TravelPack aux;
	size_t endPos, startPos;
	bool confirm;
	aux = pack;
	clearInput();
	cout << "Here is the actual info about the pack." << endl;
	printpackinfo(pack);
	cout << "If you do not wish to change certain aspects just press ENTER without any input when prompted." << endl;
	cout << "Main destiny followed by turing sugestions, if any (IN THIS FORMAT: Main - Sugestion, Sugestion, etc)): "; getline(cin, auxstr); 
	if (auxstr.length() != 0) {
		aux.places.clear();
		startPos = endPos = 0;
		endPos = auxstr.find(" - ", startPos);
		aux.places.push_back(auxstr.substr(startPos, endPos - startPos));
		startPos = endPos + 3;
		while (endPos < auxstr.length()) {
			endPos = auxstr.find(", ", startPos);
			if (endPos == string::npos) {
				aux.places.push_back(auxstr.substr(startPos));
				break;
			}
			else {
				aux.places.push_back(auxstr.substr(startPos, endPos - startPos));
				startPos = endPos + 2;
			}
		}
	}
	cout << "Starting date (YYYY/MM/DD): "; getline(cin, auxstr);
	if (auxstr.length() != 0) {
		aux.beg.clear();
		startPos = endPos = 0;
		while (endPos < auxstr.length()) {
			endPos = auxstr.find("/", startPos);
			if (endPos == string::npos) {
				aux.beg.push_back(auxstr.substr(startPos));
				break;
			}
			else {
				aux.beg.push_back(auxstr.substr(startPos, endPos - startPos));
				startPos = endPos + 1;
			}
		}
	}
	cout << "Ending date (YYYY/MM/DD): "; getline(cin, auxstr);
	if (auxstr.length() != 0) {
		aux.end.clear();
		startPos = endPos = 0;
		while (endPos < auxstr.length()) {
			endPos = auxstr.find("/", startPos);
			if (endPos == string::npos) {
				aux.end.push_back(auxstr.substr(startPos));
				break;
			}
			else {
				aux.end.push_back(auxstr.substr(startPos, endPos - startPos));
				startPos = endPos + 1;
			}
		}
	}
	cout << "What is the price per person in euros: "; getline(cin, aux.price);
	printpackinfo(aux);
	do {
		cout << "Do you want to save these changes?" << endl;
		cout << "Y/N: ";
		cin >> confirmstr;
	} while (confirmstr != "Y" && confirmstr != "N" && confirmstr != "y" && confirmstr != "n");
	(confirmstr == "Y" || confirmstr == "y") ? confirm = true : confirm = false;
	if (confirm) {
		pack = aux;
		cout << endl << "Changes save successfully" << endl;
	}
}

void printclientinfo2(Client client) {		//print client info horizontally, more compact for bigger lists but somewhat harder to read
	cout << setw(20) << left << client.name << "Adress: ";
	cout << client.adress[0] << " N " << client.adress[1];
	if (client.adress[2] != "-") {
		cout << " " << client.adress[2];
	}
	cout << " " << client.adress[3] << " - " << client.adress[4] << endl;
	cout << setw(20) << left << "("+client.nif+")" <<"Household: " << client.famsize << " |  Packs bought: ";
	for (incri i = 0; i < client.packsbought.size(); i++) {
		if (i != client.packsbought.size() - 1) {
			cout << client.packsbought[i] << " ; ";
		}
		else {
			cout << client.packsbought[i] << endl;
		}
	}
	
}

void printpackinfo2(TravelPack pack) { //print pack info horizontally, more compact for bigger lists but somewhat harder to read
	cout << setw(5) << left << pack.id << setw(20) << left << pack.places[0];
	cout << setw(12) << left << pack.beg[0] + "/" + pack.beg[1] + "/" + pack.beg[2] << setw(12) << left << pack.end[0] + "/" + pack.end[1] + "/" + pack.end[2];
	cout << setw(6) << left << pack.price << setw(6) << left << pack.maxpeeps << setw(6) << left << pack.sold << endl;
}

void buypack(vector<TravelPack> &packlist, Client &client, string packid) {
	string aux;
	int temp;
	for (size_t i = 0; i < packlist.size(); i++) {
		if (packid == packlist[i].id) {
			temp = stoi(packlist[i].sold);
			temp += 1;
			packlist[i].sold = to_string(temp);
			if (packlist[i].sold == packlist[i].maxpeeps) {
				packlist[i].id = "-" + packlist[i].id;	//make id negative in case it is sold out
			}
			client.packsbought.push_back(packid);
			return;
		}
		else if (packid == packlist[i].id.substr(1,string::npos)) {
			cout << endl << "That pack has already sold out" << endl;
			return;
		}
	}
	cout << "That pack does not exist in the database." << endl;
}
