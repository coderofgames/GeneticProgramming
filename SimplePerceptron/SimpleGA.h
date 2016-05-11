#ifndef SIMPLE_GA_H
#define SIMPLE_GA_H

#include "Utils.h"
#include <iostream>
#include <vector>
#include <string>

using std::vector;

namespace SIMPLE_GA {


	class DNA
	{
	public:



		char *genes;// = new char[18];
		char *target;
		int num_genes = 18;

		float fitness;

		DNA()
		{

		}

		void SetTarget(char* buff)
		{
			bool check = false; // don#t bother 
			if (check)
			{
				int sz = sizeof(buff);
				if (sz != num_genes) return;
			}

			for (int i = 0; i < num_genes; i++)
				target[i] = buff[i];

		}

		void Initialize()
		{
			genes = new char[num_genes];
			target = new char[num_genes];

			for (int i = 0; i < num_genes; i++) {
				//Picking randomly from a range of characters with ASCII values between 32 and 128. For more about ASCII : http ://en.wikipedia.org/wiki/ASCII
				genes[i] = (char)RandomInt(32, 128);
			}
		}


		void Fitness() {
			int score = 0;
			for (int i = 0; i < num_genes; i++) {
				//Is the character correct ?
				if (genes[i] == target[i]) {
					//If so, increment the score.
					score++;
				}
			}
			//Fitness is the percentage correct.
			fitness = float(score) / (float)num_genes;
			//fitness = fitness * fitness;
		}

		DNA* crossover(DNA *partner) {
			DNA *child = new DNA();
			child->num_genes = this->num_genes;
			child->Initialize();
			child->SetTarget(this->target);
			int midpoint = int(RandomInt(0, num_genes));
			for (int i = 0; i < num_genes; i++) {
				if (i > midpoint) child->genes[i] = genes[i];
				else   {
					if (partner != 0)
						child->genes[i] = partner->genes[i];
				}
			}
			return child;
		}


		void crossover2(DNA *partnerA, DNA* partnerB) {

			//child->num_genes = this->num_genes;
			//child->Initialize();
			//child->SetTarget(this->target);
			this->fitness = 0.0f;

			int midpoint = int(RandomInt(0, num_genes));
			for (int i = 0; i < num_genes; i++) {
				if (i > midpoint) genes[i] = partnerA->genes[i];
				else   {
					if (partnerB != 0)
						genes[i] = partnerB->genes[i];
				}
			}
		}

		//Mutation
		void mutate(float mutationRate) {
			for (int i = 0; i < num_genes; i++) {
				if (RandomFloat(0.0, 1.0) < mutationRate) {
					genes[i] = (char)RandomInt(32, 128);
				}
			}
		}
	};

	class Population
	{
	public:

		vector<DNA*> population;
		unsigned int population_size = 200;

		float mutationRate = 0.03;

		float sumFitness;

		float best_fitness = 0.0f;
		int best_index = 0;

		bool match = false;

		char* target = "to be or not to be";

		Population()
		{

		}

		Population(int sz){
			population_size = sz;
		}

		std::string  GetBest()
		{
			std::string the_best(population[best_index]->genes);

			return the_best;
		}
		void Initialize()
		{
			for (int i = 0; i < population_size; i++) {
				//Initializing each member of the population

				DNA* dna = new DNA();
				dna->num_genes = 18;
				dna->Initialize();
				dna->SetTarget(target);
				population.push_back(dna);


			}
		}


		void Old_Breeding()
		{
			std::vector<DNA*> mating_pool;
			
			int best = 0;
			int best_index = 0;
			for (int i = 0; i < population.size(); i++) {

				//n is equal to fitness times 100, which leaves us with an integer between 0 and 100.

				int n = int(population[i]->fitness * 100);
				if (n > best) {
					best = n;
					best_index = i;
				}
				for (int j = 0; j < n; j++) {
					//	Add each member of the population to the mating pool N times.
					mating_pool.push_back(population[i]);
				}
			}

			char best_string[19];
			//strcpy_s(best_string, population[best_index]->genes);
			for (int i = 0; i < 18; i++)
				best_string[i] = population[best_index]->genes[i];


			for (int i = 0; i < population.size(); i++) {
				int a = int(RandomInt(0, mating_pool.size() - 1));
				int b = int(RandomInt(0, mating_pool.size() - 1));
				if (a == b){ if (a < mating_pool.size() - 2)b = a + 1; else b = 0; }

				// crossover
				// mutation
				// etc
			}
			mating_pool.clear();
		}

		int ChooseParent()
		{
			int randSelector = (int)RandomFloat(0, sumFitness) * 100;

			// Translate this number to the corresponding member**
			int memberID = 0;
			int partialSum = 0;

			for (int i = 0; i < population.size(); i++) {
				int n = (int)(population[i]->fitness * 100);
				if (partialSum < randSelector && partialSum + n >= randSelector)
				{
					return i;
				}
				partialSum += n;
				/*			for (int j = 0; j < n; j++)
				{
				partialSum += 1;
				if (partialSum == randSelector)
				{
				return i;
				}
				}*/
			}

			int alternate = RandomInt(0, 99);

			return this->best_index;

			/*while (randSelector  > partialSum)
			{
			partialSum += population[memberID]->fitness;// / sumFitness;// fitness(memberID);
			memberID++;
			}*/

			//return memberID;
		}

		void Update()
		{
			best_fitness = 0.0f;
			sumFitness = 0.0f;
			//evaluate fitness
			for (int i = 0; i < population.size(); i++) {
				//population[i]->Fitness();
				population[i]->Fitness();

				sumFitness += population[i]->fitness;

				if (population[i]->fitness > best_fitness)
				{
					best_fitness = population[i]->fitness;
					best_index = i;
				}
			}

			// Find the sum of fitnesses. The function fitness(i) should 
			//return the fitness value   for member i**


			//for (int i = 0; i < nmembers; i++)
			//	sumFitness += fitness(i);


			// Get a floating point number in the interval 0.0 ... sumFitness**
			//float randomNumber = (float(rand() % 10000) / 9999.0f) * sumFitness;




			for (int i = 0; i < population.size(); i++) {
				//int a = int(RandomInt(0, mating_pool.size() - 1));
				//int b = int(RandomInt(0, mating_pool.size() - 1));
				//if (a == b){ if (a < mating_pool.size() - 2)b = a + 1; else b = 0; }
				//if (population[i]->fitness  > 0.8) continue;

				if (i == this->best_index) continue;

				int a = this->ChooseParent();
				int b = this->ChooseParent();

				if (a == b) if (a <= population.size() - 2)b = a + 1; else b = 0;

				DNA *partnerA = population[a];
				DNA *partnerB = population[b];

				//Step 3a: Crossover
				//DNA *child = partnerA->crossover(partnerB);
				population[i]->crossover2(partnerA, partnerB);
				//Step 3b: Mutation

				population[i]->mutate(mutationRate);


			}
		}


		void Delete()
		{
			for (int i = 0; i < population.size(); i++)
			{
				delete population[i];
				population[i] = 0;
			}

			population.clear();
		}
	};
};
#endif