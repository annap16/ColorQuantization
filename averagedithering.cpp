#include "averagedithering.h"
#include "algorithms.h"
#include "ditheringalgorithms.h"
#include <QDebug>
#include <QImage>
#include <QPainter>

AverageDithering:: AverageDithering(int _Kr, int _Kg, int _Kb, QImage* _image):DitheringAlgorithms(_Kr, _Kg, _Kb, _image)
{
}

void AverageDithering::drawImage(QPainter *painter)
{

    QImage processedImage = imageOrigin->copy();

    QVector3D steps = QVector3D(static_cast<int>(256 / Kr), static_cast<int>(256 / Kg),static_cast<int>(256 / Kb));

    for (int y = 0; y < processedImage.height(); y++)
    {
        for (int x = 0; x < processedImage.width(); x++)
        {
            QVector3D avgColors = neighborColorsAVG(x, y);
            QVector3D transformedColors = colorsTransformaiton(avgColors, steps);
            processedImage.setPixel(x, y, qRgb(transformedColors.x(), transformedColors.y(), transformedColors.z()));
        }
    }
    painter->drawImage(0, 0, processedImage);
    imageTransformed = processedImage.copy();

}


QVector3D AverageDithering::neighborColorsAVG(int x, int y)
{
    int avgR, avgG, avgB;
    int neighborCount = 0;
    QColor neighbor1(0, 0, 0, 0);
    QColor neighbor2(0, 0, 0, 0);
    QColor neighbor3(0, 0, 0, 0);
    QColor neighbor4(0, 0, 0, 0);
    QColor neighbor5(0, 0, 0, 0);
    QColor neighbor6(0, 0, 0, 0);
    QColor neighbor7(0, 0, 0, 0);
    QColor neighbor8(0, 0, 0, 0);


    if(x-1>0 && y-1>0)
    {
        neighbor1 = imageOrigin->pixelColor(x-1, y-1);
        neighborCount++;
    }
    if(x-1>0)
    {
        neighbor2 = imageOrigin->pixelColor(x-1, y);
        neighborCount++;

    }
    if(x-1>0 && y+1<imageOrigin->height())
    {
        neighbor3 = imageOrigin->pixelColor(x-1, y+1);
        neighborCount++;
    }
    if(y-1>0)
    {
        neighbor4 = imageOrigin->pixelColor(x, y-1);
        neighborCount++;
    }
    if(y+1<imageOrigin->height())
    {
        neighbor5 = imageOrigin->pixelColor(x, y+1);
        neighborCount++;
    }
    if(x+1<imageOrigin->width() && y-1>0)
    {
        neighbor6 = imageOrigin->pixelColor(x+1, y-1);
        neighborCount++;
    }
    if(x+1<imageOrigin->width())
    {
        neighbor7 = imageOrigin->pixelColor(x+1, y);
        neighborCount++;
    }
    if(x+1<imageOrigin->width() && y+1<imageOrigin->height())
    {
        neighbor8 = imageOrigin->pixelColor(x+1, y+1);
        neighborCount++;
    }

    avgR = (neighbor1.red() + neighbor2.red() + neighbor3.red() + neighbor4.red() + neighbor5.red() + neighbor6.red() + neighbor7.red() + neighbor8.red())/neighborCount;
    avgG = (neighbor1.green() + neighbor2.green() + neighbor3.green() + neighbor4.green() + neighbor5.green() + neighbor6.green() + neighbor7.green() + neighbor8.green())/neighborCount;
    avgB = (neighbor1.blue() + neighbor2.blue() + neighbor3.blue() + neighbor4.blue() + neighbor5.blue() + neighbor6.blue() + neighbor7.blue() + neighbor8.blue())/neighborCount;

    return QVector3D(avgR, avgG, avgB);

}




