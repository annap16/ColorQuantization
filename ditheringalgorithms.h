#ifndef DITHERINGALGORITHMS_H
#define DITHERINGALGORITHMS_H
#include "algorithms.h"
#include <QColor>
#include <QVector3D>
class DitheringAlgorithms: public Algorithms
{
public:
    DitheringAlgorithms(int _Kr, int _Kg, int _Kb, QImage* image);
    int Kr;
    int Kg;
    int Kb;
    QVector3D colorsTransformaiton(QVector3D colors, QVector3D steps);
};

#endif // DITHERINGALGORITHMS_H
