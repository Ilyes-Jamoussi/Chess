#ifndef Piece_H
#define Piece_H

#include <vector>

#include "Position.h"
#include "LibConstants.h"
#include "cppitertools/range.hpp"
#include "Color.h"


namespace model {

	class Piece {
	public:
		Piece() = default;
		Piece(Position position, Color color, constants::Type type);

		virtual std::vector<Position> possibleMoves(const std::shared_ptr<Piece>** pieces) const = 0;

		Piece(const Piece& other);

		virtual std::shared_ptr<Piece> clone() const = 0;

		Position& getPosition();
		Color getColor() const;
		Position getPosition() const;
		constants::Type getType()  const;

		virtual ~Piece() = default;
	private:
		Position position_;
		const Color color_ = {};
		constants::Type type_ = constants::EMPTY;
	};
}

#endif