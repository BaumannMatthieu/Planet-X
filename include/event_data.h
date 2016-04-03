#ifndef __EVENT_DATA_H__
#define __EVENT_DATA_H__

#include <SDL2/SDL.h>
#include "vector2.h"


class EventData {
    public:
        EventData();
        ~EventData();

        const Uint8* get_key_state() const;
        const Vector2<int>& get_mouse_coordinates() const;
        const Uint32 get_mouse_bitmask() const;
    
        void update_event_queue();
    private:
        
        Vector2<int> mouse_coordinates_;

        Uint32 mouse_bitmask_;
        const Uint8* key_state_;
};

#endif
