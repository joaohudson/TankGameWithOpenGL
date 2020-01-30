#include <fstream>
#include <iostream>
#include "Model.h"
#include "Renderer.h"

using std::fstream;
using std::string;
using std::stringstream;
using std::vector;
using std::stoi;

Model::Model(const char* dir, const char *textureDir)
{
	vector<string> data;

	loadFile(dir, data);
	loadModel(data);
	texture = renderer::loadTexture(textureDir);
}

Model::~Model()
{
	glDeleteTextures(1, &texture);
}

void Model::draw() const
{
	Point *point = NULL;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_TRIANGLES);
	{	
		//Desenha todas as faces:
		for(Face face : faces)
			//Desenha a face:
			for(int i = 0; i < 3; i++)
			{
				point = &face.normals[i];
				glNormal3f(point->x, point->y, point->z);

				point = &face.uvs[i];
				glTexCoord2f(point->x, point->y);

				point = &face.vertexs[i];
				glVertex3f(point->x, point->y, point->z);
			}
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Model::loadFile(const char* dir, vector<string>& data)
{
	fstream stream;
	string file(dir);
	string text;

	stream.open(file);

	while(!stream.eof())
	{
		getline(stream, text);
		data.push_back(text);
	}
}

void Model::loadModel(const vector<string>& fileData)
{
	vector<Point> vertexs;
	vector<Point> normals;
	vector<Point> uvs;
	Point point;

	//Itera por cada linha do vetor:
	for(string line : fileData)
	{
		if(!line.substr(0, 2).compare("v "))
		{
			loadVertex(line, point);
			vertexs.push_back(point);
		}
		else if(!line.substr(0, 2).compare("vt"))
		{
			loadUV(line, point);
			uvs.push_back(point);
		}
		else if(!line.substr(0, 2).compare("vn"))
		{
			loadNormal(line, point);
			normals.push_back(point);
		}
	}

	for(string line : fileData)
	{
		if(!line.substr(0, 2).compare("f "))
			loadFace(line, vertexs, uvs, normals);
	}
}

/**
 * Divide a string em substrings separadas pelo
 * caractere delimitador especificado. E as armazena
 * no vetor dado.
 */
static void split(const string& str, char delimiter, vector<string>& data);

void Model::loadFace(const string& line, const vector<Point>& vertexs, const vector<Point>& uvs,
					 const vector<Point>& normals)
{
	vector<string> tokens;
	vector<string> p1, p2, p3;
	Face face;

	split(line, ' ', tokens);

	//Pega as informações do primeiro ponto(vértice, uv, normal):
	split(tokens[1], '/', p1);
	//Pega do segundo:
	split(tokens[2], '/', p2);
	//Pega do terceiro:
	split(tokens[3], '/', p3);

	//Obtém os vértices:
	face.vertexs[0] = vertexs[stoi(p1[0]) - 1];
	face.vertexs[1] = vertexs[stoi(p2[0]) - 1];
	face.vertexs[2] = vertexs[stoi(p3[0]) - 1];
	//Obtém as coordenadas de textura:
	face.uvs[0] = uvs[stoi(p1[1]) - 1];
	face.uvs[1] = uvs[stoi(p2[1]) - 1];
	face.uvs[2] = uvs[stoi(p3[1]) - 1];
	//Obtém as normais:
	face.normals[0] = normals[stoi(p1[2]) - 1];
	face.normals[1] = normals[stoi(p2[2]) - 1];
	face.normals[2] = normals[stoi(p3[2]) - 1];

	//Guarda a face:
	faces.push_back(face);
}

/**
 * Obtém um vértice apartirda linha dada.
 */
void Model::loadVertex(const string& line, Point &vertex)
{
	vector<string> tokens;
	//Obtém um vetor de coordenadas em forma de string:
	split(line, ' ', tokens);
	
	//o primeiro token é o prefixo, não deve ser considerado:
	vertex.x = stof(tokens[1]);
	vertex.y = stof(tokens[2]);
	vertex.z = stof(tokens[3]);
}

void Model::loadUV(const string& line, Point &uv)
{
	vector<string> tokens;
	//Obtém um vetor de coordenadas em forma de string:
	split(line, ' ', tokens);
	
	//o primeiro token é o prefixo, não deve ser considerado:
	uv.x = stof(tokens[1]);
	uv.y = stof(tokens[2]);
}

void Model::loadNormal(const string& line, Point &normal)
{
	vector<string> tokens;
	//Obtém um vetor de coordenadas em forma de string:
	split(line, ' ', tokens);
	
	//o primeiro token é o prefixo, não deve ser considerado:
	normal.x = stof(tokens[1]);
	normal.y = stof(tokens[2]);
	normal.z = stof(tokens[3]);
}

/*********************************************************
 * Funções auxiliares:
 *********************************************************/

static void split(const string& str, char delimiter, vector<string>& data)
{
	string token;
	int size = 0;
	int pos = 0;

	for(unsigned int i = 0; i < str.length(); i++)
	{
		if(str[i] == delimiter)
		{
			token = str.substr(pos, size);
			
			if(!token.empty())
				data.push_back(token);

			pos = i + 1;
			size = 0;
		}
		else if(i == str.length() - 1)
		{
			token = str.substr(pos, pos - str.length());
			data.push_back(token);

		}
		else
		{
			size++;
		}
	}
}