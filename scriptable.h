#ifndef __SCRIPTABLE_H__
#define __SCRIPTABLE_H__

#include <memory>

class State {
	public:
		State(const std::function<void()>& action_func);
		~State();

		const StatePtr execute() const;

		void set_next_state(const std::shared_ptr<State> next_state);
	private:
		std::vector<std::shared_ptr<State>> next_states_;
		std::function<void()> action_func_;

		bool finished_;
};

typedef std::shared_ptr<State> StatePtr;

class Scriptable {
	public:
		Scriptable(const StatePtr action_func);
		~Scriptable();

		void execute() const;

	private:
		std::set<StatePtr> current_states_;
};

#endif
