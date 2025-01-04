#include "Game.h"

namespace model {
	using namespace constants;

		Game::Game(const GameTag& gameId) {
			this->board_ = std::make_unique<Board>();
			// Load the specified game based on the gameId
			loadGame(gameId);
		}	

		// Load the specific game based on the provided game tag
		void Game::loadGame(const GameTag& gameTag) {
			switch (gameTag) {
			case GameTag::EmptyGame:
				break;
			case GameTag::TopalovVsPolgar2008:
				TopalovVsPolgar2008();
				break;
			case GameTag::BudnikovVsNovik1991:
				BudnikovVsNovik1991();
				break;
			case GameTag::VladimorovVsPalatnik1977:
				VladimorovVsPalatnik1977();
				break;
			}	
		}

		// Reset the board and game state
		void Game::resetBoard() {
			this->board_.reset();
			this->previousSelectedPosition_.reset();
			this->stateManager_.setState(SelectionState::Disabled);
		}

		// Add a piece to the board at a given position and color
		void Game::addPiece(constants::Type type, model::Position position, model::Color color) {
			switch (type) {
			case constants::KING:
				board_->registerPiece(std::make_shared<King>( position,color ));
				break;
			case constants::BISHOP:
				board_->registerPiece(std::make_shared<Bishop>( position,color ));
				break;
			case constants::ROOK:
				board_->registerPiece(std::make_shared<Rook>( position,color ));
				break;
			}
		}

		// Load the Topalov vs Polgar 2008 game setup
		void Game::TopalovVsPolgar2008() {
			addPiece(BISHOP, { 1,7 }, White);
			addPiece(KING, { 5,1 }, White);
			addPiece(KING, { 4,3 }, Black);
			addPiece(ROOK, { 2,4 }, Black);
		}

		// Load the Budnikov vs Novik 1991 game setup
		void Game::BudnikovVsNovik1991() {
			addPiece(KING, { 0,4 }, Black);
			addPiece(ROOK, { 1,0 }, White);
			addPiece(KING, { 3,4 }, White);
			addPiece(BISHOP, { 4,4 }, White);
			addPiece(ROOK, { 6,4 }, Black);
		}

		// Load the Vladimorov vs Palatnik 1977 game setup
		void Game::VladimorovVsPalatnik1977() {
			addPiece(ROOK, { 4,0 }, White);
			addPiece(BISHOP, { 1,1 }, Black);
			addPiece(BISHOP, { 4,1 }, Black);
			addPiece(KING, { 4,2 }, Black);
			addPiece(ROOK, { 1,4 }, Black);
			addPiece(BISHOP, { 5,4 }, White);
			addPiece(KING, { 6,5 }, White);

		}

		// Handle the selection of pieces based on the current game state
		void Game::handlePieceSelection(const int rank, const int file) {
			switch (stateManager_.getCurrentState()) {
			case SelectionState::Disabled:
				// No action required.
				break;
			case SelectionState::None:
				// Handle the None state (no piece selected yet)
				handleNoneState(rank, file);
				break;
			case SelectionState::Selected:
				// Handle the Selected state (a piece is already selected)
				handleSelectedState(rank, file);
				break;
			}
		}
	
		// Handle the None state (no piece is currently selected)
		void Game::handleNoneState(const int rank, const int file) {
			Position selectedPosition = { rank,file };
			// Check if the selected position contains a piece of the current player's color
			if (getBoard()->containsPiece(selectedPosition) && isCurrentPlayerPieceColorMatch(selectedPosition)){
				emit positionSelected(rank, file);
				previousSelectedPosition_ = std::make_unique<Position>(rank, file);
				stateManager_.setState(SelectionState::Selected);
			}				
		}

		// Handle the Selected state (a piece is currently selected)
		void Game::handleSelectedState(const int rank, const int file) {
			Position selectedPosition = { rank, file };
			std::shared_ptr<Piece> previousPiece = getBoard()->getPieceAt(*this->previousSelectedPosition_);

			// Check if the newly selected position is the same as the previous one
			if (isSamePosition(selectedPosition)) {
				handleSamePosition(rank, file);
				return;
			}

			// Check if the move is valid and not capturing the opponent's king
			if (isValidMove(previousPiece, selectedPosition)) {
				// Handle a valid move and transition the player state
				handleValidMove(selectedPosition);			
				this->playerState_.transition();
				emit currentPlayerSignal();

				emit resetMessage();
				// Check if the current player is in check
				if (board_->isCheck(playerState_.getCurrentPlayer())) {
					emit checkSignal();
				}
				// Check if the current player is in checkmate
				if (this->board_->isCheckMate(playerState_.getCurrentPlayer())) {
					emit checkMateSignal();
					stateManager_.setState(SelectionState::Disabled);
					emit resetCurrentPlayerMessage();
				}
				// Check if the number of pieces is equal to 2, meaning a draw
				if (this->board_->getPieceVector().size() == 2) {
					emit drawSignal();
					stateManager_.setState(SelectionState::Disabled);
					emit resetCurrentPlayerMessage();
				}

			}

			// Check if the selected position contains a piece of the current player's color
			if (getBoard()->containsPiece(selectedPosition) && isCurrentPlayerPieceColorMatch(selectedPosition)) {
				handleJumpPosition(rank, file);
				stateManager_.setState(SelectionState::Selected);
			}
		}

		// Handle the case where the player select between different pieces
		void Game::handleJumpPosition(const int rank, const int file) {
			emit positionDeselected(this->previousSelectedPosition_->getRank(), this->previousSelectedPosition_->getFile());
			emit positionSelected(rank, file);
			previousSelectedPosition_.reset();
			previousSelectedPosition_ = std::make_unique<Position>(rank, file);
		}

		// Handle the case where the newly selected position is the same as the previous one
		void Game::handleSamePosition(const int rank, const int file) {
			emit positionDeselected(rank, file);
			// Reset the previous selected position and update the game state
			previousSelectedPosition_.reset();
			stateManager_.setState(SelectionState::None);
		}

		// Handle a valid move, including capturing pieces and updating the game state
		void Game::handleValidMove(const Position& selectedPosition) {
			emit positionDeselected(this->previousSelectedPosition_->getRank(), this->previousSelectedPosition_->getFile());
			emit clearPieceImages();

			// Perform a capture if the selected position contains a piece
			if (getBoard()->containsPiece(selectedPosition)) {
				getBoard()->performCapture(*previousSelectedPosition_, selectedPosition);
			}
			else {
				// Otherwise, move the piece to the new position
				getBoard()->movePiece(*previousSelectedPosition_, selectedPosition);
			}

			// Emit signals for refreshing piece images and reset the previous selected position
			emit refreshPieceImages();
			previousSelectedPosition_.reset();
			stateManager_.setState(SelectionState::None);
		}

		// Check if the newly selected position is the same as the previously selected one
		bool Game::isSamePosition(const Position& selectedPosition) const {
			return selectedPosition == *previousSelectedPosition_;
		}

		// Check if the move is valid
		bool Game::isValidMove(const std::shared_ptr<Piece> previousPiece, const Position& selectedPosition) const {
			return getBoard()->isMoveValid(selectedPosition, previousPiece);
		}

		bool Game::isCurrentPlayerPieceColorMatch(const Position& selectedPosition) const {
			return this->playerState_.getCurrentPlayer() == this->getBoard()->getPieceAt(selectedPosition)->getColor();
		}

		const Position* Game::getSelectedPosition() const {
			return previousSelectedPosition_.get();
		}

		Board* Game::getBoard() const { 
			return board_.get();
		}

		std::map<int, constants::GameTag> Game::getGameMapping() {
			return gameMapping;
		}

		PlayerStateManager Game::getPlayerState() const {
			return playerState_;
		}


}

