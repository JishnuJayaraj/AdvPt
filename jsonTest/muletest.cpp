#include <iostream>
#include <vector>
#include <iterator>

main()
{

using namespace std;

std::vector<int> mule;
mule.push_back(3);
mule.push_back(10);
mule.push_back(48);
mule.push_back(32);
mule.push_back(11);
mule.push_back(56);

int t = 32;

    for (int x : mule) 
        cout << x << " "; 

			int i = 0;
			for (auto it = mule.begin(); it != mule.end(); it++)
			{
				if (mule[i] == t)
				{
					mule.erase(it);
					break;
				}
				i++;
			}


    for (int x : mule) 
        cout << x << " ";


}
