#ifndef TYPESTRUDEF_H
#define TYPESTRUDEF_H

#include <vector>
#include <string>
using namespace std;

//defining new types to help readability

typedef short int opChoose;
typedef unsigned int incri;

//defining the new types of data needed		(No enunciado dizia para definir uma struct para o adress e as datas mas achei desnessario e so iria complicar o algoritmo de leitura)

struct TravelPack {
	string id;
	string maxpeeps, sold, price;
	vector<string> places, beg, end;   //dates are in the format YYYY/MM/DD
};

struct Agency {
	string name, weburl, clients, packs, nif;
	vector<string> adress;
};

struct Client {
	string name, famsize, shoptotal, nif;
	vector<string> packsbought, adress;
};

#endif