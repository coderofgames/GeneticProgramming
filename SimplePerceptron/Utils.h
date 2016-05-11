#ifndef UTILS_H
#define UTILS_H

#include "stdlib.h"
#include <windows.h>  // for MS Windows
#include <gl/glew.h>
#include <GL/glut.h>  // GLUT, include glu.h and gl.h

#include <cmath>
#include <algorithm>

#define GLM_FORCE_RADIANS
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <glm/glm/vec2.hpp>//: vec2, bvec2, dvec2, ivec2 and uvec2
#include <glm/glm/vec3.hpp> //: vec3, bvec3, dvec3, ivec3 and uvec3
#include <glm/glm/vec4.hpp> // vec4, bvec4, dvec4, ivec4 and uvec4
#include <glm/glm/mat2x2.hpp> // mat2, dmat2
#include <glm/glm/mat2x3.hpp> // mat2x3, dmat2x3
#include <glm/glm/mat2x4.hpp> // mat2x4, dmat2x4
#include <glm/glm/mat3x2.hpp> // mat3x2, dmat3x2
#include <glm/glm/mat3x3.hpp> // mat3, dmat3
#include <glm/glm/mat3x4.hpp> // mat3x4, dmat2
#include <glm/glm/mat4x2.hpp> // mat4x2, dmat4x2
#include <glm/glm/mat4x3.hpp> // mat4x3, dmat4x3
#include <glm/glm/mat4x4.hpp> // mat4, dmat4
#include <glm/glm/common.hpp> // all the GLSL common functions
#include <glm/glm/exponential.hpp> // all the GLSL exponential functions
#include <glm/glm/geometric.hpp> // all the GLSL geometry functions
#include <glm/glm/integer.hpp> // all the GLSL integer functions
#include <glm/glm/matrix.hpp> // all the GLSL matrix functions
#include <glm/glm/packing.hpp> // all the GLSL packing functions
#include <glm/glm/trigonometric.hpp> // all the GLSL trigonometric functions
#include <glm/glm/vector_relational.hpp> // all the GLSL vector relational functions

#include <ft2build.h>
#define FT_FREETYPE_H
#include <freetype.h>

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

void GraphicsGL_Rect(float x, float y, float w, float h)
{
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f); //std::cout << "guess >0" << std::endl;//noFill();
	//glColor3f(0.0f, 1.0f, 0.0f);// std::cout << "guess <=0" << std::endl;

	// Each set of 4 vertices form a quad

	glVertex2f(x, y);    // x, y
	glVertex2f(x, y + h);

	glVertex2f(x, y + h);
	glVertex2f(x + w, y + h);

	glVertex2f(x + w, y + h);
	glVertex2f(x + w, y);

	glVertex2f(x + w, y);
	glVertex2f(x, y);


	glEnd();
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

/**
* Display compilation errors from the OpenGL shader compiler
*/
void print_log(GLuint object)
{
	GLint log_length = 0;
	if (glIsShader(object))
		glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
	else if (glIsProgram(object))
		glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
	else {
		fprintf(stderr, "printlog: Not a shader or a program\n");
		return;
	}

	char* log = (char*)malloc(log_length);

	if (glIsShader(object))
		glGetShaderInfoLog(object, log_length, NULL, log);
	else if (glIsProgram(object))
		glGetProgramInfoLog(object, log_length, NULL, log);

	fprintf(stderr, "%s", log);
	free(log);
}

/**
* Compile the shader from file 'filename', with error handling
*/
GLuint create_shader(const char* filename, GLenum type)
{
	const GLchar* source = file_read(filename);
	if (source == NULL) {
		fprintf(stderr, "Error opening %s: ", filename); perror("");
		return 0;
	}
	GLuint res = glCreateShader(type);
	const GLchar* sources[] = {
		// Define GLSL version
#ifdef GL_ES_VERSION_2_0
		"#version 100\n"
#else
		"#version 120\n"
#endif
		,
		// GLES2 precision specifiers
#ifdef GL_ES_VERSION_2_0
		// Define default float precision for fragment shaders:
		(type == GL_FRAGMENT_SHADER) ?
		"#ifdef GL_FRAGMENT_PRECISION_HIGH\n"
		"precision highp float;           \n"
		"#else                            \n"
		"precision mediump float;         \n"
		"#endif                           \n"
		: ""
		// Note: OpenGL ES automatically defines this:
		// #define GL_ES
#else
		// Ignore GLES 2 precision specifiers:
		"#define lowp   \n"
		"#define mediump\n"
		"#define highp  \n"
#endif
		,
		source };
	glShaderSource(res, 3, sources, NULL);
	free((void*)source);

	glCompileShader(res);
	GLint compile_ok = GL_FALSE;
	glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
	if (compile_ok == GL_FALSE) {
		fprintf(stderr, "%s:", filename);
		print_log(res);
		glDeleteShader(res);
		return 0;
	}

	return res;
}

GLuint create_program(const char *vertexfile, const char *fragmentfile) {
	GLuint program = glCreateProgram();
	GLuint shader;

	if (vertexfile) {
		shader = create_shader(vertexfile, GL_VERTEX_SHADER);
		if (!shader)
			return 0;
		glAttachShader(program, shader);
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
GLuint create_gs_program(const char *vertexfile, const char *geometryfile, const char *fragmentfile, GLint input, GLint output, GLint vertices) {
	fprintf(stderr, "Missing support for geometry shaders.\n");
	return 0;
}
#endif

GLint get_attrib(GLuint program, const char *name) {
	GLint attribute = glGetAttribLocation(program, name);
	if (attribute == -1)
		fprintf(stderr, "Could not bind attribute %s\n", name);
	return attribute;
}

GLint get_uniform(GLuint program, const char *name) {
	GLint uniform = glGetUniformLocation(program, name);
	if (uniform == -1)
		fprintf(stderr, "Could not bind uniform %s\n", name);
	return uniform;
}
#endif