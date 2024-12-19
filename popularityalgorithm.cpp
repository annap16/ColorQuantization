#include "popularityalgorithm.h"
#include <QDebug>
#include <QPainter>
#include <QVector3D>
#include <QStatusBar>
#include <QApplication>

PopularityAlgorithm::PopularityAlgorithm(int _K, QImage* _image): Algorithms(_image)
{
    K = _K;
    computeTheMostPopularColors();
}


bool operator<(const QColor & a, const QColor & b) {
    return a.redF() < b.redF()
    || a.greenF() < b.greenF()
        || a.blueF() < b.blueF()
        || a.alphaF() < b.alphaF();
}

void PopularityAlgorithm::computeTheMostPopularColors()
{
    colorHistogram.clear();
    topKColors.clear();

    for(int y=0; y<imageOrigin->height(); y++)
    {
        for(int x=0; x<imageOrigin->width(); x++)
        {
            const QColor color = imageOrigin->pixelColor(x, y);
            colorHistogram[color]++;
        }
    }

    QVector<QPair<QColor, int>> histogramVector;
    for (auto it = colorHistogram.begin(); it != colorHistogram.end(); it++)
    {
        histogramVector.append(qMakePair(it.key(), it.value()));
    }

    std::sort(histogramVector.begin(), histogramVector.end(),
              [](const QPair<QColor, int> &a, const QPair<QColor, int> &b) {
                  return a.second > b.second;
              });

    for (int i = 0; i < K && i < histogramVector.size(); i++)
    {
        QColor color = histogramVector[i].first;
        topKColors.push_back(color);
    }

}


QColor PopularityAlgorithm::findClosestColor(QColor pixelColor)
{
    double minDistance = std::pow(pixelColor.red()-topKColors[0].red(), 2)+std::pow(pixelColor.green()-topKColors[0].green(),2) + std::pow(pixelColor.blue() - topKColors[0].blue(),2);
    QColor closestColor = topKColors[0];
    double distance;
    for(int i=1; i<topKColors.size(); i++)
    {
        distance = std::pow(pixelColor.red()-topKColors[i].red(), 2)+std::pow(pixelColor.green()-topKColors[i].green(),2) + std::pow(pixelColor.blue() - topKColors[i].blue(),2);
        if(distance<minDistance)
        {
            minDistance = distance;
            closestColor = topKColors[i];
        }
    }

    return closestColor;
}




void PopularityAlgorithm::drawImage(QPainter *painter)
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    QImage processedImage = imageOrigin->copy();

    for(int y=0; y<imageOrigin->height(); y++)
    {
        for(int x=0; x<imageOrigin->width();x++)
        {
            QColor pixelColor = imageOrigin->pixelColor(x, y);
            QColor newColor = findClosestColor(pixelColor);
            processedImage.setPixel(x, y, qRgb(newColor.red(), newColor.green(), newColor.blue()));
        }
    }
    painter->drawImage(0, 0, processedImage);
    imageTransformed = processedImage.copy();
    QApplication::restoreOverrideCursor();


}



