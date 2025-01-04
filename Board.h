#ifndef Board_H
#define Board_H

#include <memory>
#include <numeric>
#include <algorithm>

#include "LibConstants.h"
#include "Rook.h"
#include "Bishop.h"
#include "King.h"
#include "Piece.h"
#include "cppitertools/range.hpp"


namespace model {
	class Board {
	public:
		Board();

		void initializeBoardMatrix();
		void initializeEmptyBoard();
		void movePieceOnBoard(std::shared_ptr<Piece> myCurrentPiece, const Position& newPosition);

		void placePiece(std::shared_ptr<Piece> myPiece);
		void movePiece(const Position& currentPosition, const Position& newPosition);
		void registerPiece(std::shared_ptr<Piece> myPiece);
		void removePiece(std::shared_ptr<Piece> myPiece, std::shared_ptr<Piece> capturedPiece);
		void performCapture(const Position& currentPosition, const Position& newPosition);

		bool hasKing(const Position& position) const;
		bool isMoveValid(const Position& selectedPosition, const std::shared_ptr<Piece> piece) const;
		bool containsPiece(const Position& position) const;
		bool isCheck(const Color& color) const;
		bool isCheckMate(const Color& color) const;

		std::vector<Position> generateValidMoves(const std::shared_ptr<Piece> piece) const;
		std::vector<Position> getAllPossibleMoves(const Color& color) const;
		std::vector<Position> getAllValidMoves(const Color& color) const;
		Position locateKing(const Color& color) const;
				
		std::shared_ptr<Piece> getPieceAt(const Position& position) const;
		std::vector<std::shared_ptr<Piece>>& getPieceVector();
		std::shared_ptr<Piece>** getPieces(); 

		Board(const Board& other);

		~Board();
	private:
		std::vector<std::shared_ptr<Piece>> piecesVector_;
		std::shared_ptr<Piece>** pieces_; //pieces_[7][7];
	};
}



#endif