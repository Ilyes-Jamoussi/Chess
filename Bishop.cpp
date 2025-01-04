#include "Bishop.h"

namespace model {
	Bishop::Bishop(Position position, Color color) : Piece(position, color, constants::BISHOP) {} 

    std::vector<Position> Bishop::possibleMoves(const std::shared_ptr<Piece>** pieces) const {
        std::vector<Position> moves;
        const int directions[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };  // Diagonal directions
        for (auto& direction : directions) {
            int rank = this->getPosition().getRank();
            int file = this->getPosition().getFile();
            while (true) {
                rank += direction[0];
                file += direction[1];
                if (rank < 0 || rank >= constants::BoardWidth || file < 0 || file >= constants::BoardHeight)
                    break;
                if (pieces[rank][file] == nullptr)
                    moves.push_back(Position(rank, file));
                else {
                    if (pieces[rank][file]->getColor() != this->getColor()) 
                        moves.push_back(Position(rank, file));;
                    break;
                }
            }
        }
        return moves;
    }

    std::shared_ptr<Piece> Bishop::clone() const { return std::make_shared<Bishop>(*this); }
}
