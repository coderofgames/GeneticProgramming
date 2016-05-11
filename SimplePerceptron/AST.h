#ifndef AST_H
#define AST_H

#include "Utils.h"

using std::vector;

class ASTNode
{
public:

	~ASTNode()
	{
		if (left && left->type == 0)
			delete left;
		if (right && right->type == 0)
			delete right;

		// cannot delete terminal nodes
		left = NULL;
		right = NULL;
	}
	int type = 0;
	virtual double value() = 0;
	ASTNode *left = 0;
	ASTNode *right = 0;
	ASTNode* parent = 0;
};

enum OPERATOR{ ADD = 0, SUB, MUL, DIV, POW, SQRT };
string operator_array[6] = { "ADD", "SUB", "MUL", "DIV", "POW", "SQRT" };
class OperatorNode : public ASTNode
{
public:
	OperatorNode(){
		type = 0;
		left = right = 0;
		parent = 0;
	}

	virtual double value() = 0;

	OPERATOR the_operator;
	int num_operands = 2;
};

class ADDNode : public OperatorNode
{
public:
	ADDNode()
	{
		the_operator = OPERATOR::ADD;
		num_operands = 2;
		left = right = 0;
		parent = 0;
	}
	double value(){
		if (left && right)
		{
			return left->value() + right->value();
		}

		return 0.0f;
	}
};

class SUBNode : public OperatorNode
{
public:
	SUBNode(){
		the_operator = OPERATOR::SUB;
		num_operands = 2;
		left = right = 0;
		parent = 0;
	}
	double value(){
		if (left && right)
		{
			return left->value() - right->value();
		}

		return 0.0f;
	}
};

class MULNode : public OperatorNode
{
public:
	MULNode(){
		the_operator = OPERATOR::MUL;
		num_operands = 2;
		left = right = 0;
		parent = 0;
	}
	double value(){
		if (left && right)
		{
			return left->value() * right->value();
		}

		return 0.0f;
	}
};

class DIVNode : public OperatorNode
{
public:
	DIVNode(){
		the_operator = OPERATOR::DIV;
		num_operands = 2;
		left = right = 0;
		parent = 0;
	}
	double value(){
		if (left && right)
		{
			return left->value() / right->value();
		}

		return 0.0f;
	}
};

class POWNode : public OperatorNode
{
public:
	POWNode(){
		the_operator = OPERATOR::POW;
		num_operands = 2;
		left = right = 0;
		parent = 0;
	}
	double value(){
		if (left && right)
		{
			return pow(left->value(), right->value());
		}

		return 0.0f;
	}
};

class SQRTNode : public OperatorNode
{
public:
	SQRTNode(){
		the_operator = OPERATOR::SQRT;
		num_operands = 1;
		left = right = 0;
		parent = 0;
	}

	double value()
	{
		if (left)
		{
			return sqrt(left->value());
		}
		else if (right)
		{
			return sqrt(right->value());
		}
	}
};

class TerminalNode : public ASTNode
{
public:
	TerminalNode(){ sym = ""; num = 0.0;  type = 1; }
	TerminalNode(string s, bool bNum)
	{
		sym = s;
		//num = (isNumberC(s) ? string_to_double(s) : 0.0);
		numeric = bNum;
		if (bNum)
		{
			num = string_to_float(s);
		}
		else num = 0.0;
		type = 1;
		left = 0;
		right = 0;
		parent = 0;
	}

	double value(){
		return num;
	}

	double num;
	string sym;
	bool numeric = false;
};

class ASTContainer
{
public:

	ASTContainer(){}
	~ASTContainer(){
		for (int i = 0; i < terminals.size(); i++)
		{
			delete terminals[i];
			terminals[i] = NULL; // what a mess, these stray and draggling nodes 
		}
		terminals.clear();
	}
	TerminalNode *FindNextUnusedTerminal()
	{
		for (int i = 0; i < terminals.size(); i++)
		{
			if (HasTerminalBeenUsed(terminals[i]->sym) == false)
				return terminals[i];
		}
		return terminals[0];
	}

	bool CheckAllTerminalsHaveBeenUsed()
	{
		for (int i = 0; i < terminals.size(); i++)
		{
			if (HasTerminalBeenUsed(terminals[i]->sym) == false)
				return false;
		}
		return true;
	}

	bool HasTerminalBeenUsed(string s)
	{
		for (int i = 0; i < terminals_used.size(); i++)
		{
			if (terminals_used[i] == s)
				return true;
		}

		return false;
	}

	void SetTerminalValue(string symbol, double value)
	{
		for (int i = 0; i < terminals.size(); i++)
		{
			if (terminals[i]->sym == symbol)
			{
				terminals[i]->num = value;
			}
		}
	}
	TerminalNode* AddTerminal(string s, bool bNum)
	{
		for (int i = 0; i < terminals.size(); i++)
		{
			if (terminals[i]->sym == s)
				return terminals[i];
		}
		TerminalNode* t = new TerminalNode(s, bNum);
		terminals.push_back(t);
		return t;
	}

	TerminalNode* RandomTerminal()
	{
		int selector = RandomInt(0, terminals.size() - 1);
		return terminals[selector];

	}
	vector<TerminalNode* > terminals;
	vector< string > terminals_used;
};

class AST
{
private:
	ASTContainer* m_container_object = 0;
public:

	OperatorNode* current_crossover_point_parent = 0;
	OperatorNode* current_crossover_point = 0;


	~AST()
	{
		Delete();
	}

	void Delete()
	{
		delete root;
		for (int i = 0; i < terminals.size(); i++)
		{
			delete terminals[i];
			terminals[i] = NULL; // what a mess, these stray and draggling nodes 
		}
		terminals.clear();
	}

	void DeleteTree(ASTNode *n)
	{
		if (n->type == 0)
		{

			if (n->left)
			{
				DeleteTree(n->left);
			}
			if (n->right)
			{
				DeleteTree(n->right);
			}
			delete n;
		}
		else
		{
			delete n;
		}
	}

	void CreateRoot(){
		root = CreateOperatorNode();
	}

	OperatorNode * CreateOperatorNode()
	{
		int selector = (int)RandomInt(0, 6);
		switch (selector)
		{
		case 0: return new ADDNode();
		case 1:return new SUBNode();
		case 2:return new MULNode();
		case 3:return new DIVNode();
		case 4:return new POWNode();
		case 5:return new SQRTNode();
		case 6:return new SQRTNode();
		}

		return 0;
	}

	int depth = 0;

	void CreateTree(OperatorNode *node)
	{

		depth++;
		int terminal_selector = (int)RandomInt(0, 80);
		terminal_selector += depth;
		if (terminal_selector > 40)
		{
			node->left = RandomTerminal();
			node->left->parent = node;
		}
		else
		{
			node->left = CreateOperatorNode();
			CreateTree((OperatorNode*)node->left);
			node->left->parent = node;
		}

		if (node->num_operands == 1)
			return;

		terminal_selector = (int)RandomInt(0, 80);
		terminal_selector += depth;
		if (terminal_selector > 40)
		{
			node->right = RandomTerminal();
			if (node->the_operator == OPERATOR::DIV)
			{
				while (node->right == node->left)
				{
					node->right = RandomTerminal();
				}
			}
			node->right->parent = node;
		}
		else
		{
			node->right = CreateOperatorNode();
			CreateTree((OperatorNode*)node->right);
			node->right->parent = node;
		}
	}

	OperatorNode* CrossPoint()
	{
		current_crossover_point_parent = root;
		return (OperatorNode*)CrossOverPoint(root);
	}

	ASTNode* CrossOverPoint(ASTNode *node)
	{
		int direction_selector = (int)RandomInt(0, 100);
		if (direction_selector  > 50)
		{
			if (node->right && node->right->type == 0)
			{
				int cross_selector = (int)RandomInt(0, 100);
				if (cross_selector > 50)
				{
					current_crossover_point_parent = (OperatorNode*)node;
					return node->right;
				}
				else {
					current_crossover_point_parent = (OperatorNode*)node;
					return CrossOverPoint(node->right);
				}
			}
			else if (node->left && node->left->type == 0)
			{
				int cross_selector = (int)RandomInt(0, 100);
				if (cross_selector > 50)
				{
					current_crossover_point_parent = (OperatorNode*)node;
					return node->left;
				}
				else {
					current_crossover_point_parent = (OperatorNode*)node;
					return CrossOverPoint(node->left);
				}
			}
			else return node;
		}
		else
		{
			if (node->left && node->left->type == 0)
			{
				int cross_selector = (int)RandomInt(0, 100);
				if (cross_selector > 50)
				{
					current_crossover_point_parent = (OperatorNode*)node;
					return node->left;
				}
				else {
					current_crossover_point_parent = (OperatorNode*)node;
					return CrossOverPoint(node->left);
				}
			}
			else if (node->right && node->right->type == 0)
			{
				int cross_selector = (int)RandomInt(0, 100);
				if (cross_selector > 50)
				{
					current_crossover_point_parent = (OperatorNode*)node;
					return node->right;
				}
				else
				{
					current_crossover_point_parent = (OperatorNode*)node;
					return CrossOverPoint(node->right);
				}
			}
			else return node;
		}

		return 0;
	}

	void PrintTree(ASTNode *n)
	{
		if (!n)return;

		if (n->type == 0)
		{
			cout << operator_array[((OperatorNode*)n)->the_operator] << "( ";
			if (n->left)
			{
				PrintTree(n->left);
			}
			if (n->right)
			{
				PrintTree(n->right);
			}
			cout << ") ";
		}
		else
		{
			cout << " " << ((TerminalNode*)n)->sym << " ";
		}



	}

	void SetParentObject(ASTContainer *container){
		this->m_container_object = container;
	}

	TerminalNode* RandomTerminal()
	{
		if (m_container_object)
		{
			return this->RandomTerminal2();
		}
		else
		{
			int selector = RandomInt(0, terminals.size() - 1);
			return terminals[selector];
		}
		return 0;
	} 

	TerminalNode* RandomTerminal2()
	{
		return this->m_container_object->RandomTerminal();
	}

	TerminalNode* AddTerminal(string s, bool bNum)
	{
		if (m_container_object == 0)
		{
			for (int i = 0; i < terminals.size(); i++)
			{
				if (terminals[i]->sym == s)
					return terminals[i];
			}
			TerminalNode* t = new TerminalNode(s, bNum);
			terminals.push_back(t);
			return t;
		}
		else
		{
			return m_container_object->AddTerminal(s, bNum);
		}
	}


	TerminalNode *FindNextUnusedTerminal()
	{
		if (m_container_object)
		{
			m_container_object->FindNextUnusedTerminal();
		}
		else
		{
			for (int i = 0; i < terminals.size(); i++)
			{
				if (HasTerminalBeenUsed(terminals[i]->sym) == false)
					return terminals[i];
			}
			return terminals[0];
		}
		return 0;
	}

	bool CheckAllTerminalsHaveBeenUsed()
	{
		if (m_container_object)
		{
			m_container_object->CheckAllTerminalsHaveBeenUsed();
		}
		else
		{
			for (int i = 0; i < terminals.size(); i++)
			{
				if (HasTerminalBeenUsed(terminals[i]->sym) == false)
					return false;
			}
		}
		return true;
	}

	bool HasTerminalBeenUsed(string s)
	{
		if (m_container_object)
		{
			m_container_object->HasTerminalBeenUsed(s);
		}
		else
		{
			for (int i = 0; i < terminals_used.size(); i++)
			{
				if (terminals_used[i] == s)
					return true;
			}
		}

		return false;
	}

	void SetTerminalValue(string symbol, double value)
	{
		if (m_container_object)
		{
			m_container_object->SetTerminalValue(symbol, value);
		}
		else
		{
			for (int i = 0; i < terminals.size(); i++)
			{
				if (terminals[i]->sym == symbol)
				{
					terminals[i]->num = value;
				}
			}
		}
	}

	AST* CopyTree()
	{
		if (!root)return 0;

		AST * tree = new AST();
		//tree->root = new ASTNode();
		tree->root = (OperatorNode*)copy_node(this->root);
		tree->SetParentObject(this->m_container_object);
		tree->fitness = this->fitness;

		return tree;
	}

	ASTNode* copy_node(ASTNode* tree_node)
	{
		//ASTNode* temp=0;
		if (tree_node->type == 0)
		{
			OperatorNode*  temp = (OperatorNode*)tree_node;
			//ADD = 0, SUB, MUL, DIV, POW, SQRT
			OperatorNode*  new_node = 0;
			switch (temp->the_operator)
			{
			case OPERATOR::ADD:
				new_node = new ADDNode();
				break;
			case OPERATOR::SUB:
				new_node = new SUBNode();
				break;
			case OPERATOR::MUL:
				new_node = new MULNode();
				break;
			case OPERATOR::DIV:
				new_node = new DIVNode();
				break;
			case OPERATOR::POW:
				new_node = new POWNode();
				break;
			case OPERATOR::SQRT:
				new_node = new SQRTNode();
				break;
			}

			if (tree_node->left)
			{
				new_node->left = copy_node(tree_node->left);
				if (new_node->left)
					new_node->left->parent = new_node;
			}
			if (tree_node->right)
			{
				new_node->right = copy_node(tree_node->right);
				if (new_node->right)
					new_node->right->parent = new_node;
			}

			return new_node;
		}
		else
		{
			TerminalNode* new_node = (TerminalNode*)tree_node;
			return new_node;

		}

		return 0;
	}

	void Mutate()
	{
		int N = RandomInt(0, 100);
		if (N > 50)
		{
			OperatorNode* op = this->CreateOperatorNode();
			if ( op->the_operator == OPERATOR::SQRT)
			{ 
				op->left = this->root;
				this->root->parent = op;

				this->root = op;
			}
			else
			{
				op->left = this->root->left;

				if (op->left && op->left->type == 0)
					op->left->parent = op;
				op->right = this->root->right;

				if (op->right && op->right->type == 0)
					op->right->parent = op;

				this->root = op;
			}
		}
		else
		{
			Mutate_R(root);
		}
	}


	OperatorNode * CreateOperatorNode_ForMutation(OPERATOR old_op)
	{
		if (old_op == OPERATOR::SQRT) return new SQRTNode();

		int selector = (int)RandomInt(0, 4);
		switch (selector)
		{
		case 0: return new ADDNode();
		case 1:return new SUBNode();
		case 2:return new MULNode();
		case 3:return new DIVNode();
		case 4:return new POWNode();
		//case 5:return new SQRTNode();
		}

		return 0;
	}

	void Mutate_R(ASTNode* node)
	{
		if (!node )return;
		

		bool MUTATE_FLAG = false;

		bool MUTATE_LEFT_CHILD = false;
		bool MUTATE_RIGHT_CHILD = false;
		
		int N = RandomInt(0, 100);

		int LEFT_OR_RIGHT_FIRST = RandomInt(0, 100);

		if (N > 50)
		{
			
			
			if (LEFT_OR_RIGHT_FIRST > 50)
			{
				if (node->left)
				{
					if (node->left->type == 1)
					{

						TerminalNode* new_terminal = this->RandomTerminal();
						while (new_terminal == node->left)
						{
							new_terminal = this->RandomTerminal();
						}
						node->left = new_terminal;
					}
					else
					{
						MUTATE_LEFT_CHILD = true;
					}
				}
				else if (node->right )
				{
					if (node->right->type == 1)
					{
						TerminalNode* new_terminal = this->RandomTerminal();
						while (new_terminal == node->right)
						{
							new_terminal = this->RandomTerminal();
						}
						node->right= new_terminal;
					}
					else
					{
						MUTATE_RIGHT_CHILD = true;
					}
				}
				
			}

			else 
			{
				if (node->right)
				{
					if (node->right->type == 1)
					{
						TerminalNode* new_terminal = this->RandomTerminal();
						while (new_terminal == node->right)
						{
							new_terminal = this->RandomTerminal();
						}
						node->right = new_terminal;
					}
					else
					{
						MUTATE_RIGHT_CHILD = true;
					}
				}
				else if (node->left)
				{
					if (node->left->type == 1)
					{
						TerminalNode* new_terminal = this->RandomTerminal();
						while (new_terminal == node->left)
						{
							new_terminal = this->RandomTerminal();
						}
						node->left = new_terminal;
					}
					else
					{
						MUTATE_LEFT_CHILD = true;

						
					}
				}
				
				
			}
			
		}
		else
		{
			if ( LEFT_OR_RIGHT_FIRST > 50 )
			{
				if ((node->left) && (node->left->type == 0))
				{
					Mutate_R(node->left);
					MUTATE_FLAG = false;
				}
				else if ((node->right) && (node->right->type == 0))
				{
					Mutate_R(node->right);
					MUTATE_FLAG = false;
				}
				else {
					MUTATE_FLAG = true;
				}
			}
			else
			{
				if ((node->right) && (node->right->type == 0))
				{
					Mutate_R(node->right);
					MUTATE_FLAG = false;
				}
				else if ((node->left) && (node->left->type == 0))
				{
					Mutate_R(node->left);
					MUTATE_FLAG = false;
				}
				else {
					MUTATE_FLAG = true;
				}
			}

		}

		if ((MUTATE_FLAG==true) && node && node->type == 0 )
		{

			OperatorNode* op = this->CreateOperatorNode_ForMutation(((OperatorNode*)node)->the_operator);
			
			op->left = node->left;
			op->right = node->right;

			
			if ((node) && (node->parent) && (node->parent->left) && (node->parent->left == node))
			{
				node->parent->left = op;
				op->parent = node->parent;
				delete node;
			}
			else if ((node)&&(node->parent) && (node->parent->right) && (node->parent->right == node))
			{
				node->parent->right = op;
				op->parent = node->parent;
				delete node;
			}
		}

		if ((MUTATE_LEFT_CHILD==true) && node && node->left && node->left->type == 0)
		{
			
			OperatorNode* op = this->CreateOperatorNode_ForMutation(((OperatorNode*)node->left)->the_operator);
			

			if (node->left && node->left->left)
				op->left = node->left->left;
			if (node->left && node->left->right)
				op->right = node->left->right;

			op->parent = node;
			node->left->left = 0;
			node->left->right = 0;
			delete node->left;
			node->left = op;
			
			
		}

		if ((MUTATE_RIGHT_CHILD==true) && node && node->right && node->right->type == 0)
		{
			if (((OperatorNode*)node->right)->the_operator == OPERATOR::SQRT)
				return;

			OperatorNode* op = this->CreateOperatorNode_ForMutation(((OperatorNode*)node->right)->the_operator);
			

			if (node->right && node->right->left)
				op->left = node->right->left;
			if (node->right && node->right->right)
				op->right = node->right->right;

			
			op->parent = node;
			node->right->left = 0;
			node->right->right = 0;
			delete node->right;
			node->right = op;
			
		}




	}

	float fitness=0.0f;
	bool swapped = false;

	vector< OperatorNode* > operators;

	vector< TerminalNode* > terminals;

	vector< string > terminals_used;

	OperatorNode *root;
};
#endif