#ifndef __SCRIPTABLE_H__
#define __SCRIPTABLE_H__

#include <memory>
#include <iostream>
#include <set>
#include <map>

class State : public std::enable_shared_from_this<State> {
	public:
		enum {
			WANDERING, 
			ATTACK_DISPLACEMENT,
			ATTACKING, 
			FEARING,
			SHIELDING
		};

	public:
		State(const std::function<void(const std::shared_ptr<State>)>& action_func);
		~State();

		void execute();
		const std::shared_ptr<State> get_next_state(const uint8_t key);
		void set_next_state(const uint8_t next_state_key, const std::shared_ptr<State> next_state);
	private:
		std::map<uint8_t, std::shared_ptr<State>> next_states_;
		std::function<void(const std::shared_ptr<State>)> action_func_;
};

typedef std::shared_ptr<State> StatePtr;
typedef std::function<void(const StatePtr)> ActionFunc;

class Scriptable {
	public:
		Scriptable();
		~Scriptable();

		void execute() const;

	protected:
		std::set<StatePtr> current_states_;
};

#endif
