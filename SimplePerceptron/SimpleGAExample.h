#ifndef SIMPLE_GA_EXAMPLE_H
#define SIMPLE_GA_EXAMPLE_H


#include "Utils.h"
#include "SimpleExample.h"
#include "SimpleGA.h"


#include <iostream>
#include <vector>
#include <string>

using std::vector;

using namespace SIMPLE_GA;

class SimpleGA : public SimpleExample
{
public:

	int population_size = 100;

	char* target = "to be or not to be";
	float mutationRate = 0.01;


	Population population3;

	void SetPopulationSize(int n){ this->population_size = n; }

	void Initialize()
	{
		//population = new DNA*[population_size];
		population3.Initialize();
		/*for (int i = 0; i < population_size; i++) {
			//Initializing each member of the population

			DNA* dna = new DNA();
			dna->num_genes = 18;
			dna->Initialize();
			dna->SetTarget(target);
			population2.push_back(dna);

	//		population[i] = dna;// new DNA();
			//population[i]->num_genes = 18;
			//population[i]->Initialize();
			//population[i]->SetTarget(target);
		}
		*/

	}


	void Draw() {
		static bool solved = false;
		if (solved == false)
		{
			population3.Update();
			/*	for (int i = 0; i < population2.size(); i++) {
					//population[i]->Fitness();
					population2[i]->Fitness();
					}

					std::vector<DNA*> mating_pool;
					mating_pool.clear();

					int best = 0;
					int best_index = 0;
					for (int i = 0; i < population2.size(); i++) {

					//n is equal to fitness times 100, which leaves us with an integer between 0 and 100.

					int n = int(population2[i]->fitness * 100);
					if (n > best) {
					best = n;
					best_index = i;
					}
					for (int j = 0; j < n; j++) {
					//	Add each member of the population to the mating pool N times.
					mating_pool.push_back(population2[i]);
					}
					}

					char best_string[19];
					//strcpy_s(best_string, population[best_index]->genes);
					for (int i = 0; i < 18; i++)
					best_string[i] = population2[best_index]->genes[i];


					for (int i = 0; i < population2.size(); i++) {
					int a = int(RandomInt(0, mating_pool.size()-1));
					int b = int(RandomInt(0, mating_pool.size()-1));
					if (a == b){ if (a < mating_pool.size()-2)b = a + 1; else b = 0; }
					DNA *partnerA = mating_pool[a];
					DNA *partnerB = mating_pool[b];
					//Step 3a: Crossover
					//DNA *child = partnerA->crossover(partnerB);
					population2[i]->crossover2(partnerA, partnerB);
					//Step 3b: Mutation

					population2[i]->mutate(mutationRate);

					//Note that we are overwriting the population with the new children.When draw() loops, we will perform all the same steps with the new population of children.
					//delete population2[i];
					//population[i] = child;
					}
					mating_pool.clear();*/
			static int generation_count = 0;
			std::cout << "generation" << generation_count++ << ", best answer: " << population3.GetBest() << std::endl;

			if (population3.best_fitness > 0.9f)solved = true;
		}
	}

	void keyboard(unsigned char key, int x, int y){}
	void keyboardup(unsigned char key, int x, int y){}
	void Special(int key, int x, int y){};
	void reshape(GLsizei width, GLsizei height){}
	void mouse(int button, int state, int x, int y){}

	void Delete(){
/*		for (int i = 0; i < population_size; i++)
		{
			delete population2[i];
			population2[i] = 0;
		}

		population2.clear();
		*/
		population3.Delete();
		//mating_pool.clear();
		this->m_bDeleted = true;

	}
};

#endif