#include "Board.h"

namespace model {

	Board::Board() {
		initializeBoardMatrix();
		initializeEmptyBoard();
	}

	// Initializes the board array
	void Board::initializeBoardMatrix() {
		this->pieces_ = new std::shared_ptr<Piece> * [constants::BoardHeight];
		for (int rank : iter::range(constants::BoardWidth))
			pieces_[rank] = new std::shared_ptr<Piece> [constants::BoardWidth];
	}


	// Sets up the initial board with empty pieces
	void Board::initializeEmptyBoard() {
		for (int rank : iter::range(constants::BoardWidth)) {
			for (int file : iter::range(constants::BoardHeight))
				this->pieces_[rank][file] = nullptr;
		}
	}

	// Places a piece on the board
	void Board::placePiece(std::shared_ptr<Piece> myPiece) {
		this->pieces_[myPiece->getPosition().getRank()][myPiece->getPosition().getFile()] = myPiece;
	}

	// Moves a piece on the board and updates the board
	void Board::movePieceOnBoard(std::shared_ptr<Piece> myCurrentPiece, const Position& oldPosition) {
		this->pieces_[myCurrentPiece->getPosition().getRank()][myCurrentPiece->getPosition().getFile()] = myCurrentPiece;
		this->pieces_[oldPosition.getRank()][oldPosition.getFile()] = nullptr;
	}

	// Registers a piece in the list and places it on the board
	void Board::registerPiece(std::shared_ptr<Piece> piece) {
		this->piecesVector_.push_back(piece);
		this->placePiece(piece);
	}

	// Removes a piece from the list and board
	void Board::removePiece(std::shared_ptr<Piece> myPiece, std::shared_ptr<Piece> capturedPiece) {
		this->piecesVector_.erase(std::remove_if(this->piecesVector_.begin(),
			this->piecesVector_.end(),
			[&capturedPiece](std::shared_ptr<Piece> piece) {return capturedPiece->getPosition() == piece->getPosition(); }),
			this->piecesVector_.end());

		this->movePieceOnBoard(myPiece, capturedPiece->getPosition());
	}

	// Checks if the position contains a piece
	bool Board::containsPiece(const Position& position) const {
		return this->pieces_[position.getRank()][position.getFile()]->getType() != constants::EMPTY;
	}

	//Moves a piece from one position to another
	void Board::movePiece(const Position& currentPosition, const Position& newPosition) {
		std::shared_ptr<Piece> myPiece = getPieceAt(currentPosition);
		Position oldPosition = myPiece->getPosition();
		myPiece->getPosition().changePosition(newPosition);		
		movePieceOnBoard(myPiece, oldPosition);
	}

	// Captures a piece and moves the piece to a new position
	void Board::performCapture(const Position& currentPosition, const Position& newPosition) {
		removePiece(getPieceAt(currentPosition), getPieceAt(newPosition));
		movePiece(currentPosition, newPosition);
	}

	// Validates if the selected position is a valid move for the piece
	bool Board::isMoveValid(const Position& selectedPosition, const std::shared_ptr<Piece> piece) const{
		std::vector<Position> validMoves = this->generateValidMoves(piece);
		return std::find(validMoves.cbegin(), validMoves.cend(), selectedPosition) != validMoves.cend();
	}

	// Checks if there is a king at the given position
	bool Board::hasKing(const Position& position) const {
		auto it = std::find_if(piecesVector_.begin(), piecesVector_.end(), [&](std::shared_ptr<Piece> piece) {
			return  piece->getType() == constants::KING && piece->getPosition() == position; });
		return it != piecesVector_.end();
	}

	// Gets a piece at the given position
	std::shared_ptr<Piece> Board::getPieceAt(const Position& position) const { return this->pieces_[position.getRank()][position.getFile()]; }

	// Generates all possible moves for the specified color
	std::vector<Position> Board::getAllPossibleMoves(const Color& color) const {
		std::vector<Position> possibleMoves;
		for (const std::shared_ptr<Piece>& piece : this->piecesVector_) {
			if (piece->getColor() == color) {
				std::vector<Position> pieceMoves = piece->possibleMoves(const_cast<const std::shared_ptr<Piece>**>(pieces_));
				possibleMoves.insert(possibleMoves.cend(), pieceMoves.cbegin(), pieceMoves.cend());
			}
		}
		return possibleMoves;
	}

	// Generates all valid moves for the specified color
	std::vector<Position> Board::getAllValidMoves(const Color& color) const {
		std::vector<Position> validMoves;
		for (std::shared_ptr<Piece> piece : this->piecesVector_) {
			if (piece->getColor() == color) {
				std::vector<Position> pieceValidMoves = generateValidMoves(piece);
				validMoves.insert(validMoves.cend(), pieceValidMoves.cbegin(), pieceValidMoves.cend());
			}
		}
		return validMoves;
	}

	// Finds the position of the king of the specified color
	Position Board::locateKing(const Color& color) const {
		auto kingPieceIterator = std::find_if(piecesVector_.cbegin(), piecesVector_.cend(),
			[&](std::shared_ptr<Piece> piece) {
				return piece->getType() == constants::KING && piece->getColor() == color; });
			return (*kingPieceIterator)->getPosition();
	}

	// Checks if the specified color is in check
	bool Board::isCheck(const Color& color) const  {
		Color oppositeColor = (color == Color{ constants::White }) ? Color{ constants::Black } : Color{ constants::White };
		Position myKingPosition = locateKing(color);

		vector<Position> enemyPossibleMoves = this->getAllPossibleMoves(oppositeColor);

		for (const Position enemyPossiblePosition : enemyPossibleMoves) {
			if (enemyPossiblePosition == myKingPosition) {
				return true;
			}
		}
		return false;
	}

	// Checks if the specified color is in checkMate
	bool Board::isCheckMate(const Color& color) const {
		if (!this->isCheck(color))
			return false;
		return this->getAllValidMoves(color).empty();
	}

	// Generates valid moves for a piece considering the state of check
	std::vector<Position> Board::generateValidMoves(const std::shared_ptr<Piece> piece) const {
		vector<Position> possibleMoves = piece->possibleMoves(const_cast<const std::shared_ptr<Piece>**>(pieces_));
		vector<Position> validMoves;

		for (const Position& newPosition : possibleMoves) {
			Board simulatedBoard(*this);
			simulatedBoard.movePiece(piece->getPosition(), newPosition);
			if (!simulatedBoard.isCheck(piece->getColor()))
				validMoves.push_back(newPosition);
		}
		return validMoves;
	}

	Board::Board(const Board& other) {
		this->initializeBoardMatrix();
		this->initializeEmptyBoard();
		for (const std::shared_ptr<Piece>& piece : other.piecesVector_) {
			if (piece != nullptr)
				registerPiece(piece->clone());
		}
	}

	std::shared_ptr<Piece>** Board::getPieces() { return pieces_; }

	std::vector<std::shared_ptr<Piece>>& Board::getPieceVector() {
		return piecesVector_;
	}

	Board::~Board() {
		for (int rank : iter::range(constants::BoardWidth))
			delete[] pieces_[rank];
		delete[] pieces_;
	}

}
