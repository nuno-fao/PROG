#include "TypeStruDef.h"
#include "Allfuncs.h"

#include <iostream>
#include <locale>
#include <cstddef>
#include <iomanip>
#include <fstream>

using namespace std;

int main() {
	vector<Client> clients;
	vector<TravelPack> packs;
	vector<incri> toprint, startdate, enddate;
	bool nextop = true, invalidinp, wrongnif, found, confirm;
	int manageind, total;
	size_t startPos, endPos;
	string straux, negID, confirmstr;
	opChoose op;
	cout << "Hello user! :)" << endl;
	clients = readClients();
	packs = readPacks();
	do {
		switch (mainmenu()) {
		case 1:		//manage clients menu
			do {
				invalidinp = false;
				cout << endl << "Input..." << endl;
				cout << "[1] - To add a client." << endl << "[2] - To manage a client's data or make a purchase for him." << endl << "[3] - To remove a client." << endl << "[0] - To end this operation." << endl;
				cout << "What would you like to do? ";
				cin >> op;
				clearInput();
				if (cin.fail() || op < 0 || op>4) {
					invalidinp = true;
				}
				else {
					switch (op) {
					case 1:
						addClient(clients, packs);
						break;
					case 2:		//make a purchase or change info
						do {		//get the nif of subject
							found = false;
							wrongnif = false;
							cout << endl << "Input the NIF of the client's data you wish to manage (0 to go back): ";
							getline(cin, straux);
							if (straux.length() != 9 && straux != "0") {
								cout << endl << "Wrong nif length, please try again." << endl;
								wrongnif = true;
							}
							else if (straux != "0" && !wrongnif) {
								for (incri i = 0; i < straux.size(); i++) {
									if (!isdigit(straux[i])) {
										cout << endl << "Client nif contains characters that aren't numbers." << endl;
										wrongnif = true;
										break;
									}
								}
								if (!wrongnif) {
									for (incri i = 0; i < clients.size(); i++) {
										if (clients[i].nif == straux) {
											manageind = i;
											found = true;
											break;
										}
									}
								}
							}
							if (!found) {
								cout << "There is no client with that NIF" << endl;
								wrongnif = true;
							}
						} while (wrongnif && straux != "0");
						if (straux != "0") {
							do {
								cout << "Do you want to make a purchase?" << endl;		//select what to do
								cout << "Y/N: ";
								cin >> confirmstr;
							} while (confirmstr != "Y" && confirmstr != "N" && confirmstr != "y" && confirmstr != "n");
							(confirmstr == "Y" || confirmstr == "y") ? confirm = true : confirm = false;
							if (confirm) {	//buy algo
								cout << "Here are all the packs" << endl;
								cout << setw(5) << left << "ID" << setw(20) << left << "Destiny" << setw(12) << left << "Start" << setw(12) << left << "End" << setw(6) << left << "Price" << setw(6) << left << "Max" << setw(6) << left << "Sold" << endl;
								for (incri i = 0; i < packs.size(); i++) {
									if (packs[i].id[0] != '-') {
										printpackinfo2(packs[i]);
										cout << endl;
									}
								}
								cout << "What is the id of the pack you want to buy (only positive ones)? ";
								cin >> straux;
								buypack(packs, clients[manageind], straux);
							}
							else {	//change
								ChangeClientData(clients, manageind);
							}
						}
						break;
					case 3:	//delete a client
						removeClient(clients);
						break;
					case 0:
						break;
					}
				}
			} while (invalidinp);
			break;
		case 2:		//manage packs menu
			do {
				invalidinp = false;
				cout << endl << "Input..." << endl;
				cout << "[1] - To add a pack." << endl << "[2] - To manage a pack's data." << endl << "[3] - To remove a pack." << endl << "[0] - To end this operation." << endl;
				cout << "What would you like to do? ";
				cin >> op;
				if (cin.fail() || op < 0 || op>3) {
					clearInput();
					invalidinp = true;
				}
				else {
					switch (op) {
					case 1:	// to add a new pack
						addPack(packs);
						break;
					case 2:
						do {	//change pack members
							invalidinp = false;
							manageind = -1;
							cout << endl << "Input the ID of the pack's data you wish to manage (0 to go back): ";
							cin >> straux;

							if (straux != "0") {
								for (incri i = 0; i < clients.size(); i++) {
									if (packs[i].id == straux || (packs[i].id.substr(1)==straux && straux.length()== packs[i].id.length()-1)) {
										manageind = i;
										ChangePackData(packs[i]);
										break;
									}
								}
							}
						} while (manageind == -1);
						break;
					case 3:		//delete a pack
						removePack(packs);
						break;

					case 0:

						break;
					}
				}
			} while (invalidinp);
			break;
		case 3:		//Visualize information menu
			do {
				invalidinp = false;
				cout << endl << "Input..." << endl;
				cout << "[1] - To view clients info." << endl << "[2] - To view packs info." << endl << "[0] - To cancel operation." << endl;
				cout << "What would you like to do? ";
				cin >> op;
				clearInput();
				if (cin.fail() || op < 0 || op>2) {
					cout << "There is no such option" << endl;
					clearInput();
					invalidinp = true;
				}
				else {
					switch (op) {
					case 1:		//specify clients info to be output
						do {
							invalidinp = false;
							cout << endl << "Input..." << endl;
							cout << "[1] - To view all clients' info." << endl << "[2] - To view a specific client's info." << endl << "[0] - To cancel operation." << endl;
							cout << "What would you like to do? ";
							cin >> op;
							clearInput();
							if (cin.fail() || op < 0 || op>2) {
								cout << "There is no such option" << endl;
								clearInput();
								invalidinp = true;
							}
							else {
								switch (op) {
								case 1:		//output all clients
									cout << setw(20) << left << "Name" << "Information" << endl << "(NIF)" << endl;
									for (incri i = 0; i < clients.size(); i++) {
										printclientinfo2(clients[i]);
										cout << endl;
									}
									break;
								case 2:		//output one that is searched by nif
									do {
										found = false;
										wrongnif = false;
										cout << endl << "Input the NIF of the client's data you wish to manage (0 to go back): ";
										getline(cin, straux);
										if (straux.length() != 9 && straux != "0") {
											cout << endl << "Wrong nif length, please try again." << endl;
											wrongnif = true;
										}
										else if (straux != "0" && !wrongnif) {
											for (incri i = 0; i < straux.size(); i++) {
												if (!isdigit(straux[i])) {
													cout << endl << "Client nif contains characters that aren't numbers." << endl;
													wrongnif = true;
													break;
												}
											}
											if (!wrongnif) {
												for (incri i = 0; i < clients.size(); i++) {
													if (clients[i].nif == straux) {
														printclientinfo(clients[i]);
														found = true;
														break;
													}
												}
											}
										}
										if (!found) {
											cout << "There is no client with that NIF" << endl;
											wrongnif = true;
										}
									} while (wrongnif && straux != "0");
									break;
								case 0:
									break;
								}
							}
						} while (invalidinp);
						break;
					case 2:			//visualise packs menu
						do {
							invalidinp = false;
							cout << endl << "Input..." << endl;
							cout << "[1] - To view all packs' info." << endl << "[2] - To view packs with a specific destiny." << endl << "[3] - To view packs between a specific date." << endl << "[0] - To cancel operation." << endl;
							cout << "What would you like to do? ";
							cin >> op;
							clearInput();
							if (cin.fail() || op < 0 || op>3) {
								cout << "There is no such option" << endl;
								clearInput();
								invalidinp = true;
							}
							else {
								switch (op) {
								case 1:		//output all packs
									cout << setw(5) << left << "ID" << setw(20) << left << "Destiny" << setw(12) << left << "Start" << setw(12) << left << "End" << setw(6) << left << "Price" << setw(6) << left << "Max" << setw(6) << left << "Sold" << endl;
									for (incri i = 0; i < packs.size(); i++) {
										printpackinfo2(packs[i]);
										cout << endl;
									}
									break;
								case 2:		//out all that have the one main destiny
									toprint.clear();
									cout << endl << "Main destiny you want to search by (0 to go back): ";
									getline(cin, straux);
									if (straux != "0") {
										for (incri i = 0; i < packs.size(); i++) {
											if (straux == packs[i].places[0]) {
												toprint.push_back(i);
											}
										}
										if (toprint.size() >= 1) {
											cout << setw(5) << left << "ID" << setw(20) << left << "Destiny" << setw(12) << left << "Start" << setw(12) << left << "End" << setw(6) << left << "Price" << setw(6) << left << "Max" << setw(6) << left << "Sold" << endl;
											for (incri i = 0; i < toprint.size(); i++) {
												printpackinfo2(packs[toprint[i]]);
												cout << endl;
											}
										}
										else {
											cout << "The is no pack with that turistic destiny." << endl;
										}
									}
									break;
								case 3:	//output between two dates
									toprint.clear();
									cout << "In the format YYYY/MM/DD what is the starting date: ";
									cin >> straux;
									startPos = endPos = 0;
									while (endPos < straux.length()) {
										endPos = straux.find("/", startPos);
										if (endPos == string::npos) {
											startdate.push_back(stoi(straux.substr(startPos)));
											break;
										}
										else {
											startdate.push_back(stoi(straux.substr(startPos, endPos - startPos)));
											startPos = endPos + 1;
										}
									}
									cout << endl << "In the format YYYY/MM/DD what is the ending date: ";
									cin >> straux;
									startPos = endPos = 0;
									while (endPos < straux.length()) {
										endPos = straux.find("/", startPos);
										if (endPos == string::npos) {
											enddate.push_back(stoi(straux.substr(startPos)));
											break;
										}
										else {
											enddate.push_back(stoi(straux.substr(startPos, endPos - startPos)));
											startPos = endPos + 1;
										}
									}
									for (incri i = 0; i < packs.size(); i++) {	//do not know
										if ((stoi(packs[i].beg[0]) + stoi(packs[i].beg[1]) / 100 + stoi(packs[i].beg[2]) / 10000) <= (startdate[0] + startdate[1] / 100 + startdate[2]/10000)) {
											if ((stoi(packs[i].end[0]) + stoi(packs[i].end[1]) / 100 + stoi(packs[i].end[2]) / 10000) >= (enddate[0] + enddate[1] / 100 + enddate[2] / 10000)) {
												toprint.push_back(i);
											}
										}

									}
									if (toprint.size() >= 1) {
										cout << setw(5) << left << "ID" << setw(20) << left << "Destiny" << setw(12) << left << "Start" << setw(12) << left << "End" << setw(6) << left << "Price" << setw(6) << left << "Max" << setw(6) << left << "Sold" << endl;
										for (incri i = 0; i < toprint.size(); i++) {
											printpackinfo2(packs[toprint[i]]);
											cout << endl;
										}
									}
									else {
										cout << "There is no pack that matches that criteria." << endl;
									}
									break;
								case 0:
									break;
								}
							}
							break;
						} while (invalidinp);
					}
				}
			}while (invalidinp);
			break;
		case 4:		//get to total sales
			total = 0;
			for (incri i = 0; i < packs.size(); i++) {
				total += stoi(packs[i].sold);
			}
			cout << "The agency has sold a total of " << total << " packs!!!" << endl;
			break;
		case 0:	//close the program and save
			nextop=false;
			writeClients(clients);
			writePacks(packs);
			cout << endl << "Well then have a good day :)" << endl;
			break;
		}
	} while (nextop);
	return 0;
}