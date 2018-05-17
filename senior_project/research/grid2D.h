
#include<iostream>
#include<fstream>
#include<queue> 
#include"senserGroup.h"
#include"linkedList.h"
using namespace std;

class grid2D
{
public:


	void setMinMax();
	void detect();
	void print();
	void set(senserGroup sen);

private:
	
	int d[10][10];
	linkedListType<int> thegrid[10][10];
	int SenNum[10][10];
	
	double min[2];
	double max[2];
	double jumper[2]; // the jumper is how much it will go from the 1st range to the 2nd
	
	int numOfSen;   // numer of dimesnions, and number of sensors
	int numOfDim;
};


void grid2D::detect()
{
	int i, j;
	int I, J;
	int maxCell = 0;

	for(i=0; i<10; i++)
		for(j=0; j<10; j++)
			d[i][j] = 0;
	
	for(i=0; i<10; i++)
	{
		for(j=0; j<10; j++)
		{
			if(SenNum[i][j] > maxCell && d[i][j] < 1 && d[i][j] < 1)
			{
				I = i;
				J = j;
				maxCell = SenNum[i][j];
			}
		}
	}
	
	if(I>0)
	{
		if(J>0)
			d[I-1][J-1] = 1;
		d[I-1][J] = 1;
		if(J<9)
			d[I-1][J+1] = 1;
	}
	d[I][J] = 1;
	if(J>0)
		d[I][J-1] = 1;
	if(J<9)
		d[I][J-1] = 1;
	if(I<9)
	{
		if(J>0)
			d[I+1][J-1] = 1;
		d[I+1][J] = 1;
		if(J<9)
			d[I+1][J+1] = 1;
		
	}



		cout<<endl;
		cout<<maxCell<<endl;
}


void grid2D::set(senserGroup sen)
{
	nodeType<double> *p;
	int i, j, k;
	double check;
	double** num;


	numOfSen = sen.getSen();
	numOfDim = 2;
	num = new double *[numOfSen];
	for(i=0; i<numOfSen; i++)
		num[i] = new double[2];

	for(i=0; i< numOfSen; i++)
		for(j=0; j<numOfDim; j++)
		{
			p =  sen.sensers[i].first;
			for(k=0; k<j; k++)
				p = p->link;
			num[i][j] = p->info;
			
		}

	for(i=0; i< numOfSen; i++)
			cout<<num[i][0]<<" "<<num[i][1]<<endl;
	
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
	int ID[2];
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
		
	
		thegrid[ID[0]][ID[1]].insertFirst(i);
	}
	


}

void grid2D::print()
{
	ofstream fout;
	fout.open("data.txt");
	int i,j;
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
		for(j=0; j<10; j++)	
		{
			
				counter=0;
				cout<<"#"<<i<<"and #"<<j<<" this grid2D has the sensors"<<endl;
				fout<<"#"<<i<<"and #"<<j<<" this grid2D has the sensors"<<endl;
				p = thegrid[i][j].first;
			
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
			SenNum[i][j] = counter;

		
			}

		cout<<endl;
		for(i=0; i<10; i++)
		{
			for(j=0; j<10; j++)
			{
				cout<<SenNum[i][j]<<" ";
			}
			cout<<endl;
		}
		

}
