#include <iostream>
#include <vector>
#include <string>
#include <fstream>


#include "json.hpp"
#include "Gameinfo.cpp"
#include "Game_Object.h"
#include "Resources.h"

#include "Unit_Current.h"
#include "Building_Current.h"
#include "Units_Build_List.h"
#include "Buildings_Build_List.h"

#include "Units.h"
#include "Building.h"

# define MAX_ENERGY 100
using json = nlohmann::json ;

	// function to search for "item" in temp "build list"
	bool searchBuildDepend(std::string itemname, std::vector<std::string> &tmplist){

		std::string factor;                                    // delete it
		for(int i=0; i!= tmplist.size(); ++i){
			if(tmplist[i]==itemname){
				factor=tmplist[i];                            // delete it
				return true;
	    	}
		}
		std::cout<<"invalid Item: "<<factor<<std::endl;       // delete it
		return false;
	}

	
	void initialCondition(Unit_Current uc, Building_Current bc) {

		//Units ; // need 6scv
	
		// uc.addItem(u,true,false);  // *6

		// 1 cc 

	}



int main(int argc, char *argv[]){

    std::string race = argv[1];
    std::string buildlist = argv[2];


	std::cout<<race<<"Reading Build List from"<<buildlist<<std::endl;

    // ----------------------read the build list to vector "build"-------------------------

    std::vector<std::string> build;      // vector to store the build list
    std::ifstream buildListIn;  
	buildListIn.open(buildlist);
	std::string item;                    // to store each line of buid list

    if(!buildListIn){
    	std::cout<<"Error opening :"<<buildlist<<std::endl;

    }

    else {
    	while(buildListIn >> item){      
    		build.push_back(item);       
    		
    	}
    }
	buildListIn.close();

	/*  print out the buildlist

	std::vector<std::string>::iterator iter;
	for(iter=build.begin() ; iter != build.end() ; ++iter ) {
		std::cout<<*iter<<"|";
	}
	*/

    for(auto i:build){
    	std::cout<<i <<" ";
    }	
	

	//--------------------------- check for build list validity-------------------------------

	Gameinfo game;

	bool dependency = true;
	std::vector<std::string>tmplist;
	tmplist.push_back("command_center"); // store the initial condition
	tmplist.push_back("scv");

	int flag =0;                         // valid buildlist
	for(int builidItem =0; builidItem < build.size(); builidItem++) { // loop thr build list
		//int index=-1;
		//std::map < std::string, std::tuple <double, double, int, double, std::string, std::string > >::iterator i;
		//for(auto i=Validity.cbegin() ; i != Validity.cend() ; ++i) // loop thr VAlidity
		for (auto invItr:game.inventory) {   // .begin()
			if(game.searchName(build[builidItem])) {
				auto index = invItr;  // index of build item in inventory map

				tmplist.push_back(build[builidItem]);

				// Check if dependency col is 'null' OR if temp buildlist has item in 'depend' col
				 if(std::get<5>(index.second) == "null" || searchBuildDepend(std::get<5>(index.second),tmplist))
				// if(std::get<5>(index.second) == "null" || searchBuildDepend(game.searchDependency(builidItem),tmplist))
					continue;

				// Check if tmp build list contain item in produced by col
				else if(searchBuildDepend(std::get<4>(index.second),tmplist))
					continue;

				else {
					flag = 1; // invalid build list
					break;
				}

			if(flag ==1)
				break;
			}
		}
		


	}


	if(flag == 0)
		std::cout<<"\n ------ VALID BUILD LIST ------ \n";
	else
		std::cout<<"\n -----NON VALID BUILD-LIST------ \n";





	Resources resources = *new Resources(50,0,6,11,0); // cc and 6 worker

	Unit_Current unitCurrent = *new Unit_Current();
	Building_Current buildingCurrent= *new Building_Current();

	Units_Build_List unitsBuildList = *new Units_Build_List();
	Buildings_Build_List buildingsBuildlist = *new Buildings_Build_List();


	auto temp = game.searchItem("command_center");
	// map | id | time | res
	Building command_center(temp, 1,1, resources);


	std::vector<Building> buildignStorage;
	buildignStorage.push_back(command_center);

/*
	std::map < std::string, std::tuple <double, double, int, double, std::string, std::string>  > gamelist ;
	game.searchItem("scv");
	gamelist.insert(game.searchItem("scv"));
*/



	std::vector<std::string>::iterator buildItr = build.begin();   // iterator to go thr build list
	int time =1;
	// Game loop
	while (buildItr != build.end() ) {
		if(time > 1000) {          
			std::cout<<"Time Exceeds 1000";
			break;

		}






		time++;
		++buildItr;
	}








}
