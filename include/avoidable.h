#ifndef __AVOIDABLE_H__
#define __AVOIDABLE_H__

#include <memory>
#include <set>
#include "rectangle.h"
#include "circle.h"

class Avoidable;
typedef std::shared_ptr<Avoidable> AvoidablePtr;

class Avoidable {
    public:
        Avoidable(const Rectangle& rect);
        virtual ~Avoidable();

        const Circle& get_circle() const;

        static const AvoidablePtr get_most_threatening_obstacle(const AvoidablePtr& this_entity, const Point& position, const Point& ahead, const Point& ahead2, const std::set<AvoidablePtr>& avoidables);
    
    protected:
        Circle circle_;
};


#endif
