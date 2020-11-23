#include <bits/stdc++.h> 
using namespace std; 
#define POPULATION_SIZE 100 
int dna[500],vis[500]={0}; 
float c,s[500][500],d[500][500];
int t,k,m,n;

int randnum(int a, int b) 
{ 
    int r1 = (b-a)+1; 
    int r = a+(rand()%r1); 
    return r; 
} 

int mutated_dna() 
{  
	int r = randnum(0,n-1); 
    for(int i=0;i<n;i++)
	{if(r-i>=0 && vis[r-i]==0)
     {vis[r-i]++;return dna[r-i];}
	 else if(r+i<n && vis[r+i]==0)
	 {vis[r+i]++;return dna[r+i];}
	}
	return -1;
} 
  
vector<int> create_gnome() 
{ 
    for(int i=0;i<n;i++)
    vis[i]=0;
	vector<int> gnome; 
    for(int i=0;i<n;i++) 
        gnome.push_back(mutated_dna()); 
    return gnome; 
} 
  
class Individual 
{ 
public: 
    vector<int> chromosome; 
    float goodness;
    Individual(vector<int> chromosome); 
    Individual mate(Individual parent2); 
    float cal_goodness(); 
}; 
  
Individual::Individual(vector<int> chromosome) 
{ 
    this->chromosome = chromosome; 
    goodness = cal_goodness();  
}
  
Individual Individual::mate(Individual par2) 
{ 
    for(int i=0;i<n;i++)
    vis[i]=0;
	vector<int> child_chromosome; 
    for(int i=0;i<n;i++) 
    { 
        float p = randnum(0, 100)/(100.0); 
        //cout<<p<<endl;
        if(p < 0.45 && vis[chromosome[i]-1]==0) 
           {child_chromosome.push_back(chromosome[i]);vis[chromosome[i]-1]++;} 
  
        else if(p>=0.45 && p < 0.90 && vis[par2.chromosome[i]-1]==0) 
            {child_chromosome.push_back(par2.chromosome[i]);vis[par2.chromosome[i]-1]++;} 
  
        else
            child_chromosome.push_back(mutated_dna()); 
    } 
    return Individual(child_chromosome); 
}
  
float Individual::cal_goodness() 
{ 
    int a[t*k][m];
	for(int i=0;i<n;i++)
	a[k*(i/(m*k))+(i%k)][(i%(m*k))/k]=chromosome[i];
	float sum=0;
	for(int u=0;u<t;u++)
		for(int r=0;r<m;r++)
			for(int i=0;i<k;i++)
			{
				for(int j=i+1;j<k;j++)
				sum+=s[a[u*k+i][r]-1][a[u*k+j][r]-1];
				
				for(int e1=r+1;e1<m;e1++)
				for(int e2=0;e2<k;e2++)
				sum+=c*d[a[u*k+i][r]-1][a[u*k+e2][e1]-1];
			}
	return sum;
}

bool sortByGoodness(const Individual &ind1, const Individual &ind2) 
{ 
    return (ind1.goodness < ind2.goodness); 
} 


    
int main() 
{ 
    srand((unsigned)(time(0))); 
    cin>>k>>m>>t>>c;
	n=m*t*k;
	float max_val=0;
	vector<int> ans; 

	for(int i=0;i<n;i++)
	dna[i]=i+1; 
	for(int i=0;i<n;i++)
	for(int j=0;j<n;j++)
	{
		cin>>d[i][j];
		s[i][j]=1-d[i][j];
	}
	 
    long long flag=0;
    vector<Individual> population; 
    
    for(int i=0;i<POPULATION_SIZE;i++) 
    { 
        vector<int> gnome = create_gnome(); 
        population.push_back(Individual(gnome));
    } 
  
    while(flag++<1000) 
    { 
        sort(population.begin(),population.end(),sortByGoodness); 
  		vector<Individual> new_generation; 
  		ans=population[POPULATION_SIZE-1].chromosome;
  		max_val=population[POPULATION_SIZE-1].goodness;
        int s = (10*POPULATION_SIZE)/100; 
        for(int i= 0;i<s;i++) 
        	new_generation.push_back(population[POPULATION_SIZE-1-i]); 
  		s = (90*POPULATION_SIZE)/100; 
        for(int i = 0;i<s;i++) 
        { 
            int r = randnum(0, 50); 
            Individual parent1 = population[POPULATION_SIZE-1-r]; 
            r = randnum(0, 50); 
            Individual parent2 = population[POPULATION_SIZE-1-r]; 
            Individual offspring = parent1.mate(parent2); 
            if(offspring.goodness>max_val)
            {
            	max_val=offspring.goodness;
            	ans=offspring.chromosome;
			}
            new_generation.push_back(offspring);  
        } 
        population = new_generation; 
     } 
    int a[t*k][m];
	for(int i=0;i<n;i++)
	a[k*(i/(m*k))+(i%k)][(i%(m*k))/k]=ans[i];
	for(int j=0;j<m;j++)
	{for(int i=0;i<k*t;i++)
	{if(i!=0 && i%k==0)
	cout<<"| ";
	cout<<a[i][j]<<" ";}
	cout<<endl;}
    //cout<< "\nGoodness: "<< max_val; 
} 

