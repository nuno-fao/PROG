#pragma once

#include <iostream>
#include <string>
#include <vector>


#include "defs.h"
#include "Date.h"

using namespace std;

class Packet{
 private:
	  unsigned id; // packet unique identifier
	  static unsigned lastID;
	  bool available;
	  vector<string> sites; // touristic sites to visit
	  Date begin;  // begin date
      Date end;  // end date
      double pricePerPerson; // price per person
	  unsigned maxPersons; // number of persons still available in the packet (updated whenever the packet is sold to a new client)
      unsigned totalPersons;
 public:
    Packet(unsigned id,vector<string> sites, Date begin, Date end, double pricePerPerson,unsigned totalPersons, unsigned maxPersons);
    Packet(vector<string> sites, Date begin, Date end, double pricePerPerson,unsigned totalPersons, unsigned maxPersons);
    Packet();

// GET methods
	  unsigned getId() const;
	  vector<string> getSites() const;
	  Date getBeginDate() const;
	  Date getEndDate() const;
	  double getPricePerPerson() const;
	  unsigned getMaxPersons() const;
      unsigned getTotalPersons() const;
      unsigned static getLastID();
      string getFullDestination() const;
      bool getAvailability() const;
      void showFullInfo();

// SET methods
	  void setId(unsigned id);  // to set negatve if "deprecated"
	  void setSites(vector<string> sites);
	  void setBeginDate(Date begin);
	  void setEndDate(Date end);
	  void setPricePerPerson(double pricePerPerson);
	  void setMaxPersons(unsigned maxPersons);
	  void setAvailable(bool available);
      void setTotalPersons(unsigned totalPersons);
      void static setLastID(unsigned ID);

// other methods

	//friend ostream& operator<<(ostream& out, const Packet & packet);

};

bool operator == (Packet const &date1,Packet const &data2);
