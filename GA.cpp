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

    Individual mate(Individual parent2)
    {
    	string offspring="";
    	int l=PERIODS*DAYS;

    	for(int i=0;i<l;i++)
    	{
    		int p=random_num(0, 100)/100;

    		if(p<0.45) offspring+=chromosome[i];
    		else if(p<0.9) offspring+=parent2.chromosome[i];
    		else offspring+=mutatedGene();
    	}

    	return Individual(offspring);
    }
};

void display(Individual bestoffspring)
{
	int l=PERIODS*DAYS;
	for(int i=0;i<l;i++)
	{
		if(i%PERIODS==0)
			cout<<endl;
		cout<<'\t'<<bestoffspring.chromosome[i];
	}
	cout<<"\n\tFitness : "<<bestoffspring.fitness<<endl;
}

bool cmp(Individual a, Individual b)
{
	return a.fitness < b.fitness;
}

int main()
{
	vector <Individual> population;

	for(int i=0;i<POPULATION_SIZE;i++)
	{
        string gnome=createGnome();
        population.push_back(Individual(gnome));
    }

    int gen=0, c=0;

    while(1)
    {
    	sort(population.begin(), population.end());

    	if(population[0].fitness<=0||c>=500) break;

    	vector <Individual> newGeneration;
    	int s=(10*POPULATION_SIZE)/100;
    	for(int i=0;i<s;i++)
    		newGeneration.push_back(population[i]);

    	s=POPULATION_SIZE-s;

    	for(int i=0;i<s;i++)
    	{
    		int rnum=random_num(0, 50);
    		Individual parent1=population[rnum];
    		rnum=random_num(0, 50);
    		Individual parent2=population[rnum];

    		Individual offspring=parent1.mate(parent2);

    		newGeneration.push_back(offspring);
    	}

    	sort(newGeneration.begin(), newGeneration.end());

    	if(newGeneration[0].fitness==population[0].fitness)
    		c++;
    	else c=0;
    	gen++;

    	population=newGeneration;
    }

    display(population[0]);
}