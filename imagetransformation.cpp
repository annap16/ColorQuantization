#include "imagetransformation.h"
#include "algorithms.h"

#include <QGraphicsScene>

ImageTransformation::ImageTransformation(QGraphicsScene* _scene, QImage* _image): ImageItem(_image)
{
    sceneTransformed = _scene;
    algorithm = nullptr;
}
// TODO DELETE TRANSFORMEDIMAGE BO WYCIEK

void ImageTransformation::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(algorithm)
    {
        algorithm->drawImage(painter);
    }
}

void ImageTransformation::setAlgorithm(Algorithms* _algorithm)
{
    algorithm = _algorithm;
    sceneTransformed->update();
}



