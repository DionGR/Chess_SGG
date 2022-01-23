#include "WhitePlayer.h"

WhitePlayer* WhitePlayer::m_instance = nullptr;


/* Constructs the WhitePlayer class once, returns the same instance afterwards. */
WhitePlayer* WhitePlayer::getInstance()
{
	if (!m_instance)
		m_instance = new WhitePlayer();
	return m_instance;
}

/* Releases the current active WhitePlayer instance, freeing all dynamic memory. */
void WhitePlayer::releaseInstance()
{
	if (m_instance) delete m_instance;
}
