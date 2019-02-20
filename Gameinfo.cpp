#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iterator>
#include <tuple>


// ------------------------- Create a map for validity check---------// put this in a new class*****


	class Gameinfo {
// item | <mineral | vespene | buidTime | supplyCost | producedBy | dependency > 
	public:
		std::map < std::string, std::tuple <double, double, int, double, std::string, std::string> > inventory;



		// Constructor
		Gameinfo() {

			inventory.insert({ "command_center", {400, 0, 100, 0, "scv", "null" } }  ); 
			inventory.insert({ "scv",			  { 50, 0, 17,1,  "command_center/orbital_command/planetary_fortress",  "null" } });
			inventory.insert({ "orbital_command",{ 150, 0, 35, 0, "command_center", "barracks/barracks_with_tech_lab/barracks_with_reactor" } });
			inventory.insert({ "supply_depot",	  { 100, 0, 30, 0, "scv", "null" } });
			inventory.insert({ "refinery",		  { 75, 0, 30, 0, "scv", "null" } });
			inventory.insert({ "barracks",		  { 150, 0, 65, 0, "scv", "supply_depot" } });
			inventory.insert({ "barracks_with_tech_lab",	{ 50, 25, 25, 0, "barracks", "null" } });
			inventory.insert({ "barracks_with_reactor",	  { 50, 50, 50, 0, "barracks", "null" } });
			inventory.insert({ "factory",		  { 150, 100, 60, 0, "scv", "barracks/barracks_with_tech_lab/barracks_with_reactor" } });
			inventory.insert({ "factory_with_tech_lab",	  { 50, 25, 25, 0, "factory", "null" } });
			inventory.insert({ "factory_with_reactor",	  { 50, 50, 50, 0, "factory", "null" } });
			inventory.insert({ "engineering_bay",{ 125, 0, 35, 0, "scv", "command_center" } });
			inventory.insert({ "planetary_fortress",{ 150, 150, 50, 0, "command_center", "engineering_bay" } });
			inventory.insert({ "bunker",		  { 100, 0, 40, 0, "scv", "barracks/barracks_with_tech_lab/barracks_with_reactor" } });
			inventory.insert({ "ghost_academy",  { 150, 50, 40, 0, "scv", "barracks/barracks_with_tech_lab/barracks_with_reactor" } });
			inventory.insert({ "starport",		  { 400, 0, 100, 0, "scv", "factory/factory_with_reactor/factory_with_tech_lab" } });
			inventory.insert({ "starport_with_tech_lab",	  { 50, 25, 25, 0, "starport", "null" } });
			inventory.insert({ "starport_with_reactor",	  { 50, 50, 50, 0, "starport", "null" } });
			inventory.insert({ "armory",		  { 150, 100, 65, 0, "scv", "factory/factory_with_reactor/factory_with_tech_lab" } });
			inventory.insert({ "missile_turret",  { 100, 0, 25, 0,   "scv", "engineering_bay" } });
			inventory.insert({ "sensor_tower",	  { 125, 100, 25, 0, "scv", "engineering_bay" } });
			inventory.insert({ "fusion_core",	  { 150, 150, 65, 0, "scv", "starport" } });
			inventory.insert({ "marine",		  { 50, 0, 25, 1, "barracks/barracks_with_tech_lab/barracks_with_reactor", "null" } });
			inventory.insert({ "marauder",		  { 100, 25, 30, 2, "barracks_with_tech_lab", "null" } });
			inventory.insert({ "reaper",		  { 50, 50, 45, 1, "barracks_with_tech_lab", "null" } });
			inventory.insert({ "ghost",		  { 200, 100, 40, 2, "barracks_with_tech_lab", "ghost_academy" } });
			inventory.insert({ "hellion",		  { 100, 0, 30, 2, "factory/factory_with_reactor/factory_with_tech_lab", "null" } });
			inventory.insert({ "siege_tank",	  { 150, 125, 45, 3, "factory_with_tech_lab", "null" } });
			inventory.insert({ "thor",			  { 300, 200, 60, 6, "factory_with_tech_lab", "armory" } });
			inventory.insert({ "medivac",		  { 100, 100, 42, 2, "starport/starport_with_reactor/starport_with_tech_lab", "null" } });
			inventory.insert({ "viking",		  { 150, 75, 42, 2, "starport/starport_with_reactor/starport_with_tech_lab", "null" } });
			inventory.insert({ "raven",		  { 100, 200, 60, 2, "starport_with_tech_lab", "null" } });
			inventory.insert({ "banshee" ,		  { 150, 100, 60, 3, "starport_with_tech_lab", "null" } });
			inventory.insert({ "battlecruiser" ,{ 400, 300, 90, 6, "starport_with_tech_lab", "fusion_core" } });
			inventory.insert({ "mule",{ 0, 0, 90, 0, "orbital_command", "null" } });
		}

		

		void printGameinfo () {
		// iterator to point to a member and iterate through...

		//std::map < std::string, std::tuple <double, double, int, double, std::string, std::string > >::iterator itr;

		//for(itr=inventory.begin() ; itr != inventory.end() ; ++itr )
			for (auto x:inventory) {
				std::cout<<x.first<<" "<<std::get<0>(x.second)<<" "<<std::get<1>(x.second)<<" "<<std::get<2>(x.second)<<" "
				<<std::get<3>(x.second)<<" "<<std::get<4>(x.second)<<" "<<std::get<5>(x.second)<<std::endl;//*itr.first<<" "<<itr->second<<std::endl;
			}


		}


		bool searchName(std::string name) {

			std::string name;
			bool found=false;
			std::map < std::string, std::tuple <double, double, int, double, std::string, std::string > >::iterator it;
				for(auto it:inventory) { // it=inventory.cbegin() ; it != inventory.cend() ; ++it){ 
						if(it.first== name)
								found=true;
				}
			return found;			

		}

		//search in "produced by" col of inventory map for "item" 
		bool searchProducedBy(std::string item){

			bool found=false;
			std::map < std::string, std::tuple <double, double, int, double, std::string, std::string > >::iterator it;
			/*	for(auto it:inventory) { // it=inventory.cbegin() ; it != inventory.cend() ; ++it){ 
						if(std::get<4>(it.second) == item)
								found=true;
				}
			*/
				for(auto it:inventory) { // it=inventory.cbegin() ; it != inventory.cend() ; ++it){ 
						std::string str = std::get<4>(it.second);
						if(str.find(item) != std::string::npos)
								found=true;
				}	
				return found;
		}


		// search in "dependecy" col in inventory for "item"
		bool searchDependency(std::string item){

			bool found=false;
			std::map < std::string, std::tuple <double, double, int, double, std::string, std::string > >::iterator it;
	/*			for(auto it: inventory) {//(auto it=inventory.cbegin() ; it != inventory.cend() ; ++it){
						if(std::get<5>(it.second) == item)
							found=true;
				}

	*/			for(auto it: inventory) {//(auto it=inventory.cbegin() ; it != inventory.cend() ; ++it){
						std::string str = std::get<5>(it.second);
						if(str.find(item) != std::string::npos)
							found=true;
				}
			return found;

		}
		

		// 
		std::map < std::string, std::tuple <double, double, int, double, std::string, std::string> > searchItem(std::string name) {

			std::map < std::string, std::tuple <double, double, int, double, std::string, std::string > >::iterator it;

			for(auto it:inventory) { // it=inventory.cbegin() ; it != inventory.cend() ; ++it){ 
				if(it.first== name)
				return *(it);
			}
						

		}
	
/*{
	    for (auto itr = inventory.find(name); itr != inventory.end(); itr++) 
            return *itr;

		}*/

	};