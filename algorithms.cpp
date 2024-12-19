#include "algorithms.h"
#include <QImage>

Algorithms::Algorithms() {}

Algorithms::Algorithms(QImage* _image)
{
    imageOrigin = _image;
}
bool Algorithms::isWithinBound(int x, int y)
{
    if(x>0 && y>0 && x<imageOrigin->width() && y<imageOrigin->height())
    {
        return true;
    }
    return false;
}


