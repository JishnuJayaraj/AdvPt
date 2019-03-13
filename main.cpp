#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>

#include "json.hpp"
#include "Gameinfo.cpp"
#include "Game_Object.h"
#include "Resources.h"

// #include "Unit_Current.h"
// #include "Building_Current.h"
// #include "Units_Build_List.h"
// #include "Buildings_Build_List.h"

#include "Units.h"
#include "Building.h"


using json = nlohmann::json ;
json j_all;           // game-buildlistValid-initialUnit-message
 json j_init;
 json j_message;       std::vector<json> j_MESSAGES;//-- time-status-events
  json j_status;      // resource , workers
  json j_eventS, j_eventE;     std::vector<json> j_EVENTS;// (build start, end, unit create, special)

 int ct =8 ;                               //??????? inside build fn parameter prod num??
 std::ofstream out; 
	// function to search for "item" in temp "build list" temp
	bool searchBuildDepend(std::string itemname, std::vector<std::string> &tmplist){

		 
		std::string str;               // delete it
		std::cout<<"looking for :"<<itemname<<" in temp list \n Temp List :";   //del   
		for(unsigned int i=0; i!= tmplist.size(); ++i){                      // del
			std::cout<<tmplist[i]<<"~";
		}                                                           // del

		for(unsigned int i=0; i!= tmplist.size(); ++i){
			str = tmplist[i];
			std::cout<<"\n    checking in temp buildList item:"<<str;
			if(itemname.find(str) != std::string::npos) {//if(tmplist[i]==itemname){
			    std::cout<<" -FOUND-\n";                        // delete it
				return true;
	    	}
		}
		std::cout<<"invalid Item: "<<str<<std::endl;       // delete it
		return false;
	}

	
	void initial_Condition(std::multimap <std::string, Game_Object*> *current) {

		current->insert( {"command_center", new Building ("command_center","null",1,0,0)} );
		current->insert({ "scv", new Scv("scv", "null", 2,0,1) });
		current->insert({ "scv", new Scv("scv", "null", 3,0,1) });
		current->insert({ "scv", new Scv("scv", "null", 4,0,1) });
		current->insert({ "scv", new Scv("scv", "null", 5,0,1) });
		current->insert({ "scv", new Scv("scv", "null", 6,0,1) });
		current->insert({ "scv", new Scv("scv", "null", 7,0,1) });

		j_init["command_center"] = { 1 };
		j_init["scv"] = { 2,3,4,5,6,7 };
	}

	void print_Resource(std::multimap <std::string, Game_Object*> current, Resources &resource, std::multimap <int, Game_Object*> Temp) {               // Fill in
		
		std::cout<<"  print resource fn\n";                             //del
		
		double w_mineral = 0, w_vespene = 0;
		double current_sup =0 ; //, sup_used=0;         // del sup_used

		std::multimap <std::string, Game_Object*>::iterator it;
		std::multimap <int, Game_Object*>::iterator its;

		std::cout<<"\tCurrent: ";                                      //del
		for(it=current.begin() ; it != current.end() ; it++) {
			std::cout<<it->first<<" ";                                 //del
			current_sup += it->second->getSupplyUsed();
			if((it->first == "scv") && (it->second->getOccupied() > 0)) {
				char w_type = it->second->workerType();
				switch(w_type) {
					case 'm':
						w_mineral++; break;
					case 'v':
						w_vespene++; break;
				}
			}

		}

		std::cout<<"\n\tTemp: ";                                         //del
		for (its = Temp.begin(); its != Temp.end(); its++) { 
			std::cout<<its->second->getName()<<" ";                        //del
			current_sup += its->second->getSupplyUsed();
		}

		int cc_count = current.count("command_center");
		int oc_count = current.count("orbital_command");
		int pf_count = current.count("planetary_fortress");
		int sd_count = current.count("supply_depot");
		int total_sup = 11 * (cc_count + oc_count + pf_count) + 8 * (sd_count);

		double min = resource.minerals;           std::cout<<"\n\t mineral: "<<min;  //del
		double vesp = resource.vespene;           std::cout<<"  vespene: "<<vesp;


		j_status = {
			{"workers",{
				{"minerals", w_mineral},
				{"vespene", w_vespene}
			}},
			{"resources", {
				{"minerals", min},
				{"vespene", vesp},
				{"supply_used", current_sup},
				{"supply", total_sup}
			}}
		};


	}

	void update_Resource(int t, std::multimap<std::string, Game_Object*> current, Resources& resource, std::multimap <int, Game_Object*> Temp) {

				std::cout<<"\n  update resources fn\n";


		double w_mineral = 0, w_vespene = 0;
		double current_sup =0, temp_sup=0, sup_used=0;

		std::multimap <std::string, Game_Object*>::iterator it; // loop current

		std::cout<<"\tCurrent: ";                                     //del
		for(it=current.begin() ; it != current.end() ; it++) {
			std::cout<<it->first<<" ";                               //del
			if((it->first == "scv") && (it->second->getOccupied() > 0)) {
				char w_type = it->second->workerType();
				switch(w_type) {
					case 'm':
						w_mineral++; break;
					case 'v':
						w_vespene++; break;
				}
			}

			current_sup += it->second->getSupplyUsed();

		}

		std::multimap <int, Game_Object*>::iterator itt;
		std::cout<<"\n\tTemp: ";                                      //del
		for(itt=Temp.begin();itt != Temp.end(); itt++) { 
			std::cout<<itt->second->getName()<<" ";                     //del
			temp_sup += itt->second->getSupplyUsed();
		}

		sup_used = current_sup + temp_sup;

		std::cout<<"\n\tworker status (m,v,s,t) :"<<w_mineral<<" "<<w_vespene<<" "<<sup_used<<" ";    //deletee 

		int cc_count = current.count("command_center");
		int oc_count = current.count("orbital_command");
		int pf_count = current.count("planetary_fortress");
		int sd_count = current.count("supply_depot");
		int total_sup = 11 * (cc_count + oc_count + pf_count) + 8 * (sd_count);

        std::cout<<total_sup;                            //del
	// Specialll
		bool m_empty;
		if (oc_count > 0){            // check mule vector is empty
			m_empty = current.find("orbital_command")->second->getMule().empty();

		}
		else
			m_empty = true;

		if(!m_empty) {
			      //delete
			int size = current.find("orbital_command")->second->getMule().size();
			resource.updateResource((w_mineral*0.7+size*2.8), w_vespene* 0.35, sup_used, total_sup);
			std::cout<<"\n\t <update resource class called for mule>\n"<<resource.minerals<<" "<<resource.vespene<<" "<<resource.supply_used<<" "<<resource.supply_total;
		}
		else
		{
			resource.updateResource((w_mineral*0.7), (w_vespene* 0.35), sup_used, total_sup);
			std::cout<<"\n\t <update resource class called for no mule> current (m,v,s,t): "<<resource.minerals<<" "<<resource.vespene<<" "<<resource.supply_used<<" "<<resource.supply_total;            //del
		}
		
		for (auto p : current)
		{
			if (p.first == "orbital_command")
			{
				p.second->energyUpdate();                                               //to update orbital command energy
				p.second->mule_update(t);
			}
		}


	}


	void worker_distribution(std::multimap <std::string,Game_Object*>& current) {
		int count_refinery=current.count("refinery");

		int count=0;   // count of scv in vespene

		std::cout<<"\n  worker dist fn\n";   
		std::cout<<"\tNo: of refineries :"<<count_refinery<<std::endl;                                  //del
		std::multimap <std::string, Game_Object*>::iterator it;
		for(it=current.begin(); it != current.end(); it++) {
			if(count == 3*count_refinery) // max 3 scv on vespene
				return;

			if(it->first == "scv") {
				std::cout<<"\n\t<add worker to vespene>\n";                 //del
				it->second->updateWorkerType('v');
				count++;                                         // keep adding until 3 worker on refineries
			}

		} 


	}

	// time | current | res | temp   ?name
	std::string build_start(int t, std::string name, std::multimap<std::string, Game_Object*> & current, Resources &resource,  std::multimap <int, Game_Object*>& Temp) {

		j_eventS.clear();
		//std::string name ; // = "" ;                      // check pass as arg
		// check for mule deployment

		for(auto it = current.begin(); it != current.end(); it++) {
			if(it->first == "orbital_command") {
				if(it->second->getEnergy() >= 50) {
					name = "mule";                 
					std::cout<<"mule check PASS";                           //del
				}    // why reanmae
			}
		}

		std::cout<<"\n  buildStart fn called for: <<"<<name<<">> detils from list(m,v,t,s) :";     //del

		Gameinfo game;
		auto list = game.searchItem(name);
		double min=std::get<0>(list.second);                    std::cout<<min<<" "; // del
		double ves=std::get<1>(list.second);                    std::cout<<ves<<" ";
		int tim= std::get<2>(list.second);                      std::cout<<tim<<" ";
		double sup_needed=std::get<3>(list.second);				std::cout<<sup_needed<<" ";
		std::string prod_name =std::get<4>(list.second);  // whole list with /
		std::string dep_name =std::get<5>(list.second);

		// bool check = true;              // del

		if(!resource.checkResource(min,ves,sup_needed)) {
		    std::cout<<"\n\tResource requirement not met \n";                            //del
			return "no build";
		}

/*
		if(!checkProducer(prod_name, current)) {
			std::cout<<"Producer requirement not met \n";
			return "no build";
		}

		if(!checkDependency(dep_name, current)) {
			std::cout<<"Dependency requirement not met \n";
			return "no build";
		}		
		*/
// json

		if(name=="mule")
			j_eventS["type"] = "special";
		else
		{
			j_eventS["type"] = "build-start";
		}

		json j_eventName(name);
		j_eventS["name"] = j_eventName;

		std::cout<<"\n\tBefore modify res called(m,v,s,t) :"<<resource.minerals<<" "<<resource.vespene<<" "<<resource.supply_used<<" "<<resource.supply_total; 
		resource.modifyResource(min, ves, sup_needed);
		std::cout<<"\n\tAfter modify res called(m,v,s,t) :"<<resource.minerals<<" "<<resource.vespene<<" "<<resource.supply_used<<" "<<resource.supply_total;
		// check producer
		std::multimap<std::string, Game_Object*>::iterator it;              // need del_it
		for(it=current.begin(); it != current.end(); it++) {
			if(prod_name.find(it->first) != std::string::npos) {   //if(it->first == prod_name) {                  //big prod name
				if(name == "mule") {
					it->second->activate_mule(t);
					json j_trig(it->second->getNumber() ); // return the id
					j_eventS["triggered_by"] = j_trig;
				}
				else {                    // from list act time | time neede | Temp | nameOf Item to be build | no | sup neede by item
					it->second->build(t, tim, Temp, name, ct++, sup_needed );             // whats hapenin ct????
					it->second->updateOccupied('-');
					json j_trig(it->second->getNumber() );
					j_eventS["producerID"] = j_trig;
				}

				break;
			}
		}

		j_EVENTS.push_back(j_eventS);
		return name;

	}


	void build_end(int t, std::multimap <std::string, Game_Object*>& current, std::multimap <int, Game_Object*>& Temp) {

		j_eventE.clear();

		std::cout<<"\n  buildend fn\n";              //delete

		std::multimap <int, Game_Object*>::iterator its = Temp.begin();
		std::multimap <std::string, Game_Object* >::iterator cur_its;
		std::vector <int> num;        // 

		std::multimap <int, Game_Object* >::iterator del_its = Temp.end(); //?????

		while(its != Temp.end()) {

			j_eventE.clear();
			if(t == its->first) { // current tim = build end time

				std::string temp_name = its->second->getName();
				std::cout<<"\tBuild end of: "<<temp_name;              //  delete

							if (temp_name == "orbital_command" || temp_name == "planetary_fortress" || temp_name == "factory_with_reactor" ||
								temp_name == "factory_with_tech_lab" || temp_name == "starport_with_reactor" || temp_name == "starport_with_tech_lab"
								|| temp_name == "barracks_with_tech_lab" || temp_name == "barracks_with_reactor") {

									for(cur_its = current.begin(); cur_its != current.end(); cur_its++) {

										if(cur_its->second->getNumber() == its->second->getProdnum()) {

											current.erase(cur_its);            // ???????
											break;
										}
									}

								}

				current.insert({ its->second->getName(), its->second }) ;// copy from temp vector to actual vector
				for (cur_its = current.begin(); cur_its != current.end(); cur_its++)   //searching actual vector
				{
					if (cur_its->second->getNumber() == its->second->getProdnum())     // search for producer
						cur_its->second->updateOccupied('+');
				}

				num.push_back(its->second->getNumber());
				json j_num(num);
				json j_name(its->second->getName());
				json j_prod(its->second->getProdnum());

				j_eventE = {
					{"type", "build-end"},
					{"name", j_name},
					{"producerID", j_prod},
					{"producedIDs", j_num}
				};

				del_its = its;
			}

			its++ ;
			if (del_its != Temp.end())
			{
				j_EVENTS.push_back(j_eventE);
				Temp.erase(del_its);              //delete the copy in temp after transferred to actual
				del_its = Temp.end();
			}

		}


	}


int main(int argc, char *argv[]){

    std::string race = argv[1];
    std::string buildlist = argv[2];

	out.open("result.txt");   // write output to file

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
	std::cout<<std::endl;

	//--------------------------- check for build list validity-------------------------------

	Gameinfo game;

	// bool dependency = true;
	std::vector<std::string>tmplist;
	tmplist.push_back("command_center"); // store the initial condition
	tmplist.push_back("scv");
 
	std::cout<<"Initial templist :";              // del
	for(unsigned int i=0; i!= tmplist.size(); ++i){ 
		std::cout<<tmplist[i]<<" ";
	}
	std::cout<<std::endl;

	int flag =0;                         // valid buildlist
	for(unsigned int builidItem =0; builidItem < build.size(); builidItem++) { // loop thr build list
		//int index=-1;
		//std::map < std::string, std::tuple <double, double, int, double, std::string, std::string > >::iterator i;
		//for(auto i=Validity.cbegin() ; i != Validity.cend() ; ++i) // loop thr VAlidity
		//for (auto invItr:game.inventory) {   // .begin()
		
		//for (auto invItr=game.inventory.begin(); invItr != game.inventory.end(); invItr++) { 
		//	if(game.searchName(build[builidItem])) {

			std::string thing=build[builidItem];
			auto invItr = game.inventory.find(thing);
			auto index = invItr;  // index of build item in inventory map
				std::cout<<"item about to build is :"<<thing<<"\n";             // del
				tmplist.push_back(thing);


// use switch with loop here 	for (int i = 0; i < 2; i++)
//                                    switch (i) 
//                                        case 0:                                    break

				// Check if dependency col is 'null' OR if temp buildlist has item in 'depend' col
				 if(std::get<5>(index->second) == "null" || searchBuildDepend(std::get<5>(index->second),tmplist)) { 
				// if(std::get<5>(index.second) == "null" || searchBuildDepend(game.searchDependency(builidItem),tmplist))
					std::cout<<" dependecy found"<<"\n";
					continue; // break;
				}
				// Check if tmp build list contain item in produced by col
				if(searchBuildDepend(std::get<4>(index->second),tmplist)) { 
					std::cout<<" produced by found \n";
					continue; //break;     
				}  

				else {
					std::cout<<"dependency/producedBy fail "<<std::endl ; 
					flag = 1; // invalid build list
					break;
				}

			if(flag ==1)
				break;
			//}
		//}
		


	}


	if(flag == 0)
		std::cout<<"\n ------ VALID BUILD LIST ------ \n";
	else
		std::cout<<"\n -----NON VALID BUILD-LIST------ \n";

	Resources resource = *new Resources(50,0,6,11); // cc and 6 worker

	std::multimap <std::string, Game_Object*> current; // holds units and buildings of game
	std::multimap <int, Game_Object*> Temp;    // obj with time for BUILD END	
	
	initial_Condition(&current);

	std::string check = "null";                                    //
	std::vector<std::string>::iterator buildItr = build.begin();   //iterator to go thr build list
	std::string entity = *buildItr;                                // each item
	int timee =1;
	// Game loop
	while (buildItr != build.end() || !Temp.empty() ) {
		if(timee > 1000) {          
			std::cout<<"\n\n <<<<<< Time Exceeds 1000 >>>>>>";
			break;

		}

		j_message.clear();

		if(buildItr == build.end())                    //del
			entity = "null";
		else
		{
			entity = *buildItr;
			std::cout<<"\n\nentity: "<<entity<<"  time :"<<timee<<"\n";                    // delete
		}
		
		update_Resource(timee, current, resource, Temp);
		build_end(timee, current, Temp);
		check = build_start(timee, entity, current, resource, Temp);
		std::cout<<"\n  check value in main: "<<check;                                   //del
		worker_distribution(current);

		print_Resource(current, resource, Temp);

		j_message["time"] = timee;
		j_message["status"] = j_status;
		j_message["events"] = j_EVENTS;

		if(!j_EVENTS.empty()) {       //{
			j_MESSAGES.push_back(j_message);
			j_EVENTS.clear();
		}

//		itr--;



		timee++;
		 //++buildItr;                                                //
		if (check == entity){
			std::cout<<"check status sucess";                       // delete
			++buildItr;
		}
	}


	if (timee < 1000) {
	j_all = {
		{ "buildlistValid",1 },
		{ "game","sc2-hots-terran" },
		{ "initialUnits",j_init },
		{ "messages",j_MESSAGES } };
	out << j_all;
		//out << time;
	}
	else
	{
		j_all = {
		{ "buildlistValid",0 },
		{ "game","sc2-hots-terran" }
		};
		out << j_all;
		//out << time;
	}

	out.close();





}
