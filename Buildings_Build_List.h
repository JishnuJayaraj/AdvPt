

#include <vector>
#include <iostream>


#include "Building.h"
#include "Units.h"


class Buildings_Build_List{

    public:

        struct build_item{             // build and its time
            Building build;
            int time;
            bool finish;
        };

        std::vector<build_item> currentList;   // list of building
        // maybe a vector to store finished building also



        void addItem(Building &item) {

            build_item *new_build_item = new build_item; 
            new_build_item->build = item;
            new_build_item->time = item.build_time;
            new_build_item->finish = false;

            currentList.push_back(*new_build_item);
        }


        int numOfAwaitingBuilding() {

            int num =0;
            for(int i=0; i<currentList.size();i++) {
                if(currentList[i].finish == false)
                    num++;
            }

            return num;
        }

// add the finished building to new wvctor
        int numOfFinishedBuilding() {

            int num =0;
            for(int i=0; i<currentList.size();i++) {
                if(currentList[i].finish == true)
                    num++;
            }

            return num;
        }




}