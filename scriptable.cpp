#include "scriptable.h"
#include <memory>

State::State(const ActionFunc& action_func) : action_func_(action_func) {
	
}

State::~State() {	

}

void State::execute() {
	action_func_(shared_from_this());
}

void State::set_next_state(const uint8_t next_state_key, const StatePtr next_state) {
	next_states_.insert(std::pair<uint8_t, StatePtr>(next_state_key, next_state));
}

const StatePtr State::get_next_state(const uint8_t key) {
	return next_states_[key];
}

Scriptable::Scriptable() {

}

Scriptable::~Scriptable() {

}

void Scriptable::execute() const {
	for(auto& state : current_states_) {
		state->execute();
	}	
}

