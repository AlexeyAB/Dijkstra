#pragma once
#include <array>
#include <vector>
#include <bitset>
#include <utility>


class DijkstraDistance
{
public:
	DijkstraDistance( void );
	~DijkstraDistance( void );

	enum { MATRIX_SIZE = 10 };

	void FillWallsMatrix( const size_t wallsNumber );
	std::vector<std::pair<size_t, size_t> > GetElementsTo( const std::pair<size_t, size_t> &position );
	bool DijkstraFindPath( const std::pair<size_t, size_t> startPosition = std::make_pair(0, 0) );


	std::array<std::array<std::pair<size_t, size_t>, MATRIX_SIZE>, MATRIX_SIZE> mParentsMatrix;
	std::array<std::bitset<MATRIX_SIZE>, MATRIX_SIZE> mWallsMatrix;

private:
	std::array<std::array<size_t, MATRIX_SIZE>, MATRIX_SIZE> mDistancesMatrix;
	std::array<std::bitset<MATRIX_SIZE>, MATRIX_SIZE> mMarkedMatrix;
	std::array<std::bitset<MATRIX_SIZE>, MATRIX_SIZE> mAddedMatrix;
};

