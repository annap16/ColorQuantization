#include "errordiffusiondithering.h"
#include <QImage>
#include <QPainter>

ErrorDiffusionDithering::ErrorDiffusionDithering(int _Kr, int _Kg, int _Kb, QImage* _image): DitheringAlgorithms(_Kr, _Kg, _Kb, _image)
{
    filter[0][0] = 0.0f;
    filter[0][1] = 0.0f;
    filter[0][2] = 7.0f / 16.0f;

    filter[1][0] = 3.0f / 16.0f;
    filter[1][1] = 5.0f / 16.0f;
    filter[1][2] = 1.0f / 16.0f;

    filter[2][0] = 0.0f;
    filter[2][1] = 0.0f;
    filter[2][2] = 0.0f;

}

void ErrorDiffusionDithering::drawImage(QPainter *painter)
{
    QVector3D steps = QVector3D(static_cast<int>(256 / Kr), static_cast<int>(256 / Kg),static_cast<int>(256 / Kb));
    QImage processedImageS = imageOrigin->copy();
    QImage processedImageI = imageOrigin->copy();

    for(int y=0; y<imageOrigin->height(); y++)
    {
        for(int x =0; x<imageOrigin->width(); x++)
        {
            QColor currentColor = processedImageS.pixelColor(x, y);
            QVector3D originalColors(currentColor.red(), currentColor.green(), currentColor.blue());
            QVector3D approxColorsVec = colorsTransformaiton(originalColors, steps);
            QVector3D error = originalColors-approxColorsVec;
            QColor approximatedColor(approxColorsVec.x(), approxColorsVec.y(), approxColorsVec.z());
            processedImageI.setPixel(x, y, qRgb(approximatedColor.red(), approximatedColor.green(), approximatedColor.blue()));

            int fx = 1;
            int fy = 1;
            for(int i = -fx; i<=fx; i++)
            {
                for(int j=-fy; j<=fy; j++)
                {
                    if(isWithinBound(x+i, y+j))
                    {
                        QColor neighborColor = processedImageS.pixelColor(x+i, y+j);
                        int newRed = qBound(0, neighborColor.red() + static_cast<int>(error.x() * filter[i + fx][j + fy]), 255);
                        int newGreen = qBound(0, neighborColor.green() + static_cast<int>(error.y() * filter[i + fx][j + fy]), 255);
                        int newBlue = qBound(0, neighborColor.blue() + static_cast<int>(error.z() * filter[i + fx][j + fy]), 255);
                        neighborColor.setRed(newRed);
                        neighborColor.setGreen(newGreen);
                        neighborColor.setBlue(newBlue);
                        processedImageS.setPixel(x+i, y+j, qRgb(neighborColor.red(), neighborColor.green(), neighborColor.blue()));
                    }
                }
            }

        }
    }

    painter->drawImage(0, 0, processedImageI);
    imageTransformed = processedImageI.copy();
}

