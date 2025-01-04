#include "Position.h"

namespace model {

    Position::Position(int rank, int file)
        : interface::Coordinates(rank, file),
        rank_(rank), file_(file) {}

    Position::Position() : Position(0, 0) {}

    bool Position::equalPositions(const Position& other) const {
        return file_ == other.file_ && rank_ == other.rank_;
    }

    bool Position::insideBoard() const {
        return this->file_ >= 0 && this->file_ < constants::BoardWidth && this->rank_ >= 0 && this->rank_ < constants::BoardHeight;
    }

    bool Position::equalPositions(const int rankIndex, const int fileIndex) const {
        return file_ == fileIndex && rank_ == rankIndex;
    }

    bool Position::operator==(const Position& other) const {
        return equalPositions(other);
    }

    bool Position::operator!=(const Position& other) const {
        return !equalPositions(other);
    }

    Position& Position::operator+ (const Position& otherPosition) {
        this->rank_ += otherPosition.rank_;
        this->file_ += otherPosition.file_;
        return *this;
    }

    void Position::changePosition(const int rankIndex, const int fileIndex) {
        rank_ = rankIndex;
        file_ = fileIndex;      
    }

    void Position::changePosition(const Position& position) {
        rank_ = position.getRank();
        file_ = position.getFile();
    }

    void Position::operator+=(const Position& other) {
        this->rank_ += other.rank_;
        this->file_ += other.file_;
    }

    Position Position::operator*(int scalar) const {
        return Position(rank_ * scalar, file_ * scalar);
    }

    bool Position::isSumEven() const {
        return (file_ + rank_) % 2 == 0;
    }

    int Position::getFile() const {
        return file_;
    }

    int Position::getRank() const {
        return rank_;
    }

    int& Position::getFile() {
        return file_;
    }
    int& Position::getRank() {
        return rank_;
    }
}
