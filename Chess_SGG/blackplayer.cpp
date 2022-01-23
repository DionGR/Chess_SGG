#include "blackplayer.h"

BlackPlayer* BlackPlayer::m_instance = nullptr;


/* Constructs the BlackPlayer class once, returns the same instance afterwards. */
BlackPlayer* BlackPlayer::getInstance()
{
	if (!m_instance)
		m_instance = new BlackPlayer();
	return m_instance;
}

/* Releases the current active BlackPlayer instance, freeing all dynamic memory. */
void BlackPlayer::releaseInstance()
{
	if (m_instance) delete m_instance;
}
