#include "StdAfx.h"
#include "dijkstra.h"

Dijkstra::Dijkstra(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	ui.horizontalScrollBar->setRange(0, GLWidget::MATRIX_SIZE * GLWidget::MATRIX_SIZE);
}

Dijkstra::~Dijkstra()
{

}
