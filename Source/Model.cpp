#include "Model.h"

Model::Model(void)
{
	width = height = 0;
	position[0] = 0;
	position[1] = 0;
}

Model::~Model(void)
{
}

void Model::Init(int width, int height, const char *path)
{
	this->width = width;
	this->height = height;

	texture.LoadTexture(path);
}

void Model::SetPosition(int x, int y)
{
	position[0] = x;
	position[1] = y;
}

void Model::Draw()
{
	glPushMatrix();
	glTranslatef(position[0], position[1], 0);

	texture.BindTexture();
	glBegin(GL_POLYGON);
		glTexCoord2f(0, 0);   glVertex2i(0,0);
		glTexCoord2f(0, 1);   glVertex2i(0, height);
		glTexCoord2f(1, 1);   glVertex2i(width, height);
		glTexCoord2f(1, 0);   glVertex2i(width, 0);
	glEnd();

	glPopMatrix();
}