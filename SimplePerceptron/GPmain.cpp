// SimplePerceptron.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include <iostream>

#include <windows.h>  // for MS Windows
#include "Utils.h"
#include "SimpleGAExample.h"
#include "GeneticProgramming.h"
#include "AST.h"



int width = 640;
int height = 480;



/*=================================================================
GLUT FUNCTIONS
=================================================================*/

















/*=================================================================
Main
=================================================================*/

int _tmain(int argc, char* argv[])
{
	srand(10);   /// TWEAK


	/*=================================================================
	tests of the parser, lexer, ast builder and REPL
	=================================================================*/
	string s2 = "x%y;";
	string s4 = "if ((m eq 1) and((n eq 2) or(mm eq 10))) then((x = sqrt(sin(y + 5.25))) and(t = 1)); ";
	string s5 = "if (m eq 1) then(x = sqrt(sin(y + 5.25))) else (x = 5); ";
	//string s3 = strSplit(s4);

	SimpleScript simple_script;
	simple_script.arrayInfixExpression = simple_script.strSplit(simple_script.strInfixExpression);

//	cout << "s3: " << s3 << endl;
	simple_script.parse();

	std::vector<std::string> x = split("one:two::three", ':');
	
	cout << "-------------------------------------------" << endl;
	cout << "printing array postfix expression" << endl;
	for (int i = 0; i < simple_script.arrayPostfixExpression.size(); i++) std::cout << simple_script.arrayPostfixExpression[i] << " ";// std::endl;
	cout << endl<<"-------------------------------------------" << endl;

	vector<string> output = simple_script.postfixEvaluateList(simple_script.arrayPostfixExpression);
	vector<ASTNode*> node_stack = simple_script.postfixEvaluateListTree(simple_script.arrayPostfixExpression);

	simple_script.abstractTree->root = (OperatorNode*)node_stack[0];
	
	cout << endl << endl << endl << endl;
	cout << "Attempting to print Tree from input expression:..."<<endl;
	simple_script.abstractTree->PrintTree(simple_script.abstractTree->root);
	cout << endl << endl << "Attempting to set some values, x=3, y=4 (expecting the value z=5)" << endl;
	simple_script.abstractTree->SetTerminalValue("x", 3.0);
	simple_script.abstractTree->SetTerminalValue("y", 4.0);
	cout<< endl<<endl<<"x=3, y=4, value = "<< simple_script.abstractTree->root->value();
	cout << endl << endl << endl << endl;

	for (int i = 0; i < output.size(); i++) {
		cout << "**********************" << endl << output[i] << endl;
		if (output[i] == "ADD")
		{
			cout << "create ADD node" << endl;
		}
		if (output[i] == "MUL")
		{
			cout << "create ADD node" << endl;
		}

	}
	


	/*=================================================================
	test of the now redundant binary tree 
	=================================================================*/

	SimpleBinaryTree binaryTree;
	binaryTree.Insert(2);
	binaryTree.Insert(3);
	binaryTree.Insert(1);
	binaryTree.Insert(5);
	binaryTree.Insert(7);
	binaryTree.Insert(5);
	binaryTree.Insert(3);
	binaryTree.Insert(2);
	binaryTree.Insert(1);
	binaryTree.Insert(8);
	 
	binaryTree.TraverseInorder(binaryTree.root);

	cout << "**************************************************************" << endl;
	

	ASTPopulation *ast_population = new ASTPopulation();
	ast_population->SetPopulationSize(1000);   // TWEAK       : trying different population sizes can help

	ast_population->SetProbabilities(0.5, 0.3, 0.2);   // TWEAK    : note I actually need to breed the best tweak or change these over time
	ast_population->AddTerminal("x", false);
	ast_population->AddTerminal("y", false);


	/*
	Generating a random set of samples to produc a curve that is solved by pythagoras theorem (or something)
	*/
	for (int i = 0; i < 20; i++) // TWEAK    : adding more samples 
	{
		
		
		double x1, y1, a;
		//===============================================
		fitness_sample samp;
		x1 = RandomFloat(1, 40.0); y1 = RandomFloat(1, 40.0);
		a = 0.0;
		samp.terminal_values.push_back(x1);
		samp.terminal_values.push_back(y1);
		//samp.terminal_values.push_back(a);
		samp.training_sample = sqrt(x1*x1 + y1*y1);

		ast_population->terminal_fitness_values.push_back(samp);
	}

	ast_population->generatePopulation();



	for (int epoch = 0; epoch < 200; epoch++)
	{
		ast_population->compute_sample_values();
		
		AST * best_tree = ast_population->population[ast_population->the_best];
		ASTNode *best_root = best_tree->root;
		best_tree->PrintTree(best_root);   // TWEAK:   consider algebraic reduction on this
		cout << "Best Current Score: " << ast_population->current_best_score << endl;
		cout << endl << endl;
		cout << "result with x=3, y=4 : ";
		ast_population->SetTerminalValue("x", 3.0);
		ast_population->SetTerminalValue("y", 4.0);
		cout<< best_tree->root->value();   // evaluate the expression with given inputs, this won't always be closest to 5
		cout << endl << endl;
		cout << "SumFitness: " << ast_population->sumFitness << endl;
		
		ast_population->Breed();
		
	}
	
	delete ast_population;

	cout << "**************************************************************" << endl;
	 

	// this is still left over from previous work

	






	

	return 0;
}

