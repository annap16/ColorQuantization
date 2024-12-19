#include "ditheringalgorithms.h"

DitheringAlgorithms::DitheringAlgorithms(int _Kr, int _Kg, int _Kb, QImage* _image): Algorithms(_image)
{
    Kr = _Kr;
    Kg = _Kg;
    Kb = _Kb;
}

QVector3D DitheringAlgorithms::colorsTransformaiton(QVector3D colors, QVector3D steps)
{
    QVector3D integerPart;
    QVector3D moduloPart;
    for(int i=0; i<3; i++)
    {
        integerPart[i] = floor(colors[i]/steps[i]);
        moduloPart[i] = static_cast<int>(colors[i])%static_cast<int>(steps[i]);
    }
    for(int i=0; i<3; i++)
    {
        if(moduloPart[i]>=steps[i]/2)
        {
            integerPart[i]++;
        }
        integerPart[i] = integerPart[i]*steps[i];
    }
    for(int i=0;i<3;i++)
    {
        if(integerPart[i]>255)
        {
            integerPart[i]=255;
        }
    }
    return integerPart;
}


