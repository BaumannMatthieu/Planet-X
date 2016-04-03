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
			SHIELDING,
            AVOIDANCE,
            FOLLOW_LEADER
		};

	public:
		State(const uint8_t key, const std::function<void(const std::shared_ptr<State>)>& action_func);
		~State();

		void execute();
		const std::shared_ptr<State> get_next_state(const uint8_t key);
		void set_next_state(const uint8_t next_state_key, const std::shared_ptr<State> next_state);
	
        const uint8_t get_key() const;
        
    private:
	    const uint8_t key_;

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

        void set_current_states(const std::set<StatePtr> current_states);

        void insert_state(const StatePtr state);
        void erase_state(const StatePtr state);
        
        bool is_current_state(const uint8_t key) const;
	protected:
		std::set<StatePtr> current_states_;
};

#endif
