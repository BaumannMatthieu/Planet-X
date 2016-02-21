#include "event_handler.h"

EventHandler::EventHandler() {

}

EventHandler::~EventHandler() {

}

void EventHandler::add(const SDL_EventType& event_type,
	       	       const Callback& callback) {
	events_map_[event_type].push_back(callback);
}

void EventHandler::handle(const SDL_Event& event) {
	const SDL_EventType event_type = static_cast<SDL_EventType>(event.type);
	
	for(auto& callback_event : events_map_[event_type]) {
		callback_event(event);
	}
}

