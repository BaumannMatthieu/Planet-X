#ifndef __MOVABLE_H__
#define __MOVABLE_H__

class Movable {
    	public:
        	virtual void move() = 0;

	protected:
		float acceleration_;
		float velocity_;
		float mass_;

		virtual float compute_force() const = 0;
};

#endif
