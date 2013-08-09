#pragma once
#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <QtGui/QMainWindow>
#include "ui_dijkstra.h"

class Dijkstra : public QMainWindow
{
	Q_OBJECT

public:
	Dijkstra(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Dijkstra();

private:
	Ui::DijkstraClass ui;

};

#endif // DIJKSTRA_H
