#ifndef ORDEREDDITHERING_H
#define ORDEREDDITHERING_H
//#include "algorithms.h"
#include "ditheringalgorithms.h"
#include <QVector3D>
#include <map>
class QImage;

class OrderedDithering: public DitheringAlgorithms
{
public:
    OrderedDithering(int _Kr, int _Kg, int _Kb, QImage* _image, bool _random);
    bool random;
    std::map<int, std::vector<std::vector<int>>> ditheringMatrices;
    void drawImage(QPainter *painter) override;
    QVector3D estimateN();
    int roundUpToAllowed(double n);
    std::map<int, std::vector<std::vector<int>>> generateDitheringMatrices();

};

#endif // ORDEREDDITHERING_H
