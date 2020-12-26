#include<bits/stdc++.h>

using namespace std;

#define POPULATION_SIZE 100
#define SUBJECTS_SIZE 6
#define PROFESSORS_SIZE 3
#define PERIODS 6
#define DAYS 5

const string SUBJECTS="ABCDEF";
const string PROFESSORS="xyz";
const string MAP="yxxzyx";

const int SUB[SUBJECTS_SIZE]={7,3,6,4,5,5};
const int PROF[PROFESSORS_SIZE]={13,12,5};

class Individual
{
    public:

    string chromosome;
    int fitness;
};

void display(vector <Individual> population)
{
	int l=PERIODS*DAYS;
	for(int i=0;i<l;i++)
	{
		if(i%PERIODS==0)
			cout<<endl;
		cout<<'\t'<<population[0].chromosome[i];
	}
	cout<<"\n\tFitness : "<<population[0].fitness<<endl;
}

int main()
{
	vector<Individual> population;
}