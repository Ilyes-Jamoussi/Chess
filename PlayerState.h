#pragma once
#include "LibConstants.h"
#include "Color.h"

#pragma once

#ifndef PlayerState_H
#define PlayerState_H

namespace model {
	class PlayerStateManager {
	public:

		PlayerStateManager() : currentState_(constants::White) {}

		void transition() {
			currentState_ = (currentState_ == Color{ constants::White }) ? Color{ constants::Black } : Color{ constants::White};
		}

		Color getCurrentPlayer() const { return currentState_; }

		bool isWhite() {
			return currentState_ == Color{ constants::White };
		}

		void setState(Color newState) { currentState_ = newState; }

	private:
		Color currentState_{ constants::White };  // Current state of the player
	};
}



#endif