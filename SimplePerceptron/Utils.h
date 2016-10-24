#ifndef UTILS_H
#define UTILS_H

#include "stdlib.h"
#include <windows.h>  // for MS Windows

#include <iostream>
#include <cmath>
#include <algorithm>




//#include <ft2build.h>
#define FT_FREETYPE_H
//#include <freetype.h>

#define stdmax(a,b) (a>b?a:b)


inline float RandomFloat(float min, float max)
{
	float r = (float)rand() / (float)RAND_MAX;
	return min + r * (max - min);
}


inline float RandomInt(int min, int max)
{
	float r = (float)rand() / (float)RAND_MAX;
	return (int)((float)min + r * float(max - min));
}


#define PI 3.141592

inline float RandomAngle()
{
	return RandomFloat(0, 2 * PI);
}

class PVector
{
public:
	PVector(float X, float Y){
		x = X;
		y = Y;
	}

	PVector(){
		x = 0.0f;
		y = 0.0f;
	}

	void operator=(PVector &p2)
	{
		x = p2.x;
		y = p2.y;
	}

	void Random()
	{
		float theta = RandomAngle();

		x = cosf(theta);
		y = sinf(theta);
	}


	void Mult(float val)
	{
		x *= val;
		y *= val;
	}

	void add(PVector p)
	{
		x += p.x;
		y += p.y;
	}

	void normalize()
	{
		float mag = sqrtf(x*x + y*y);
		x /= mag;
		y /= mag;
	}

	float x;
	float y;
};

inline float dist(float x1, float y1, float x2, float y2)
{
	float dx = x2 - x1;
	float dy = y2 - y1;
	return sqrtf(dx*dx + dy*dy);
}


//====================================================================
//
// Bitfield
//
//
//====================================================================


class BitField
{
public:

	// looks a bit over complex, but this works for an
	// N-dimensional bitfield from some old code that
	// i wrote years ago ... may take a look at an easier version
	// later ...
	// NOTE: the use of 32 means that it uses integers, this could
	// be updated to use bytes by changing to 8,
	// and thiswould be more memory compressed too ...
	// however, as the saying goes ... "if it ain't broke, don't fix it"

	BitField(){}
	BitField(int numBits)
	{
		dataSize = 32;
		if (numBits == 0)
			numBits = dataSize;

		m_numBits = numBits;
		m_sizeInInts = (numBits / dataSize) + 1; // need to add one int

		m_data = new int[(m_sizeInInts)];

		//memset( (void*)m_data, 0, sizeof(m_data) );
		for (int i = 0; i < m_sizeInInts; i++)
		{
			m_data[i] = 0;
		}
	}

	~BitField()
	{
		if (m_data)
			delete[] m_data;
	}

	void SetBit(int i)
	{
		if (i < m_numBits && i >= 0)
		{
			*(m_data + ((i + 1) / dataSize)) |= 1 << ((i + 1) - ((i + 1) / dataSize)*(dataSize - 1));
			return;
		}
		//DEBUG_PRINT("Bitfield Error in Utils/Collections.h: Values must be wrong. i == %d, and m_numBits == %d", i, m_numBits);
	}

	bool CheckBit(int i)
	{
		if (i < m_numBits && i >= 0)
		{
			return (*(m_data + ((i + 1) / dataSize)) & 1 << ((i + 1) - (dataSize - 1)*((i + 1) / dataSize)));
		}
		//DEBUG_PRINT("Bitfield Error in Utils/Collections.h: Values must be wrong. i == %d, and m_numBits == %d", i, m_numBits);
		return false;
	}

	void ResetBit(int i)
	{
		if (i < m_numBits && i >= 0)
		{
			(*(m_data + ((i + 1) / dataSize)) &= ~(1 << ((i + 1) - ((i + 1) / dataSize)*(dataSize - 1))));
			return;
		}
		//DEBUG_PRINT("Bitfield Error in Utils/Collections.h: Values must be wrong. i == %d, and m_numBits == %d", i, m_numBits);
	}

	void Clear()
	{

		for (int i = 0; i < m_sizeInInts; i++)
		{
			m_data[i] = 0;
		}
	}


	int m_sizeInInts;
	int m_numBits;
	int dataSize;
	int *m_data;

};


//====================================================================
//
// BlockIndexBitField
//	basically the same as the other bitbuffer, with clearer notation
//
//====================================================================

class BlockIndexBitField
{
public:

	BlockIndexBitField(int numBits)
	{
		dataSize = 32;
		if (numBits == 0)
			numBits = dataSize;

		m_numBits = numBits;
		m_sizeInInts = (numBits / dataSize) + 1; // need to add one int

		m_data = new int[(m_sizeInInts)];

		//memset( (void*)m_data, 0, sizeof(m_data) );
		for (int i = 0; i < m_sizeInInts; i++)
		{
			m_data[i] = 0;
		}
	}

	~BlockIndexBitField()
	{
		if (m_data)
			delete[] m_data;
	}

	void SetBit(int idx)
	{
		if (idx > m_numBits) return;

		if (idx < 0) return;

		int blockIndex = (int)((float)(idx) / dataSize);

		int remainder = idx - blockIndex*dataSize;

		m_data[blockIndex] |= (1 << remainder);
	}

	bool CheckBit(int idx)
	{
		if (idx > m_numBits) return false;

		if (idx < 0) return false;

		int blockIndex = (int)((float)(idx) / dataSize);

		int remainder = idx - blockIndex*dataSize;

		return m_data[blockIndex] & (1 << remainder);
	}

	void ResetBit(int idx)
	{
		if (idx > m_numBits) return;

		if (idx < 0) return;

		int blockIndex = (int)((float)(idx) / dataSize);

		int remainder = idx - blockIndex*dataSize;

		m_data[blockIndex] &= ~(1 << remainder);
	}

	void Clear()
	{
		for (int i = 0; i < m_sizeInInts; i++)
		{
			m_data[i] = 0;
		}
	}

	int m_sizeInInts;
	int m_numBits;
	int dataSize;
	int *m_data;
};



class BlockIndexBitField_8
{
public:

	BlockIndexBitField_8(int numBits)
	{
		dataSize = 8;
		if (numBits == 0)
			numBits = dataSize;

		m_numBits = numBits;
		m_sizeInBytes = (numBits / dataSize) + 1; // need to add one int

		m_data = new unsigned char[(m_sizeInBytes)];

		//memset( (void*)m_data, 0, sizeof(m_data) );
		for (int i = 0; i < m_sizeInBytes; i++)
		{
			m_data[i] = 0;
		}
	}

	~BlockIndexBitField_8()
	{
		if (m_data)
			delete[] m_data;
	}

	void SetBit(int idx)
	{
		if (idx > m_numBits) return;

		if (idx < 0) return;

		int blockIndex = (int)((float)(idx) / dataSize);

		int remainder = idx - blockIndex*dataSize;

		m_data[blockIndex] |= (1 << remainder);
	}

	bool CheckBit(int idx)
	{
		if (idx > m_numBits) return false;

		if (idx < 0) return false;

		int blockIndex = (int)((float)(idx) / dataSize);

		int remainder = idx - blockIndex*dataSize;

		return m_data[blockIndex] & (1 << remainder);
	}

	void ResetBit(int idx)
	{
		if (idx > m_numBits) return;

		if (idx < 0) return;

		int blockIndex = (int)((float)(idx) / dataSize);

		int remainder = idx - blockIndex*dataSize;

		m_data[blockIndex] &= ~(1 << remainder);
	}

	void Clear()
	{
		for (int i = 0; i < m_sizeInBytes; i++)
		{
			m_data[i] = 0;
		}
	}

	int m_sizeInBytes;
	int m_numBits;
	int dataSize;
	unsigned char *m_data;
};



/*=================================================================
BINARY TREE
=================================================================*/

class BinaryTreeNode
{
public:
	BinaryTreeNode(){
		data = 0;
		left = right = 0;
	}

	void Visit(){
		std::cout << "Visiting This: " << data << std::endl;
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
		if (n->left)
			TraversePreorder(n->left);
		if (n->right)
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



/* modern opengl wiki books*/
/**
* Store all the file's contents in memory, useful to pass shaders
* source code to OpenGL
*/
char* file_read(const char* filename)
{
	FILE* in = 0;
		fopen_s(&in,filename, "rb");
	if (in == NULL) return NULL;

	int res_size = BUFSIZ;
	char* res = (char*)malloc(res_size);
	int nb_read_total = 0;

	while (!feof(in) && !ferror(in)) {
		if (nb_read_total + BUFSIZ > res_size) {
			if (res_size > 10 * 1024 * 1024) break;
			res_size = res_size * 2;
			res = (char*)realloc(res, res_size);
		}
		char* p_res = res + nb_read_total;
		nb_read_total += fread(p_res, 1, BUFSIZ, in);
	}

	fclose(in);
	res = (char*)realloc(res, nb_read_total + 1);
	res[nb_read_total] = '\0';
	return res;
}


#ifdef GL_GEOMETRY_SHADER
GLuint create_gs_program(const char *vertexfile, const char *geometryfile, const char *fragmentfile, GLint input, GLint output, GLint vertices) {
	GLuint program = glCreateProgram();
	GLuint shader;

	if (vertexfile) {
		shader = create_shader(vertexfile, GL_VERTEX_SHADER);
		if (!shader)
			return 0;
		glAttachShader(program, shader);
	}

	if (geometryfile) {
		shader = create_shader(geometryfile, GL_GEOMETRY_SHADER);
		if (!shader)
			return 0;
		glAttachShader(program, shader);

		glProgramParameteriEXT(program, GL_GEOMETRY_INPUT_TYPE_EXT, input);
		glProgramParameteriEXT(program, GL_GEOMETRY_OUTPUT_TYPE_EXT, output);
		glProgramParameteriEXT(program, GL_GEOMETRY_VERTICES_OUT_EXT, vertices);
	}

	if (fragmentfile) {
		shader = create_shader(fragmentfile, GL_FRAGMENT_SHADER);
		if (!shader)
			return 0;
		glAttachShader(program, shader);
	}

	glLinkProgram(program);
	GLint link_ok = GL_FALSE;
	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
	if (!link_ok) {
		fprintf(stderr, "glLinkProgram:");
		print_log(program);
		glDeleteProgram(program);
		return 0;
	}

	return program;
}
#else

#endif
#endif