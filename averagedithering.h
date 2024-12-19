#ifndef AVERAGEDITHERING_H
#define AVERAGEDITHERING_H
#include "ditheringalgorithms.h"
#include <QVector3D>

class AverageDithering: public DitheringAlgorithms
{
public:
    AverageDithering(int _Kr, int _Kg, int _Kb, QImage* _image);
    void drawImage(QPainter *painter) override;
    QVector3D neighborColorsAVG(int x, int y);
};

#endif // AVERAGEDITHERING_H
