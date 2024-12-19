#ifndef POPULARITYALGORITHM_H
#define POPULARITYALGORITHM_H
#include "algorithms.h"
#include <QMap>
#include <QColor>
#include <QVector>

class PopularityAlgorithm: public Algorithms
{
public:
    PopularityAlgorithm(int _K, QImage* _image);
    int K;
    QMap<QColor, int> colorHistogram;
    QVector<QColor> topKColors;
    void drawImage(QPainter *painter) override;
    void computeTheMostPopularColors();
    QColor findClosestColor(QColor pixelColor);
};

#endif // POPULARITYALGORITHM_H
