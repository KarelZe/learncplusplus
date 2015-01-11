#include<iostream>

using namespace std;

	long calculatePascal(int row, int position)
	{
	
		if (position ==row)
			{
			//right numbers
			return 1;
			}
		
		else if(position ==1)
			//left numbers
			{
			return 1;
			}
		else
		{
			//others
		return calculatePascal(row-1,position)+calculatePascal(row-1,position-1);
		}
			
	}

int main()
{
	unsigned int row=0;
	unsigned int position=0;
	
	
	cout<<"type in the position"<<endl;
	cin>>position;

	cout<<"type in the row"<<endl;
	cin>>row;
	
	if(row<position){
		//error treatment
		cout<<"Your entry is not valid"<<endl;
		return 0;	
		}

	
	cout<<"Your Result: "<<calculatePascal(row, position)<<endl;
	
}
