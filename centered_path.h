#ifndef __CENTERED_PATH_H__
#define __CENTERED_PATH_H__

#include <memory>
#include "path.h"

class CenteredPath : public Path {
    public:
        CenteredPath(const Point& center);
        ~CenteredPath();

        void update(const Point& new_center);

    private:
        Point center_;        
};

typedef std::shared_ptr<CenteredPath> CenteredPathPtr;

#endif
