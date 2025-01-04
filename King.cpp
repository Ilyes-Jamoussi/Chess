#include "King.h"

namespace model {

	King::King(Position position, Color color) : Piece(position, color, constants::KING) {
		(KingsInstancesCount_ >= 2) ? throw MoreThan2KIng("Can't have more than 2 kings") : KingsInstancesCount_++;
	}

    vector<Position> King::possibleMoves(const std::shared_ptr<Piece>** pieces) const {
        vector<Position> moves;
        const int directions[8][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1},{1, 1}, {-1, -1}, {-1, 1}, {1, -1} };
        for (auto& direction : directions) {
            int rank = this->getPosition().getRank();
            int file = this->getPosition().getFile();
            rank += direction[0];
            file += direction[1];
            if (!(rank < 0 || rank >= constants::BoardWidth || file < 0 || file >= constants::BoardHeight)) {
                if (pieces[rank][file] == nullptr) 
                    moves.push_back(Position(rank, file));
                else if (pieces[rank][file]->getColor() != this->getColor()) 
                    moves.push_back(Position(rank, file));;
            }
        }
        return moves;
    };
    
    std::shared_ptr<Piece> King::clone() const { return std::make_shared<King>(*this); }

	King::~King(){
		KingsInstancesCount_--;
	}
}




