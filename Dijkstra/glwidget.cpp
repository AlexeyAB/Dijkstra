#include "StdAfx.h"
#include "glwidget.h"
#include<QMessageBox>


GLWidget::GLWidget(QWidget *parent)
	: QGLWidget(parent), mWallsNumber(0)
{
	ui.setupUi(this);
	mCalcDistance.FillWallsMatrix(mWallsNumber);
}

GLWidget::~GLWidget()
{
}

void GLWidget::SetWallsNumber(int number) 
{
	mWallsNumber = (number < 0)? 0 : number;
}

void GLWidget::GenerateWalls() 
{
	mCalcDistance.FillWallsMatrix(mWallsNumber);
	paintGL();
	repaint();
}


void GLWidget::FindPath() 
{
	if(!mCalcDistance.DijkstraFindPath()) 
	{
		QMessageBox msgBox;
		msgBox.setText("Unable find path!");
		msgBox.exec();
	}

	repaint();
}


void GLWidget::ShowWalls() 
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(0, 0, 1);

	for(size_t x = 0; x < MATRIX_SIZE; ++x) 
	{
		for(size_t y = 0; y < MATRIX_SIZE; ++y) 
		{
			if(mCalcDistance.mWallsMatrix[x][y]) 
			{
				PaintQuad(x, y);
			}
		}
	}
}

void GLWidget::ShowPath(const std::pair<size_t, size_t> endPosition) 
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(0, 1, 1);

	size_t x = endPosition.first, y = endPosition.second;
	PaintQuad(x, y);
	while(x != 0 || y != 0) 
	{
		auto curElement = mCalcDistance.mParentsMatrix[x][y];
		x = curElement.first, y = curElement.second;
		PaintQuad(x, y);
	}
}

void GLWidget::PaintQuad(size_t x, size_t y) 
{
	glBegin(GL_QUADS);
		glVertex2f(x*2.0f / MATRIX_SIZE, (y+1)*2.0f / MATRIX_SIZE);			// left-top
		glVertex2f((x+1)*2.0f / MATRIX_SIZE, (y+1)*2.0f / MATRIX_SIZE);	// right-top
		glVertex2f((x+1)*2.0f / MATRIX_SIZE, y*2.0f / MATRIX_SIZE);			// right-bottom
		glVertex2f(x*2.0f / MATRIX_SIZE, y*2.0f / MATRIX_SIZE);					// left-bottom
	glEnd();
}


void GLWidget::initializeGL() 
{
	glLoadIdentity();
	glTranslatef(-1.0f, -1.0f, 0.0f);
	glClearColor(1, 1, 0, 1);
	//glEnable(GL_DEPTH_TEST);
}


void GLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(1, 0, 0);	// Red

	// Show grid
	glBegin(GL_QUAD_STRIP);
		for(size_t i = 0; i <= MATRIX_SIZE; ++i) 
		{
			glVertex2f(i*2.0f / MATRIX_SIZE, 0.0f);
			glVertex2f(i*2.0f / MATRIX_SIZE, 2.0f);
		}
	glEnd();

	glBegin(GL_QUAD_STRIP);
		for(size_t i = 0; i <= MATRIX_SIZE; ++i) 
		{
			glVertex2f(0.0f, i*2.0f / MATRIX_SIZE);
			glVertex2f(2.0f, i*2.0f / MATRIX_SIZE);
		}
	glEnd();

	ShowPath();
	ShowWalls();
}


void GLWidget::resizeGL(int w, int h) 
{
	glViewport(0, 0, static_cast<GLint>(w), static_cast<GLint>(h));

}