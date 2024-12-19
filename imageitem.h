#ifndef IMAGEITEM_H
#define IMAGEITEM_H
#include <QGraphicsItem>

class QImage;

class ImageItem: public QGraphicsItem
{
public:
    ImageItem()=default;
    ImageItem(QImage* _image);
    QImage* image;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
};

#endif // IMAGEITEM_H
