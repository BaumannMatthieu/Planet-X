#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <memory>
#include "ship.h"
#include "event_registrable.h"

class Player : public Ship,
               public EventRegistrable {
	public:
		Player(const Rectangle& box);
		virtual ~Player();

		void update();
        void register_events();
};

typedef std::shared_ptr<Player> PlayerPtr;

#endif
