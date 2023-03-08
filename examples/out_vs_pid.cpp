#include <stdio.h>
#include <string.h>
#include <exception>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;

int min(int a, int b){
	return a <= b ? a:b; 
}

int main(){

	string fPIDname = "/Volumes/Passport/CERN/sFGD/data/2018_July/out.txt";
	string fsFGDname = "/Volumes/Passport/CERN/sFGD/data/2018_July/sFGD.txt";
	string foutPIDsFGDname = "/Volumes/Passport/CERN/sFGD/data/2018_July/PIDsFGD.txt";
	ifstream PIDdata(fPIDname.c_str());
	ifstream sFGDdata(fsFGDname.c_str());
	ofstream outPIDsFGDdata(foutPIDsFGDname.c_str());
	if (!PIDdata){
		cout<<fPIDname<<" doesn't exist!"<<endl;
		return -1;
	}
	if (!sFGDdata){
		cout<<fsFGDname<<" doesn't exist!"<<endl;
		return -1;
	}

	int numberOfSpills = 370;

	vector<double> PIDevents[numberOfSpills];
	vector<string> PIDparticles[numberOfSpills];
	vector<double> sFGDevents[numberOfSpills];

	for (int i = 0; i< numberOfSpills; i++){
		PIDevents[i].clear();
		PIDparticles[i].clear();
		sFGDevents[i].clear();
	}

	cout << "Taking events at "<< fPIDname<<endl;
	int SpillNumber = 0;
	double tempTime = 0;
	string tempPID = "";

    while (!PIDdata.eof()) {
    	PIDdata>>SpillNumber>>tempTime>>tempPID;
    	PIDevents[SpillNumber].push_back(tempTime);
    	PIDparticles[SpillNumber].push_back(tempPID);
    	//cout<<SpillNumber<<" "<<PIDevents[SpillNumber].back()<<" "<<PIDparticles[SpillNumber].back()<<endl;
    }
    cout << "Taking events at "<< fsFGDname<<endl;
    while (!sFGDdata.eof()) {
    	sFGDdata>>SpillNumber>>tempTime;
    	sFGDevents[SpillNumber].push_back(tempTime);
    	//cout<<SpillNumber<<" "<<sFGDevents[SpillNumber].back()<<endl;
    }

    for (int i = 1; i < numberOfSpills; i++){
    	int minSpill = min(sFGDevents[i].size(),PIDevents[i].size());
    	if (sFGDevents[i].size() != PIDevents[i].size()){
    	 	cout<<i<<" "<<minSpill<<" "<<sFGDevents[i].size()<<" "<<PIDevents[i].size()<<endl;
    	 	if (sFGDevents[i].size() != 0){
    	 		vector<double> tempPIDevents;
    	 		vector<double> tempsFGDevents;

    	 		tempPIDevents.clear();
    	 		tempsFGDevents.clear();

    	 		for (int k=0; k< PIDevents[i].size(); k++){
					tempPIDevents.push_back(PIDevents[i].at(k) - PIDevents[i].at(0));
				}

				cout<<tempPIDevents.size()<<endl;

    	 		if (i == 4 || i == 213){
    	 			for (int k = 0; k < tempPIDevents.size(); k++)
    	 				cout << setprecision(15) << tempPIDevents.at(k)<<endl;
    	 		}
    	 	}

    	} else {
    		for (int k = 0; k < minSpill; k++){
    			if (PIDparticles[i].at(k) != "x")
    				outPIDsFGDdata << i << " " << setprecision(15) << sFGDevents[i].at(k) << " " << PIDparticles[i].at(k) << endl;
    		}
    	}
    }



	return 0;
}