#include<iostream>
#include<cstdlib>
#include<cmath>
#include<iomanip>

using namespace std;

double randomNumber();

int main(){
double iteration;
double pi, x, y, result =0;


//Pre-Calculation
cout<<"Please set the number of iterations:"<<endl;
cin>>iteration;

//Calculation
for (int i; i<=iteration;i++)
	{
	
	 x =(double)rand()/RAND_MAX;
	 y= (double)rand()/RAND_MAX;	
		
			if (x*x+y*y<=1)
			
				result++;
	}

result=4*result/iteration;	
pi = atan(1)*4;
//output
cout<<"Thank you. Only "<<iteration<<" steps to go."<<endl;
cout<<result<<endl;
cout<<fixed<<setprecision(2)<<endl;
cout<<abs(pi-result)*100/pi<<"%"<<endl;
}
