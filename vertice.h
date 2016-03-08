#ifndef __VERTICE_H__
#define __VERTICE_H__

#include "collisable.h"
#include "rectangle.h"

class Vertice : public Collisable {
    public:
        Vertice(const Point& point);
        virtual ~Vertice();
    
        const Point& get_position() const;
        virtual bool compute(const Rectangle& rect) const;

    protected:
        Point point_;
};

#endif
