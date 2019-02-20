
#include <iostream>
#include <vector>


#include "Building.h"
#include "Units.h"

class Units_Build_List {

    public:
        struct item {
            Units unit;
            int time;
            bool finish;
        };

        std::vector<item> currentList;



        void addUnit(Units &work) {

            item *newItem= new item;
            newItem->unit = work;
            newItem->time = work.build_time;
            newItem->finish = false;
            currentList.push_back(*newItem);
        }

        int numOfAwaitingUnits() {

            int num=0;
            for(int i=0;i<currentList.size();i++){
                if(currentList[i].finish==false){
                    num++;
                }
            }
            return num; 

        }

        int numOfFinishedUnits() {

            int num=0;
            for(int i=0;i<currentList.size();i++){
                if(currentList[i].finish==true){
                    num++;
                }
            }
            return num; 

        }


};


