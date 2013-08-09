#pragma once
#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "ui_glwidget.h"
#include "DijkstraDistance.h"


class GLWidget : public QGLWidget
{
	Q_OBJECT

	void initializeGL();
	void paintGL();
	void resizeGL(int w, int h);

	void PaintQuad(size_t x, size_t y) const;
	void PaintCube(size_t x, size_t y) const;

	void ShowWalls() const;
	void ShowPath(const std::pair<size_t, size_t> endPosition = std::make_pair(MATRIX_SIZE-1, MATRIX_SIZE-1)) const;
public:
	GLWidget(QWidget *parent = 0);
	~GLWidget();

	static const size_t MATRIX_SIZE = DijkstraDistance::MATRIX_SIZE;
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
