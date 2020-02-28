#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "Agency.h"
#include "Menus.h"
#include "funcs.h"
// #include "utils.h"

int main(){
    unsigned option;
    Agency agency;// create the agency
    agency.setPacketsFromFile();
    agency.setClientsFromFile();
    cout << "\e[8;20;150t";
    clearScreen();
    while (true) {
        option=selec(0,3,dataDefault,mainMenu,agency);
        switch (option) {
        //Client's management
        case(1):{
            while ((option=selec(0,5,dataDefault,menu_1,agency))){
                switch (option) {
                //view client's info
                case (1):{
                    (option=selec(0,2,dataDefault,menu_1_1,agency));
					switch (option) {
                    //specific client
					case(1): {
						agency.showClientByVAT();
						break;
						}
                    //all clients
					case(2): {
						(option = selec(0, 0, printClientsVector, menu_1_3, agency));
						break;
						}
					}
                    break;
                }
                //create client
                case (2):{
                    agency.createClient();
                    break;
                }
                //edit client
                case(3):{
                    agency.changeClient();
                    break;
                }
                //make purchase
                case (4):{
                    agency.sellPacketToClient();
                    break;
                }
               //remove client
                case (5):{
                    agency.removeClient();
                    break;
                }
                }

            }
            break;
        }
        //packet management
        case(2):{
            while ((option=selec(0,5,dataDefault,menu_2,agency))) {
                switch (option) {
                //view packets
                case (1):{
                    unsigned option1;
                    while ((option1=selec(0,5,dataDefault,menu_2_1,agency))) {
                        switch (option1) {
                        //view all
                        case (1):{
                            (option1=selec(0,0,printPacketsVector,menu_2_1_1,agency));
                            break;
                        }
                        //view all refering destination
                        case (2): {
                            agency.showPacketByDestiny();
                            break;
                        }
                        //view all between dates
                        case (3): {
                            agency.showPacketByDates();
                            break;
                        }
                        //view between dates and destination
                        case (4):{
                           agency.showPacketByDatesAndDestiny();
                            break;
                        }
                        //view sold packets
                        case (5):{
                            unsigned option2;
                            while ((option2=selec(0,2,dataDefault,menu_2_1_5,agency))) {
                                switch (option2) {
                                //view sold specific clients
                                case(1):{
                                    agency.showPacketsOfClient();
                                    break;
                                }
                                //view sold all clients
                                case(2):{
                                    agency.showPacketsOfAllClients();
                                    break;
                                }
                                }
                            }
                            break;
                        }
                    }
                    }
					break;
                }
                //create packet
				case (2): {
					agency.createPacket();
					break;
				}
                //edit packet
                case (3): {
                    agency.changePackets();
                    break;
                }
                //switch avalability
                case (4):{
                    agency.removePacket();
                    break;
                }
            }
            }
            break;
        }
        //statistics
        case(3):{
            while ((option=selec(0,2,dataDefault,menu_3,agency))) {
                switch (option) {
                //view most visited
                case(1):{
                    agency.showMostPopular();
                    break;
                }
                //view recomendations
                case(2):{
                    agency.showRecommendations();
                }
                }
            }
            break;
        }
        //exit
        case(0):{

            unsigned option1;
            bool confirmExit=true;
            if(agency.getClientsInfoHasChanged() || agency.getPacketsInfoHasChanged()){
                while (confirmExit) {
                    option1=selec(1,3,dataDefault,menu_exit,agency);
                    switch (option1) {
                    //save changes
                    case (1):{
                        //chacks if the informtion has changed, if it has chaged , the program saves the new info
                        if(agency.getClientsInfoHasChanged()){
                            agency.saveClientsToFile();
                        }
                        if(agency.getPacketsInfoHasChanged()){
                            agency.savePacketsToFile();
                        }
                        exit(0);
                    }
                    //continue editing
                    case (2):{
                        confirmExit=false;
                        option=1;
                        break;
                    }
                    //exit without saving
                    case(3):{
                        exit(0);
                    }
                    }
                }
            }
            else {
                exit(0);
            }
            break;
        }
        }
    }
}
