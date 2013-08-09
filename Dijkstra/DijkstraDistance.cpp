#include "StdAfx.h"
#include "DijkstraDistance.h"
#include <cassert>
#include <ctime>
#include <random>
#include <limits>

DijkstraDistance::DijkstraDistance( void )
{
}
// ----------------------------------------------------------------------------


DijkstraDistance::~DijkstraDistance( void )
{
}
// ----------------------------------------------------------------------------

void DijkstraDistance::FillWallsMatrix( const size_t wallsNumber ) 
{
	assert(wallsNumber <= MATRIX_SIZE*MATRIX_SIZE);

	for(size_t x = 0; x < MATRIX_SIZE; ++x)
		for(size_t y = 0; y < MATRIX_SIZE; ++y) 
		{
			mWallsMatrix[x][y] = 0;
			mParentsMatrix[x][y] = std::pair<size_t, size_t>(0, 0);
		}

	std::default_random_engine gen(static_cast<size_t>(time(NULL)));
	std::uniform_int_distribution<size_t> index_rand(0, MATRIX_SIZE-1);

	for(size_t i = 0; i < wallsNumber; ++i) 
	{
		size_t x = index_rand(gen), y = index_rand(gen);
		while(mWallsMatrix[x][y]) 
		{
			++x;
			if(x == MATRIX_SIZE)
				x = 0, ++y;
			if(y == MATRIX_SIZE)
				y = 0;
		}
		mWallsMatrix[x][y] = 1;
	}	
}
// ----------------------------------------------------------------------------


std::vector<std::pair<size_t, size_t> > DijkstraDistance::GetElementsTo( const std::pair<size_t, size_t> &position ) 
{
	std::vector<std::pair<size_t, size_t> > elementsTo;
	size_t x = position.first, y = position.second;

	if(x > 0 && !mMarkedMatrix[x-1][y]) 
		elementsTo.emplace_back(std::pair<size_t, size_t>(x-1, y));

	if(x < MATRIX_SIZE-1 && !mMarkedMatrix[x+1][y]) 
		elementsTo.emplace_back(std::pair<size_t, size_t>(x+1, y));

	if(y > 0 && !mMarkedMatrix[x][y-1]) 
		elementsTo.emplace_back(std::pair<size_t, size_t>(x, y-1));

	if(y < MATRIX_SIZE-1 && !mMarkedMatrix[x][y+1]) 
		elementsTo.emplace_back(std::pair<size_t, size_t>(x, y+1));
	
	return elementsTo;
}
// ----------------------------------------------------------------------------


bool DijkstraDistance::DijkstraFindPath( const std::pair<size_t, size_t> startPosition ) 
{
	// If there is wall on start position
	if(mWallsMatrix[startPosition.first][startPosition.second])
	{
		return false;
	}

	// Initialize the matrix
	const size_t INF = size_t()-1;
	for(size_t x = 0; x < mDistancesMatrix.size(); ++x)
		for(size_t y = 0; y < mDistancesMatrix[0].size(); ++y) 
		{
			mDistancesMatrix[x][y] = INF;
			mParentsMatrix[x][y] = startPosition;
			mMarkedMatrix[x][y] = mWallsMatrix[x][y];
		}
	mDistancesMatrix[0][0] = 0;

	for(size_t i = 0; i < mAddedMatrix.size(); ++i) 
	{
		mAddedMatrix[i].reset();
	}

	std::pair<size_t, size_t> curPosition = startPosition;
	mMarkedMatrix[startPosition.first][startPosition.second] = true;

	std::vector<std::pair<size_t, size_t> > candidatesForMark;	
	candidatesForMark.push_back(startPosition);	

	while(!candidatesForMark.empty()) 
	{
		size_t iForMarked = 0;

		curPosition = candidatesForMark[iForMarked];
		size_t currentDistance = mDistancesMatrix[curPosition.first][curPosition.second];
		
		for(size_t i = 0; i < candidatesForMark.size(); ++i) 
		{
			size_t x = candidatesForMark[i].first, y = candidatesForMark[i].second;
			if (!mMarkedMatrix[x][y] && (mDistancesMatrix[x][y] < currentDistance)) 
			{
				curPosition = candidatesForMark[i];
				currentDistance = mDistancesMatrix[x][y];	
				iForMarked = i;
			}
		}

		// If there are no more reachable position then exit
		if(currentDistance == INF) 
		{
			break;
		}

		candidatesForMark.erase(candidatesForMark.cbegin() + iForMarked);
		mMarkedMatrix[curPosition.first][curPosition.second] = true;

		// Get the nearest elements to try to change(reduce) its distance
		std::vector<std::pair<size_t, size_t> > elementsTo = GetElementsTo(curPosition);

		for(size_t i = 0; i < elementsTo.size(); ++i) 
		{
			size_t x = elementsTo[i].first, y = elementsTo[i].second;
			const size_t len = 1, toDistance = mDistancesMatrix[x][y];

			if(currentDistance + len < toDistance) 
			{
				mDistancesMatrix[x][y] = currentDistance + len;
				mParentsMatrix[x][y] = curPosition;
			}

			if(!mAddedMatrix[x][y]) 
			{
				candidatesForMark.push_back(elementsTo[i]);
				mAddedMatrix[x][y] = true;
			}
		}
	}

	if(mDistancesMatrix[MATRIX_SIZE-1][MATRIX_SIZE-1] == INF) 
	{
		return false;
	}
	else 
	{
		return true;
	}
}
// ----------------------------------------------------------------------------
