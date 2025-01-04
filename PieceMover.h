//#pragma once
//#include "Board.h"
//#include "Square.h"
//
//namespace model {
//    class PieceMover {
//    public:
//        PieceMover(Board* board, Piece* piece, const Position& destination) 
//        : board_(board), piece_(piece), originalPosition_(piece->getPosition()), validMove_(false) {
//            if (!board || !piece)
//                throw std::invalid_argument("Board and Piece cannot be null.");
//
//            validMove_ = piece->canMoveTo(destination,piece->getColor(), board_->getPieces()  );
//            if (!validMove_)
//                throw std::runtime_error("Invalid move attempted.");
//        }
//    
//        ~PieceMover() {
//            if (piece_ && validMove_) {
//                board_->movePiece(piece_->getPosition(), originalPosition_);
//            }
//        }
//
//        PieceMover(const PieceMover&) = delete;
//        PieceMover& operator=(const PieceMover&) = delete;
//
//    private:
//        Board* board_;
//        Piece* piece_;
//        Position originalPosition_;
//        bool validMove_; 
//    };
//}