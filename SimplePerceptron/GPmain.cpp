// SimplePerceptron.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include <iostream>

//#include "SimplePerceptron.h"

#include <windows.h>  // for MS Windows
//#include <GL/glut.h>  // GLUT, include glu.h and gl.h

#include "Utils.h"

#include "SimpleGAExample.h"



//#include "SimplePlot3d.h"
//#include "SimpleTextExample.h"

//#include "TranslatedTextExample.h"
//#include "AdvancedPlot2DTickLabels.h"


SimpleExample *example;

int width = 640;
int height = 480;// 360;




void cleanup()
{
	example->Delete();
}


void setup() {
	
	example = new  SimpleGA();

}


void draw() {		
	example->Draw();

	//glFlush();  // Render now
	//glutPostRedisplay();
}

/* Handler for window re-size event. Called back when the window first appears and
whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
	// Compute aspect ratio of the new window
	example->reshape(width, height);
}
void display() {
//	float faspect = (float)width / (float)height;
	//Sleep(10);
	draw();
	//glutPostRedisplay();
}


void mouse(int button, int state, int x, int y)
{
	/*if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		exit(0);
	}*/
	example->mouse(button, state, x, y);
}


void keyboard(unsigned char key, int x, int y)
{
	example->keyboard(key, x, y);
}

void keyboardup(unsigned char key, int x, int y)
{
	example->keyboardup(key, x, y);
}

void special(int key, int x, int y) {

	example->Special(key, x, y);

	/*
	if (
	modifiers ==
	(GLUT_ACTIVE_CTRL | GLUT_ACTIVE_ALT))
	{
	cout << "Pressed Insert " <<
	"with only Ctrl and Alt" << endl;
	}
	The above approach will cause a message to be displayed if ONLY the ctrl and alt keys have been held.

	If we do not mind if other keys are held in addition, we can use the AND(&) operator as shown below. Here you can hold down all 3 modifiers and the message will still be displayed.

	else if (modifiers & GLUT_ACTIVE_CTRL &&
	modifiers & GLUT_ACTIVE_ALT)
	{
	cout << "Pressed Insert " <<
	"with Ctrl and Alt" << endl;
	}
	*/
	//glutPostRedisplay();
}

int init_resources(void)
{
	example->Initialize();

	return 1;
}









#include "SimpleScript.h"


class BinaryTreeNode
{
public:
	BinaryTreeNode(){
		data = 0;
		left = right = 0;
	}

	void Visit(){
		cout << "Visiting This: " << data << endl;
	}

	void Insert(int dat)
	{
		if (dat > data)
		{
			if (right)
			{
				right->Insert(dat);
			}
			else
			{
				right = new BinaryTreeNode();
				right->data = dat;
			}
		}
		else
		{
			if (left)
			{
				left->Insert(dat);
			}
			else
			{
				left = new BinaryTreeNode();
				left->data = dat;
			}
		}
	}

	int data;

	BinaryTreeNode *left;
	BinaryTreeNode *right;
};

class SimpleBinaryTree
{
public:
	SimpleBinaryTree()
	{
		root = 0;
	}
	void Insert(int data)
	{
		if (root)
		{
			root->Insert(data);
		}
		else
		{
			root = new BinaryTreeNode();
			root->data = data;
		}
	}

	BinaryTreeNode* TraversePreorder(BinaryTreeNode* node)
	{
		BinaryTreeNode *n = node;
		n->Visit();
		if ( n->left )
			TraversePreorder(n->left);
		if ( n->right )
			TraversePreorder(n->right);
		
		return n;
	}

	BinaryTreeNode* TraversePostorder(BinaryTreeNode* node)
	{
		BinaryTreeNode *n = node;
		
		if (n->left)
			TraverseInorder(n->left);
		if (n->right)
			TraverseInorder(n->right);
		n->Visit();

		return n;
	}

	BinaryTreeNode* TraverseInorder(BinaryTreeNode* node)
	{
		BinaryTreeNode *n = node;
		if (n->left)
			TraverseInorder(n->left);
		n->Visit();
		if (n->right)
			TraverseInorder(n->right);
		
		return n;
	}

	BinaryTreeNode *root;
};

#include "AST.h"

class fitness_sample
{
public:
	vector<double> terminal_values;
	double training_sample;
};

class ASTPopulation : public ASTContainer
{
public:
	ASTPopulation()
	{
		//	ast = new AST();
		//	ast->CreateRoot();

	}
	~ASTPopulation()
	{

	}

	struct terminal_rep
	{
		double value;
		string id;
		bool is_numeric;
	};

	/*void AddTerminal(string term, bool numeric)
	{
	terminal_rep rep;
	rep.id = term;
	rep.is_numeric = numeric;
	terminals.push_back(rep);
	}

	void SetTerminalValue(string term, double value)
	{
	for (int u = 0; u < terminals.size(); u++)
	{
	terminals[u].value = value;
	}
	}*/

	void SetPopulationSize(int size)
	{
		population_size = size;
	}

	void generatePopulation()
	{
		for (int i = 0; i < population_size; i++)
		{
			AST *ast = new AST();
			ast->SetParentObject(this);
			ast->CreateRoot();
			//ast->AddTerminal("x", false);
			//ast->AddTerminal("y", false);
			//ast->AddTerminal("a", false);
			//ast->AddTerminal("3.13", true);
			/*for (int j = 0; j < terminals.size(); j++)
			{
			ast->AddTerminal(terminals[j].id, terminals[j].is_numeric);
			}*/
			ast->CreateTree(ast->root);

			population.push_back(ast);
						ast->PrintTree(ast->root);
			population_values.push_back(0.0);
			/*
			ast->SetTerminalValue("x", 9.8);
			ast->SetTerminalValue("y", 4.5);
			ast->SetTerminalValue("a", 1);
			//			double root_value = ast->root->value();

			cout << "value of calculation with x= " << 9.8 << " and y= " << 4.5 << " and a=" << 1 << "  :==" << root_value;
			delete ast;
			*/
			//cout << endl;
		}
	}

	double current_best_sample = 10000000.0;

	void ComputeValues(int index)
	{
		for (int i = 0; i < population.size(); i++)
		{
			double this_value = population[i]->root->value();
			if (this_value == INFINITY || this_value == -INFINITY){
				population_values[i] += 1000;
				continue;
			}
			population_values[i] += (this_value- terminal_fitness_values[index].training_sample);
			//cout << "This Value: " << this_value << "        ";
			//double compare_val = abs(population_values[i]);
			//if (compare_val < current_best_sample )current_best_sample = compare_val;
		}
	}
	int the_best = 0;
	double current_best_score = 0.0;
	void ComputeFitness()
	{
		double percentage_scale = 1 / current_best_sample;
		
		for (int i = 0; i < population.size(); i++)
		{
			//population_values[i]
			//population[i]->PrintTree(population[i]->root);
			if (population_values[i] == 0)population[i]->fitness = 100000000;
			else
			{
				double average_difference = population_values[i] / terminal_fitness_values.size();

				double abs_difference = (average_difference*average_difference);
				//double abs_difference_squared = abs_difference * abs_difference;
				//population_values[i] = abs_difference_squared;
				if (abs_difference < 0.00001 )
				{
					//if (population[i]->fitness == 0.0)
					//	population[i]->fitness = 1.0;

					population[i]->fitness = 10000;
				}


				if (abs_difference >= 100000000 || abs_difference <= -INFINITY)
				{
					population[i]->fitness = 0;
				}
				else population[i]->fitness = 1 / abs_difference;
			}

			if ((population[i]->fitness != population[i]->fitness ))population[i]->fitness = 1;

			sumFitness += population[i]->fitness;
			//cout << "SumFitness: " << sumFitness << " ";
			population[i]->swapped = false;
			if (population[i]->fitness > current_best_score)
			{
				current_best_score = population[i]->fitness;
				the_best = i;
			}
			//cout << "fitness: " << abs_difference_squared << "        ";
			
			population_values[i] = 0.0f;
		}
	}

	void compute_sample_values()
	{
		the_best = 0;
		current_best_sample = 10000000.0;
		current_best_score = 0.0f;
		for (int i = 0; i < terminal_fitness_values.size(); i++)
		{
			for (int j = 0; j < terminal_fitness_values[i].terminal_values.size(); j++)
			{
				SetTerminalValue(this->terminals[j]->sym, terminal_fitness_values[i].terminal_values[j]);
			}
			ComputeValues(i);
			
//			cout << endl;

		}



		ComputeFitness();

//		sumFitness /= terminal_fitness_values.size();


	}

	int SelectBreedOp()
	{
		int breed_op_sel = RandomInt(0, 10000);
		int cross_thresh = prob_cross_over * 10000;
		int mutate_thresh = prob_mutate * 10000;
		int clone_thresh = prob_clone * 10000;

		int threshold_1 = cross_thresh + mutate_thresh;


		if (breed_op_sel < cross_thresh)
		{
			// cross
			return 0;
		}
		else if (breed_op_sel >= cross_thresh && breed_op_sel < threshold_1)
		{
			// mutate
			return 1;
		}
		else if (breed_op_sel >= threshold_1)
		{
			// clone
			return 2;
		}

		return 0;
	}
	vector<AST*> old_population;
	void Breed()
	{
		
		for (int i = 0; i < population.size(); i++)
		{
			AST* new_tree = population[i]->CopyTree();
			old_population.push_back(new_tree);
		}
		

		for (int i = 0; i < population.size(); i++)
		{
			

			//if (old_population[i]->swapped)continue;

			int breed_op = SelectBreedOp();

			if (i == this->the_best)
			{
				breed_op = 2;
			}
			else if (population[i]->fitness ==0)
			{
				breed_op = 1;
			}


			switch (breed_op)
			{
			case 0:
			{
				int parent_one_selector = ChooseParent();

				//AST* parent_one = population[parent_one_selector]->CopyTree();

				int parent_two_selector = ChooseParent();

				//int parent_one_selector = RandomInt(0, population.size()-1);
				
				//int parent_two_selector = RandomInt(0, population.size() - 1);
				
				if (parent_one_selector == parent_two_selector)
				{
					if (parent_one_selector == population.size() - 1)
					{
						parent_two_selector = the_best;
					}
					else 
					{
						parent_two_selector = parent_one_selector + 1;
					}
				}

				AST* newNode = this->DoSelectionCrossover(old_population, parent_one_selector, parent_two_selector);
				//this->DoSwapCrossover(parent_one_selector, parent_two_selector);
				delete population[i];
				population[i] = newNode;


				break;
			}
			case 1:
				population[i]->Mutate();
				
				break;
			case 2:
				
				// cloning .... lol
				break;

			}


			population_values[i] = 0.0f;
		}

		for (int i = 0; i < old_population.size(); i++)
		{
			delete old_population[i];
			

			population[i]->fitness = 0.0f;
		}

		old_population.clear();
		sumFitness = 0.0;
	}
 

	int ChooseParent()
	{
		int randSelector = (int)(RandomFloat(0, sumFitness) * 100);

		// Translate this number to the corresponding member**
		int memberID = 0;
		int partialSum = 0;

		for (int i = 0; i < population.size(); i++) {
			int n = (int)(old_population[i]->fitness * 100);
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

		return this->the_best;

		/*while (randSelector  > partialSum)
		{
		partialSum += population[memberID]->fitness;// / sumFitness;// fitness(memberID);
		memberID++;
		}*/

		//return memberID;
	}


	void SetProbabilities(double cross_over, double mutate, double clone)
	{
		prob_cross_over = cross_over;
		prob_mutate = mutate;
		prob_clone = clone;

	}


	AST* DoSelectionCrossover(vector<AST*> &pool, unsigned int s1, unsigned int s2)
	{

		AST* first_tree = pool[s1]->CopyTree();
		AST* second_tree = pool[s2]->CopyTree();


		ASTNode* cross1 = first_tree->CrossPoint();
		ASTNode* cross2 = second_tree->CrossPoint();

		ASTNode* cross1_p = first_tree->current_crossover_point_parent;
		ASTNode* cross2_p = second_tree->current_crossover_point_parent;

		if (cross1_p == cross1)
		{
			//cout << "first tree swaps root" << endl;
			first_tree->root = (OperatorNode*)cross2;
		}
		else
		{
			//cout << "Performing cross" << endl;
			// is it the left or the right?
			if (cross1 == cross1_p->left)
			{
				cross1_p->left = cross2;
			}
			else
			{
				cross1_p->right = cross2;
			}
		}

		if (cross2_p == cross2)
		{
			//cout << "second tree swaps root" << endl;
			second_tree->root = (OperatorNode*)cross1;
		}
		else
		{
			//cout << "Performing cross" << endl;
			if (cross2 == cross2_p->left)
			{
				cross2_p->left = cross1;
			}
			else
			{
				cross2_p->right = cross1;
			}
		}

		///old_population[s1]->swapped = true;
		//old_population[s2]->swapped = true;
		int rand_selector = RandomInt(0, 100);
		if (rand_selector > 50)
			return first_tree;
		else return second_tree;
		//population[s1]->fitness = 0.0f;
		//population[s2]->fitness = 0.0f;
	}

	void DoSwapCrossover(unsigned int s1, unsigned int s2)
	{
		
		ASTNode* cross1 = population[s1]->CrossPoint();
		ASTNode* cross2 = population[s2]->CrossPoint();

		ASTNode* cross1_p = population[s1]->current_crossover_point_parent;
		ASTNode* cross2_p = population[s2]->current_crossover_point_parent;
		
		if (cross1_p == cross1)
		{
			//cout << "first tree swaps root" << endl;
			population[s1]->root = (OperatorNode*)cross2;
		}
		else
		{
			//cout << "Performing cross" << endl;
			// is it the left or the right?
			if (cross1 == cross1_p->left)
			{
				cross1_p->left = cross2;
			}
			else
			{
				cross1_p->right = cross2;
			}
		}

		if (cross2_p == cross2)
		{
			//cout << "second tree swaps root" << endl;
			population[s2]->root = (OperatorNode*)cross1;
		}
		else
		{
			//cout << "Performing cross" << endl;
			if (cross2 == cross2_p->left)
			{
				cross2_p->left = cross1;
			}
			else
			{
				cross2_p->right = cross1;
			}
		}

		population[s1]->swapped = true;
		population[s2]->swapped = true;

		//population[s1]->fitness = 0.0f;
		//population[s2]->fitness = 0.0f;
	}

	
	double sumFitness = 0.0;
	
	double prob_cross_over;
	double prob_mutate;
	double prob_clone;
	
	vector< fitness_sample > terminal_fitness_values;
	//vector<terminal_rep> terminals;
	int population_size = 0;

	
	vector<AST*> population;
	vector<AST*> copy_population;

	vector<double> population_values;
};

int _tmain(int argc, char* argv[])
{
	srand(10);
	/*std::vector<std::string> arr;
	arr = split("This--is--split", "--");
	for (size_t i = 0; i<arr.size(); i++)
		printf("%s\n", arr[i].c_str());
		*/

	VariableSizedMultiList< string, string > mlist;

	mlist.Insert("NAME", "DAVE");
	mlist.Insert("NAME", "KATHY");
	mlist.Insert("NAME", "GEORGE");
	mlist.Insert("NAME", "SHIRVIN");

	mlist.Insert("PLACE", "READING");
	mlist.Insert("PLACE", "LONDON");
	mlist.Insert("PLACE", "TOKYO");

	mlist.Insert("SUBJECT", "MATH");
	mlist.Insert("OBJECT", "TABLE");


	VariableMultiListNode<string, string> n = mlist["NAME"];

	int index = mlist.FindKey("SUBJECT");




//	vector<string> v1 = string_to_vector(simple_script.strMyOperators);

//	for (int i = 0; i < v1.size(); i++) cout << v1[i] << endl;

	// Load some data //
	std::vector<int> params;
	params.push_back(1);
	params.push_back(2);
	params.push_back(3);
	params.push_back(4);

	// Store and print our results to standard out //
	std::stringstream param_stream;
	//std::cout << my::join(param_stream, params.begin(), params.end(), ",").str() << std::endl;

	// A quick and dirty way to print directly to standard out //
	my::join(std::cout, params.begin(), params.end(), ",") << std::endl;




	const std::string s = "x = sin(y+2)";

	std::regex words_regex("[^\\S]+");
	//std::regex words_regex("/\S*/");
	/*auto words_begin =
		std::sregex_iterator(s.begin(), s.end(), words_regex);
	auto words_end = std::sregex_iterator();

	std::cout << "Found "
		<< std::distance(words_begin, words_end)
		<< " words:\n";

	for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
		std::smatch match = *i;
		std::string match_str = match.str();
		std::cout << match_str << '\n';
	}*/


	std::vector<string> vs = vsplit(s, words_regex);
	for (int i = 0; i < vs.size(); i++) std::cout << vs[i] << std::endl;


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
	
	//cout << endl << simple_script.postfixEvaluate(simple_script.arrayPostfixExpression) << endl;


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
	/*for (int i = 0; i < 1200; i++)
	{
		OperatorNode *n = new OperatorNode();
		delete n;
	}*/

	/*for (int i = 0; i < 10; i++)
	{
		AST *ast = new AST();
		ast->CreateRoot();
		ast->AddTerminal("x", false);
		ast->AddTerminal("y", false);
		ast->AddTerminal("a", false);
		ast->AddTerminal("3.13", true);
		ast->CreateTree(ast->root);
		ast->PrintTree(ast->root);

		ast->SetTerminalValue("x", 9.8);
		ast->SetTerminalValue("y", 4.5);
		ast->SetTerminalValue("a", 1);

		double root_value = ast->root->value();

		cout << "value of calculation with x= " << 9.8 << " and y= " << 4.5 << " and a=" << 1 << "  :==" << root_value;
		delete ast;
		cout << endl;
	}*/

	ASTPopulation *pop = new ASTPopulation();
	pop->SetPopulationSize(1000);
	pop->SetProbabilities(0.5, 0.3, 0.2);
	pop->AddTerminal("x", false);
	pop->AddTerminal("y", false);

	for (int i = 0; i < 20; i++)
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

		pop->terminal_fitness_values.push_back(samp);
	}

	
	//pop->AddTerminal("a", false);
	//pop->AddTerminal("3.13", true);
	pop->generatePopulation();
//	pop->SetTerminalValue("x", 9.8);
//	pop->SetTerminalValue("y", 4.5);
//	pop->SetTerminalValue("a", 1);


/*	cout << "printing first tree" << endl;
	cout << "=====================================" << endl;
	pop->population[0]->PrintTree(pop->population[0]->root);
	cout << endl;
	cout << "printing second tree" << endl;
	cout << "=====================================" << endl;
	pop->population[1]->PrintTree(pop->population[1]->root);
	cout << endl;

	cout << "Attempting copy tree" << endl;
	cout << endl << endl << endl << endl;
	AST* new_tree = pop->population[0]->CopyTree();
	new_tree->PrintTree(new_tree->root);
	cout << endl << endl << endl << endl;
	cout << "Copy tree done" << endl;


	cout << endl << endl << endl << endl;
	cout << "Attempting to mutate" << endl;
	cout << endl << endl << endl << endl;
	AST* new_tree2 = pop->population[1]->CopyTree();
	new_tree2->PrintTree(new_tree2->root);
	cout << endl << endl << endl << endl;
	
	for (int i = 0; i < 100; i++){
		new_tree2->Mutate();

		new_tree2->PrintTree(new_tree2->root);
		cout << endl << endl << endl << endl;
	}
	cout << "mutate done" << endl;


	ASTNode* cross1 = pop->population[0]->CrossPoint();
	ASTNode* cross2 = pop->population[1]->CrossPoint();

	ASTNode* cross1_p = pop->population[0]->current_crossover_point_parent;
	ASTNode* cross2_p = pop->population[1]->current_crossover_point_parent;

	if (cross1_p == cross1)
	{
		cout << "first tree swaps root" << endl;
		pop->population[0]->root = (OperatorNode*)cross2;
	}
	else
	{
		cout << "Performing cross" <<endl;
		// is it the left or the right?
		if (cross1 == cross1_p->left)
		{
			cross1_p->left = cross2;
		}
		else
		{
			cross1_p->right = cross2;
		}
	}

	if (cross2_p == cross2)
	{
		cout << "second tree swaps root" << endl;
		pop->population[1]->root = (OperatorNode*)cross1;
	}
	else
	{
		cout << "Performing cross" << endl;
		if (cross2 == cross2_p->left)
		{
			cross2_p->left = cross1;
		}
		else
		{
			cross2_p->right = cross1;
		}
	}

	cout << "printing first tree" << endl;
	cout << "=====================================" << endl;
	pop->population[0]->PrintTree(pop->population[0]->root);
	cout << endl;
	cout << "printing second tree" << endl;
	cout << "=====================================" << endl;
	pop->population[1]->PrintTree(pop->population[1]->root);
	cout << endl;

	*/
	for (int epoch = 0; epoch < 200; epoch++)
	{
		pop->compute_sample_values();
		AST * best_tree = pop->population[pop->the_best];
		ASTNode *best_root = best_tree->root;
		best_tree->PrintTree(best_root);
		cout << "Best Current Score: " << pop->current_best_score << endl;
		cout << endl << endl;
		cout << "result with x=3, y=4 : ";
		pop->SetTerminalValue("x", 3.0);
		pop->SetTerminalValue("y", 4.0);
		cout<< best_tree->root->value();
		cout << endl << endl;
		cout << "SumFitness: " << pop->sumFitness << endl;
		pop->Breed();
		
	}
	
	delete pop;

	cout << "**************************************************************" << endl;
	 

	setup();

	glutInit(&argc, argv);                 // Initialize GLUT
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(width, height);   // Set the window's initial width & height
	glutCreateWindow("OpenGL Setup Test"); // Create a window with the given title
	
	glutInitWindowPosition(640, 480); // Position the window's initial top-left corner
	glutReshapeFunc(reshape);       // Register callback handler for window re-size event
	//glutDisplayFunc(display); // Register display callback handler for window re-paint

	/* Extension wrangler initialising */
	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK)
	{
		printf( "Error: %s\n", glewGetErrorString(glew_status));
		return EXIT_FAILURE;
	}

	if (!GLEW_VERSION_2_0) {
		printf( "No support for OpenGL 2.0 found\n");
		return 1;
	}

	GLint max_units;

	glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &max_units);
	if (max_units < 1) {
		printf( "Your GPU does not have any vertex texture image units\n");
		return 1;
	}

	printf("Use left/right/up/down to move.\n");
	printf("Use pageup/pagedown to change the horizontal scale.\n");
	printf("Press home to reset the position and scale.\n");
	printf("Press F1 to toggle interpolation.\n");
	printf("Press F2 to toggle clamping.\n");
	printf("Press F3 to toggle rotation.\n");
	printf("Press F4 to toggle polygon offset.\n");

	/* When all init functions run without errors,
	the program can initialise the resources */
	if (init_resources())
	{
		/* We can display it if everything goes OK */
		glutDisplayFunc(display);
		glutKeyboardFunc(keyboard);
		glutKeyboardUpFunc(keyboardup); 
		glutIdleFunc(display);

		glutSpecialFunc(special);
		glutMouseFunc(mouse);
		
		glutMainLoop();
	}
	//glutMainLoop();           // Enter the event-processing loop

	cleanup();
	

	return 0;
}

