#pragma once
#ifndef GameModel_H
#define GameModel_H
#include <Qobject>
#include <memory>
#include <iostream>
#include <utility>
#include <map>

#include "Board.h"
#include "SelectedPieceState.h"
#include "PieceMover.h"
#include "LibConstants.h"
#include "PlayerState.h"

/*
* This program simulates a chess game model
* \file   Game.h
* \author Ahmed Sami Benabbou : 2122457 et Ilyes Jamoussi : 205854
* \date   27 avril 2024
* Créé le 3 mai 2024
*/

namespace model {
class Game :public QObject {
	Q_OBJECT
public:
	Game() = delete;
	explicit Game(const constants::GameTag& gameId);

	void addPiece(constants::Type type, model::Position position, model::Color color);
	void loadGame(const constants::GameTag& gameTag);

	void TopalovVsPolgar2008();
	void BudnikovVsNovik1991();
	void VladimorovVsPalatnik1977();

	void handlePieceSelection(const int rank, const int file);
	void handleNoneState(const int rank, const int file);
	void handleSelectedState(const int rank, const int file);
	void handleSamePosition(const int rank, const int file);
	void handleValidMove(const Position& selectedPosition);
	void handleJumpPosition(const int rank, const int file);

	bool isValidMove(const std::shared_ptr<Piece> previousPiece, const Position& selectedPosition) const;
	bool isSamePosition(const Position& selectedPosition) const;
	bool isCurrentPlayerPieceColorMatch(const Position& selectedPosition) const;

	void resetBoard();
	Board* getBoard() const;
	const Position* getSelectedPosition() const;
	std::map<int, constants::GameTag> getGameMapping();
	PlayerStateManager getPlayerState() const;

private:
	std::unique_ptr<Board> board_;
	std::unique_ptr<Position> previousSelectedPosition_ = nullptr;
	PiecesStateManager stateManager_;
	PlayerStateManager playerState_;
	std::map<int, constants::GameTag> gameMapping = { //change this after need to be static
			{0, constants::GameTag::TopalovVsPolgar2008},
			{1, constants::GameTag::BudnikovVsNovik1991 },
			{2, constants::GameTag::VladimorovVsPalatnik1977 },
	};

signals:
	void positionSelected(const int /*rank*/, const int  /*file*/);
	void positionDeselected(const int  /*rank*/, const int  /*file*/);
	void clearPieceImages();
	void refreshPieceImages();
	void checkMateSignal();
	void checkSignal();
	void currentPlayerSignal();
	void resetMessage();
	void drawSignal();
	void resetCurrentPlayerMessage();
	};


}


#endif