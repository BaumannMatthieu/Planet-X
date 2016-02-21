#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

class Renderable {
	public:
		Renderable() { }
		virtual ~Renderable() { }

		virtual void draw(SDL_Renderer* renderer) = 0;
};

#endif
