#ifndef IMAGETRANSFORMATION_H
#define IMAGETRANSFORMATION_H
#include <QGraphicsItem>
#include <imageitem.h>

class QGraphicsScene;
class Algorithms;

class ImageTransformation: public ImageItem
{
public:
    ImageTransformation(QGraphicsScene* _scene, QImage* _image);
    QGraphicsScene* sceneTransformed;
    Algorithms* algorithm;
    void setAlgorithm(Algorithms* _algorithm);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // IMAGETRANSFORMATION_H
