#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <memory>
#include "ship.h"
#include "event_registrable.h"

class Player : public Ship,
               public EventRegistrable {
	public:
		Player();
		virtual ~Player();

		void update();
        void register_events();

    private:
        bool stopped_;
        float k_;
        Point focus_;
};

typedef std::shared_ptr<Player> PlayerPtr;

#endif