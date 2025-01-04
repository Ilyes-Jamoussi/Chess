#ifndef Bishop_H
#define Bishop_H
#include "Position.h"
#include "Piece.h"

namespace model {
	class Bishop : public Piece {
	public:
		Bishop(Position position, Color color);

		std::vector<Position> possibleMoves(const std::shared_ptr<Piece>** pieces) const override;

		std::shared_ptr<Piece> clone() const override;

	};
}
#endif
