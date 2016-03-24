#include "scriptable.h"
#include <memory>

State::State(const uint8_t key, const ActionFunc& action_func) : key_(key), action_func_(action_func) {
	
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

const uint8_t State::get_key() const {
    return key_;
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

void Scriptable::set_current_states(const std::set<StatePtr> current_states) {
    current_states_.clear();
    current_states_ = current_states;
}

bool Scriptable::is_current_state(const uint8_t key) const {
    for(auto& state : current_states_) {
        if(state->get_key() == key) {
            return true;
        }
    }
    return false;
}

void Scriptable::insert_state(const StatePtr state) {
    current_states_.insert(state);
}

void Scriptable::erase_state(const StatePtr state) {
    current_states_.erase(state);
} 
