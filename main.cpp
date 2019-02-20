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


	std::cout<<race<<buildlist<<std::endl;

    // ----------------------read the build list to vector "build"-----//

    std::vector<std::string> build;      // vector to store the build list

    std::ifstream buildListIn;  

    buildListIn.open(buildlist);

    std::string item;                    // to store each line of buid list

    if(!buildListIn){
    	std::cout<<"error opening build List"<<std::endl;

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


    for(auto i:build){
    	std::cout<<i <<" ";
    }	
	*/

	// check for dependencies

	Gameinfo game;

	bool dependency = true;
	std::vector<std::string>tmplist;
	tmplist.push_back("command_center"); // store the initial condition
	tmplist.push_back("scv");

	int flag =0;
	for(int builidItr =0; builidItr < build.size(); builidItr++) { // loop thr build list
		//int index=-1;
		//std::map < std::string, std::tuple <double, double, int, double, std::string, std::string > >::iterator i;
		//for(auto i=Validity.cbegin() ; i != Validity.cend() ; ++i) // loop thr VAlidity
		for (auto invItr:game.inventory) {
			if(game.searchName(build[builidItr])) {
				auto index = invItr;  // index of build item in inventory map

				// Check if dependency col is 'null' OR if temp buildlist has item in 'depend' col
				if(std::get<5>(index.second) == "null" || searchBuildDepend(std::get<5>(index.second),tmplist))
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


Building commandcenter(findName("commanc center"), id,sdj, sadjf, json);


std::vector<Building> buildignStorage;
buildignStorage.push_back(commandcenter);


std::map < std::string, std::tuple <double, double, int, double, std::string, std::string>  > gamelist ;
game.searchItem("scv");
gamelist.insert(game.searchItem("scv"));




for(int i=0 ; i<1000 ; i++) {




}



/*

std::string s = "[\"nlohmann\", \"json\"]";
json second = json::parse(s);

auto j3 = json::parse("{ \"happy\": true, \"pi\": 3.141 }");
std::string R;
auto j3 = json::parse(R"(
	{
	"happy": true,
	"pi": 3.141 
	}
	)")_json;
	*/
}
