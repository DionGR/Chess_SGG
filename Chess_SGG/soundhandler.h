#pragma once

#include "global.h"

class SoundHandler {
public:
	static void menuMusic() { graphics::playMusic(MENU_MUSIC, 0.15f); }
	static void stopMusic() { graphics::stopMusic(); }

	static void startGame() { graphics::playSound(START_GAME_EFFECT, 1.0f); }

	static void pieceMoved() { graphics::playSound(PIECE_MOVED_EFFECT, 1.0f); }
	static void pieceCaptured() { graphics::playSound(PIECE_CAPTURED_EFFECT, 1.0f); }
	static void check() { graphics::playSound(CHECK_EFFECT, 1.0f); }
};
