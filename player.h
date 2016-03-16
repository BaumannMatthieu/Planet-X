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
    
        bool is_player() const;

    private:
        bool stopped_;
        bool ready_to_cast_;
        float k_;
        Point focus_;

        Point mouse_;
};

typedef std::shared_ptr<Player> PlayerPtr;

#endif
