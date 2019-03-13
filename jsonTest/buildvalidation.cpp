#include <iostream>
#include <vector>

main()
{

std::string itemname = "bar";

std::vector<std::string> tmplist;
tmplist.push_back("command_center");
tmplist.push_back("scv");
tmplist.push_back("scv");
tmplist.push_back("barrack");
tmplist.push_back("marine");
tmplist.push_back("marauder");

for(auto c:tmplist)
	std::cout<<c<<" ";

std::cout<<"\nitem name : "<<itemname<<"\n \n";


// std::cout<<tmplist[0]<<" \n"<<tmplist[1]<<" \n"<<tmplist[3];


		std::string factor;                 // delete it
		                                   
		for(int i=0; i!= tmplist.size(); ++i){
			std::string str = tmplist[i];
			std::cout<<"going thr tmplist item :"<<str<<"\n";
			if(str.find(itemname) != std::string::npos) {//if(tmplist[i]==itemname){
				factor=tmplist[i];                            // delete it

				std::cout<<"found :"<<factor;
				break;
	    		}
		}
		// std::cout<<"invalid Item: "<<factor<<std::endl;




}
