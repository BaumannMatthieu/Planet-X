#include "../include/event_handler.h"

EventHandler::EventHandler() {

}

EventHandler::~EventHandler() {

}

void EventHandler::add(const SDL_EventType& event_type,
	       	           const Callback& callback) {
	events_map_[event_type].push_back(callback);
}

void EventHandler::handle(const EventData& event_data) {
    for(auto& callbacks_event_type : events_map_) {	
	    for(auto& callback_event : callbacks_event_type.second) {
		    callback_event(event_data);
	    }
    }
}

