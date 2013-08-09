#pragma once
#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "ui_glwidget.h"
#include "DijkstraDistance.h"


class GLWidget : public QGLWidget
{
	Q_OBJECT

public:
	GLWidget(QWidget *parent = 0);
	~GLWidget();

	void ShowWalls();
	void ShowPath(const std::pair<size_t, size_t> endPosition = std::make_pair(MATRIX_SIZE-1, MATRIX_SIZE-1));
	void PaintQuad(size_t x, size_t y);

	void initializeGL();
	void paintGL();
	void resizeGL(int w, int h);
	
	enum { MATRIX_SIZE = DijkstraDistance::MATRIX_SIZE };
private:
	Ui::GLWidget ui;
	size_t mWallsNumber;
	DijkstraDistance mCalcDistance;

public slots:
	void SetWallsNumber(int number);
	void GenerateWalls();
	void FindPath();
};

#endif // GLWIDGET_H
