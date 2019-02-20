#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "json.hpp"
 int main()
 {

	std::cout<<"HelloWorld";

	std::string str ("command_center/orbital_command/planetary_fortress");
	std::string str2 ("command_centers");

	if (str.find(str2) != std::string::npos) {
 	
		std::cout<<"found";
    }

// string streams: concatenate int, double, string into a single alrge string

    std::stringstream ss;
    ss<<123<<"jishnu";

    std::string var = "age24";
    ss<<var;

    std::cout<<ss.str();


    ss.clear(); // clear the error
    ss.str(""); // clear all


   // -------------- json out file --------------


    std::ofstream out;
    out.open("myoutput.txt");

    using json = nlohmann::json;
    json all;

    bool validity = false;

    if(validity)
    {
    			all = {
							{ "buildlistValid",0 },
						    { "game","sc2-hots-terran" }
					  };
		out << all;
    }

    else {
    	

    	json init;
		init["command_center"] = { 1 };
		init["scv"] = { 2,3,4,5,6,7 };

		std::vector<json> mes;

		json status;
		status = {
				{ "workers",{
					{ "minerals",5 },
					{ "vespene",5 }
				} },
				{ "resources",{
					{ "minerals",6 },
					{ "vespene",3 },
					{ "supply-used",3 },
					{ "supply",10 }
				} }
			};
/*
			// special
			k["type"] = "special";
			k["type"] = "build-start";
			json k_name("jishnu");
			k["name"] = k_name;
			k["triggeredBy"] = "trigerdby";
			k["producerID"] = "prodID";

*/

			std::vector<json> events;
			json eventStart, eventEnd, eventSpcl ;

			eventStart = {
					{ "type", "build-start" },
					{ "name", "j_name" },
					{ "producerID", "_prid" }
				};

			eventEnd = {
					{ "type", "build-end" },
					{ "name", "j_name" },
					{ "producerID", "_prid" },
					{ "producedIDs", "j_numend" }
				};

			eventSpcl = {
					{ "type", "special" },
					{ "name", "mule" },
					{ "triggeredBy", "j_trigBy" }
				};

			// OR



/*

			std::string name = "mule";
			eventSpcl["type"] = "special";
			eventSpcl["name"] = name;
			eventSpcl["producerID"] = "pr_id";
			eventSpcl["triggerredBy"] = "triggered by";

*/

			events.push_back(eventStart);
			events.push_back(eventEnd);
			events.push_back(eventSpcl);



		m["time"] = "time";
		m["status"] = status;
		m["events"] =  events   ; 

		mes.push_back(m);
		
		// n.push_back(m);


   	    all = {
			{ "buildlistValid",1 },
			{ "game","sc2-hots-terran" },
			{ "initialUnits",init },
			{ "messages",mes }        // mes[] -> event[], status, time
		};
		out << all;
	}

	out.close();
}