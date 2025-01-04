#pragma once
#include "Piece.h"

namespace model {

	Piece::Piece(Position position, Color color, constants::Type type) : position_(position), color_(color), type_(type) {}

	Piece::Piece(const Piece& other) : position_(other.position_), color_(other.color_), type_(other.type_) {};

	Position& Piece::getPosition() { 
		return position_; 
	}

	Position Piece::getPosition() const { 
		return position_; 
	}

	Color Piece::getColor() const { 
		return color_; 
	}

	constants::Type Piece::getType()  const {
		if (this == nullptr)
			return constants::EMPTY;
		return type_;
	}
}
