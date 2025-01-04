#include "Rook.h"


namespace model {
    Rook::Rook(Position position, Color color) : Piece(position, color, constants::ROOK) {}  

    std::vector<Position> Rook::possibleMoves(const std::shared_ptr<Piece>** pieces) const  {
        std::vector<Position> moves;
        const int directions[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };  
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

    std::shared_ptr<Piece> Rook::clone() const { return std::make_shared<Rook>(*this); }
}

