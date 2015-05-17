//Method according to Chp. "III. Ermittlung des Value at Risk mit Simulationsverfahren, Historische Simulation

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include<vector>
#include<iomanip>
#include<cmath>


using namespace std;

int main(){
	
	//link to the path. raw data is downloaded from google finance. remove first line of document
	ifstream file("C:\\Users\\Studio\\Desktop\\value at risk\\Rohdaten\\ifnny.csv");	
	
	string line;
	int confidenceLevel=0, lineAmount=0;
	double step=0,  valueAtRisk=0;
	vector<double>closeVector(0);
	//cin for confidence level using int's to allow easier comparsion in whileloop
	do
	{
		cout<<"Please type in 1 for 0.90, 2 for .95 and 3 for .99"<<endl;
		cin>>confidenceLevel;		
	}
	//exception handling
	while(confidenceLevel>3 || confidenceLevel<1);
	
	switch(confidenceLevel){
	
	case 1:
	step = 0.1;
	
	break;
	case 2:
	step= 0.05;
	
	break;	
	case 3:
	step = 0.01;
	
	break;
	
	}
	
	
	bool skipFirstLine=true;
	//parse document
	while(getline(file, line))
	{
	if(!file)
        break;	
    //Skip the first line, First line contains name of rows   
	if(skipFirstLine){
		skipFirstLine = !skipFirstLine;
		continue;		
	}

	

		
	for (int i=0;i<line.size();i++)
	{
	
	
		replace(line.begin(),line.end(), ',', ' ');
		replace(line.begin(),line.end(), '\t', ' ');
		replace(line.begin(),line.end(), ';', ' ');
	}
	
	
	stringstream lineBuffer(line);
	
	string date;
	int volume;
	double open, high, low, close;
	
	lineBuffer >> date >> open >>high >> low>>close>>volume;
	
	closeVector.resize(closeVector.size()+1);
	closeVector.at(lineAmount)=close;
	lineAmount++;
			
	}
	//expost calculation, create new vector where to store daily difference. Calculate yield, calculate price difference on acutal niveau
	vector<double>difference(lineAmount-1);
	for(int i=1;i<lineAmount;i++){
		difference.at(i-1)=exp(log(closeVector.at(i-1)/closeVector.at(i)))-1;
		difference.at(i-1)= difference.at(i-1)*closeVector.at(0);
	}
		
	//sort with descending order
	sort(difference.begin(), difference.end());
	
	//round down--> risk will be overestimated, otherwise use ceil, then cast to int
	step = floor(step*difference.size());
		
	valueAtRisk=difference.at((int)step);
	
	//output value at risk expost
	cout<<"Your value at risk expost at the chosen confidence level per stock: $ "<<fixed<<setprecision(2)<<-valueAtRisk<<endl;

	system("pause");
	
	}
