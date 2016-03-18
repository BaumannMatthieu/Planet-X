#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

#include <SDL2/SDL.h>
#include <map>
#include <vector>
#include <functional>
#include <iostream>

#include "event_data.h"

typedef std::function<void(const EventData&)> Callback;

class EventHandler {
	public:
		EventHandler();
		~EventHandler();
	
		void add(const SDL_EventType& event_type,
    			 const Callback& callback);

		void handle(const EventData& event_data);
	private:
		std::map<SDL_EventType, std::vector<Callback>> events_map_;
};

#endif
