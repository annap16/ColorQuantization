#ifndef ERRORDIFFUSIONDITHERING_H
#define ERRORDIFFUSIONDITHERING_H
#include "ditheringalgorithms.h"
#include <QMatrix3x3>
#include <QColor>

class ErrorDiffusionDithering: public DitheringAlgorithms
{
public:
    ErrorDiffusionDithering(int _Kr, int _Kg, int _Kb, QImage* _image);
    float filter[3][3];
    void drawImage(QPainter *painter) override;
};

#endif // ERRORDIFFUSIONDITHERING_H
