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

int random_num(int start, int end)
{
    int range=end-start+1;

    return start+(rand()%range);
}

char mutatedGene()
{
    int l=SUBJECTS_SIZE;
    int r=random_num(0, l-1);

    return SUBJECTS[r];
}

string createGnome()
{
    int l=PERIODS*DAYS;
    string gnome="";
    for(int i=0;i<l;i++)
        gnome+=mutatedGene();

    return gnome;
}

class Individual
{
    public:

    string chromosome;
    int fitness;

    Individual(string str)
    {
        chromosome=str;
        fitness=calcFitness();
    }

    int conflictSubHours()
    {
    	int l=PERIODS*DAYS, conflicts=0;

        for(int i=0;i<SUBJECTS_SIZE;i++)
        {
            int c=0;
            char sub=SUBJECTS[i];

            c=count(chromosome.begin(), chromosome.end(), sub);

            conflicts+=abs(c-SUB[i]);
        }

        return conflicts;
    }

    int conflictSubCont()
    {
    	int l=PERIODS*DAYS, conflicts=0;

    	for(int i=0;i<l-1;i++)
    		if(chromosome[i]==chromosome[i+1])
    			conflicts++;

    	return conflicts;
    }

    int calcFitness()
    {
        int fitness=0;
        fitness+=conflictSubHours();
        fitness+=conflictSubCont();
        
        return fitness;
    }
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
	vector <Individual> population;

	for(int i=0;i<POPULATION_SIZE;i++)
	{
        string gnome=createGnome();
        population.push_back(Individual(gnome));
    }

    bool found=false;
}