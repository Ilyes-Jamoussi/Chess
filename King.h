#pragma once
#ifndef King_H
#define King_H
#include "Position.h"
#include "Piece.h"
#include <stdexcept>

struct MoreThan2KIng : public std::exception {
	using std::exception::exception;
};

using namespace std;
namespace model {
	class King : public Piece {
	public:
		King(Position position, Color color);

		std::vector<Position> possibleMoves(const std::shared_ptr<Piece>** pieces) const override;

		std::shared_ptr<Piece> clone() const override;

		~King();
	private:
		static inline int KingsInstancesCount_ = 0;
	};
	
}

#endif


