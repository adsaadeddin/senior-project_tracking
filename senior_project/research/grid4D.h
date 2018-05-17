#include<iostream>
#include<fstream>
#include"senserGroup.h"
#include"linkedList.h"
using namespace std;

class grid4D
{
public:
	void set(senserGroup sen);

	void setMinMax();
	void print();

private:
	

	linkedListType<int> thegrid[10][10][10][10];
	
	double min[4];
	double max[4];
	double jumper[4]; // the jumper is how much it will go from the 1st range to the 2nd
	
	int numOfSen;   // numer of dimesnions, and number of sensors
	int numOfDim;
};


void grid4D::set(senserGroup sen)
{
	nodeType<double> *p;
	int i, j, k;
	double check;
	double** num;


	numOfSen = sen.getSen();
	numOfDim = 4;
	num = new double *[numOfSen];
	for(i=0; i<numOfSen; i++)
		num[i] = new double[4];

	for(i=0; i< numOfSen; i++)
		for(j=0; j<numOfDim; j++)
		{
			p =  sen.sensers[i].first;
			for(k=0; k<j; k++)
				p = p->link;
			num[i][j] = p->info;
			
		}

	for(i=0; i< numOfSen; i++)
			cout<<num[i][0]<<" "<<num[i][1]<<" "<<num[i][2]<<" "<<num[i][3]<<endl;
	
	for(i=0; i<numOfDim; i++)
	{
		min[i] = 10000000;
		max[i] = 0;
	}

	for(i=0; i<numOfDim; i++)
	{
		for(j=0; j<numOfSen; j++)
		{
			p = sen.sensers[j].first;
			for(k=0; k<i; k++)
				p = p->link;

			if( min[i] > p->info)
				min[i] = p->info;
			if(max[i] < p->info)
				max[i] = p->info;
		}

		jumper[i] = ((max[i] - min[i])/10);
		
	}

	for(i=0; i<numOfDim; i++)
	{
		cout<<"min#:"<<i+1<<" : "<<min[i]<<endl;
		cout<<"max#:"<<i+1<<" : "<<max[i]<<endl;
		cout<<"jumper#"<<i+1<<" : "<<jumper[i]<<endl;
	}
	bool fine = false;
	int ID[4];
	for(i=0; i<numOfSen; i++)
	{
		for(j=0; j<numOfDim; j++)
		{
			fine = false;
			check = min[j];
			ID[j] = 0;
			while(!fine)
			{
				
				if( num[i][j] >= check && num[i][j] <= (check+jumper[j]))
				{	cout<<ID[j]<<" "<<endl;
					fine = true;
				}
				else
				{
					check+=jumper[j];
					ID[j]++;
				}
			}
		}
		
		
	
		thegrid[ID[0]][ID[1]][ID[2]][ID[3]].insertFirst(i);
	}
	


}

void grid4D::print()
{
	ofstream fout;
	fout.open("data.txt");
	int i;
	for(i =0; i< numOfDim; i++)
	{
		cout<< "for Dimension #"<<i+1<<endl;
		cout<<"min ="<<min[i]<<endl;
		cout<<"max ="<<max[i]<<endl;
		cout<<"jumper ="<<jumper[i]<<endl;
	}
	nodeType<int> *p;
	int counter;

	for(i=0; i<10; i++)
		for(int j=0; j<10; j++)	
			for(int k=0; k<10; k++)
				for(int l=0; l<10; l++)
				{
					counter=0;
					cout<<"#"<<i<<"and #"<<j<<" and #"<<k<<" and #"<<l<<"this cell has the sensors"<<endl;
					fout<<"#"<<i<<"and #"<<j<<" and #"<<k<<" and #"<<l<<"this cell has the sensors"<<endl;
					p = thegrid[i][j][k][l].first;
					while(p != NULL)
					{
						cout<<p->info<<" ";
						fout<<p->info<<" ";
						p = p->link;
						counter++;
					}
				cout<<endl;
				fout<<endl;
				cout<<"the number of sensors in this part is : "<<counter<<endl;
				fout<<"the number of sensors in this part is : "<<counter<<endl;

		
				}
}
