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

        void init_missile_handler();
		
        void update();
        void register_events();
    
        bool is_player() const;

        void cast_missile(const Vector2<float>& direction) const;
    private:
        bool stopped_;
        float k_;
        Point focus_;
        Point dir_;
};

typedef std::shared_ptr<Player> PlayerPtr;

#endif
