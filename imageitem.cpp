#include "imageitem.h"
#include <QPainter>

ImageItem::ImageItem(QImage* _image)
{
    image = _image;
}

void ImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (image)
    {
        painter->drawImage(0, 0, *image);
    }

}

QRectF ImageItem::boundingRect() const {
    if (image && !image->isNull())
    {
        return QRectF(0, 0, image->width(), image->height());
    }
    return QRectF();
}


