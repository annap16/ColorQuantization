#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <QImage>
class QPainter;

class Algorithms
{
public:
    Algorithms();
    Algorithms(QImage* image);
    QImage* imageOrigin;
    QImage imageTransformed;
    virtual void drawImage(QPainter *painter)=0;
    bool isWithinBound(int x, int y);
};

#endif // ALGORITHM_H
