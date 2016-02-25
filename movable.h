#ifndef __MOVABLE_H__
#define __MOVABLE_H__

class Movable {
    public:
       	virtual void move() = 0;

    protected:
		virtual const Vector2<float> compute_force() const = 0;
	
    protected:
		Vector2<float> acceleration_;
		Vector2<float> velocity_;
		float mass_;
};

#endif
