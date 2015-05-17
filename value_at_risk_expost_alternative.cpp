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
	
	//link to the path. raw data is downloaded from google finance.
	ifstream datei("C:\\Users\\Studio\\Desktop\\value at risk\\Rohdaten\\googl.csv");	
	
	string line;
	int confidenceLevel;
	double quantile, mean=0, variance=0, valueAtRisk;
	 int lineAmount=0, days;
	
	vector<double>closeVector(0);

	//cin for confidence level using int's to allow easier comparsion in whileloop
	
	do
	{
	cout<<"Please type in 1 for 0.90, 2 for .95 and 3 for .99"<<endl;
	cin>>confidenceLevel;		
	}
	//exception handling
	while(confidenceLevel>3 || confidenceLevel<1);

	/*
	Multiply with quantile of standardised normal distribution, taken from:
	http://www.vwi.tu-dresden.de/~treiber/statistikFormelnTabellen/erf_quantile.pdf
	*/
	
	switch(confidenceLevel){
	
	case 1:
	quantile = 1.2816;
	
	break;
	case 2:
	quantile = 1.6449;
	
	break;	
	case 3:
	quantile = 2.3263;
	
	break;
	
	
	}
	
	do
	{
	cout<<"Please type in the holding period in days"<<endl;
	cin>>days;		
	}
	//exception handling, in most cases it will be 1, 10, 63 or 250 days
	while(days>999 || days<1);
	
	bool skipFirstLine=true;
	
	//parse document
	while(getline(datei, line))
	{
	if(!datei)
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
	
	
	stringstream linebuffer(line);
	
	string date;
	int volume;
	double open, high, low, close;
	
	linebuffer >> date >> open >>high >> low>>close>>volume;
	
	closeVector.resize(closeVector.size()+1);
	closeVector.at(lineAmount)=close;
	lineAmount++;
			
	}
	//expost calculation, create new vector where to store daily difference.
	vector<double>difference(lineAmount-1);
	for(int i=1;i<lineAmount;i++){
	difference.at(i-1)=(closeVector.at(i)-closeVector.at(i-1))/closeVector.at(i)*-100.0;
	}
	
	for(int i=0;i<=difference.size();i++){
	mean+=difference[i];
	variance+=(difference[i]*difference[i]);
	}

	mean/=difference.size();
	variance=variance/difference.size()-mean*mean;
	
	//Scale to "holding period", calculate standard deviation from variance
	valueAtRisk= sqrt(variance)*quantile*sqrt(days);
		
	//output value at risk expost
	cout<<"Your value at risk expost at a holding period of "<<days<<" day(s) "<<valueAtRisk<<" %"<<endl;

	system("pause");
	}
