#ifndef __MOVABLE_H__
#define __MOVABLE_H__

class Movable {
    public:
       	virtual void move() = 0;

    protected:
		Vector2<float> force_;
		Vector2<float> acceleration_;
		Vector2<float> velocity_;
        float max_velocity_;
        float max_force_;
		
		float mass_;
};

#endif
