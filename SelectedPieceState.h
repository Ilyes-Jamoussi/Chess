#pragma once

#ifndef SelectedPieceState_H
#define SelectedPieceState_H



enum class SelectionState {
	None,        // No piece selected
	Selected,    // A piece is selected
	Disabled,
};

class PiecesStateManager {
public:

	PiecesStateManager() : currentState_(SelectionState::None) {}

	void transition(SelectionState newState) { currentState_ = newState; }

	SelectionState getCurrentState() const { return currentState_; }
	void setState(SelectionState nextState) { currentState_ = nextState; }
private:
	SelectionState currentState_{ SelectionState::None };  // Current state of the piece
};



#endif