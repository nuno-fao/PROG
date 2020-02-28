#pragma once
#include "Agency.h"
#include <iomanip>
#include <math.h>
using namespace std;

void data(Agency agency);
void dataDefault(Agency agency);
void printClientsVector(Agency agency);
void printClientsVector(vector<Client> clients);
void printPacketsVector(Agency agency);
void printPacketsVector(vector<Packet> packet);
void printPacketsVectorWAvailability(vector<Packet> packet);
unsigned selec(unsigned menor, unsigned maior, void data(Agency agency), void menu(Agency agency), Agency agency);
unsigned selec(unsigned menor, unsigned maior);
void clearScreen();
void greatings(Agency agency);
vector<string> vectorString(string morada, string separador);
vector<Packet> StringIDtoPackVec(vector<Packet> packets, vector<string> stringvec);
Packet BinarySearch(vector<Packet> packet, int id);
int BinarySearchID(vector<Packet> packet, int id);
void clearBuffer(void);
bool strIsNumber(string str);
bool checkZip(string zip);
string strVecToStr(vector<string> strvec);
