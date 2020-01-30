#ifndef _MODEL_
#define _MODEL_

#include <string>
#include <vector>
#include "Renderer.h"

struct Point
{
	public:
	Point(){ x = y = z = 0.0f; }

	float x, y, z;
};

struct Face
{
	public:
	Point vertexs[3];
	Point uvs[3];
	Point normals[3];
};

class Model
{
	public:
	/**
	 * Carraga um modelo com textura do disco,
	 * com os diretório especificados.
	 */
	Model(const char* modelDir, const char *textureDir);

	/**
	 * Destrói este modelo e libera os recursos
	 * usados.
	 */
	~Model();

	/**
	 * Desenha o modelo carregado.
	 */
	void draw() const;

	private:

	GLuint texture;
	std::vector<Face> faces;

	void loadFile(const char* dir, std::vector<std::string>& data);
	void loadModel(const std::vector<std::string>& data);
	void loadVertex(const std::string& line, Point& vertex);
	void loadUV(const std::string& line, Point& uv);
	void loadNormal(const std::string& line, Point& normal);
	void loadFace(const std::string& line, const std::vector<Point>& vertexs, const std::vector<Point>& uvs,
				  const std::vector<Point>& normals);
};

#endif