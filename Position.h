#pragma once
#ifndef Position_H
#define Position_H

#include "LibConstants.h"
#include "Coordinates.h"

namespace model {
	class Position : public interface::Coordinates {
	public:
		Position(int rank, int file);
		Position();
		bool equalPositions(const Position& autre) const;
		bool equalPositions(const int rankIndex, const int fileIndex) const;
		bool insideBoard() const;
		bool isSumEven() const;

		bool operator== (const Position& otherPosition) const;
		bool operator!= (const Position& otherPosition) const;		
		Position& operator+ (const Position& otherPosition);
		void operator+=(const Position& other);

		void changePosition( const int rankIndex,const int fileIndex);	
		void changePosition(const Position& position);
		Position operator* (const int scalar) const;
		
		int getFile() const;
		int getRank() const;
		int& getFile();
		int& getRank();

	private:
		int rank_, file_;
	};
}

#endif // POSITION_H