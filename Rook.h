#pragma once
#ifndef Rook_H
#define Rook_H

#include "Position.h"
#include "Piece.h"
#include "LibConstants.h"

namespace model {
	class Rook : public Piece {
	public:
		Rook(Position position, Color color);

		std::vector<Position> possibleMoves(const std::shared_ptr<Piece>** pieces) const override;

		std::shared_ptr<Piece> clone() const;
	};
}
#endif
