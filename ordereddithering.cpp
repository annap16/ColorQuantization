#include "ordereddithering.h"
#include <QImage>
#include <QColor>
#include <random>
#include <QPainter>

OrderedDithering::OrderedDithering(int _Kr, int _Kg, int _Kb,QImage* _image,  bool _random): DitheringAlgorithms(_Kr, _Kg, _Kb, _image)
{
    random = _random;
    ditheringMatrices = generateDitheringMatrices();
}

void OrderedDithering::drawImage(QPainter *painter)
{
    QVector3D vectorN = estimateN();
    QVector3D vectorNPow2 = vectorN*vectorN;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrX(0, static_cast<int>(vectorN.x())-1);
    std::uniform_int_distribution<> distrY(0, static_cast<int>(vectorN.y())-1);
    std::uniform_int_distribution<> distrZ(0, static_cast<int>(vectorN.z())-1);

    QImage processedImage = imageOrigin->copy();

    for(int y=0; y<imageOrigin->height(); y++)
    {
        for(int x =0; x<imageOrigin->width(); x++)
        {
            QColor currentColor = processedImage.pixelColor(x, y);

            QVector3D currentColorVec = QVector3D(
                round((currentColor.red() * (Kr - 1) / 255.0)*vectorNPow2.x()),
                round((currentColor.green() * (Kg - 1) / 255.0)*vectorNPow2.y()),
                round((currentColor.blue() * (Kb - 1) / 255.0)*vectorNPow2.z())
                );

            QVector3D color = currentColorVec/vectorNPow2;
            QVector3D re = QVector3D(
                ( static_cast<int>(currentColorVec.x())% static_cast<int>(vectorNPow2.x())),
                ( static_cast<int>(currentColorVec.y())% static_cast<int>(vectorNPow2.y())),
                ( static_cast<int>(currentColorVec.z())% static_cast<int>(vectorNPow2.z()))
                );
            QVector3D i, j;
            if(random)
            {
                i = QVector3D(distrX(gen), distrY(gen), distrZ(gen));
                j = QVector3D(distrX(gen), distrY(gen), distrZ(gen));

            }
            else
            {
                i = QVector3D(x % static_cast<int>(vectorN.x()),
                             x % static_cast<int>(vectorN.y()),
                             x % static_cast<int>(vectorN.z()));
                j = QVector3D(y % static_cast<int>(vectorN.x()),
                              y % static_cast<int>(vectorN.y()),
                              y % static_cast<int>(vectorN.z()));

            }


            int DnR = ditheringMatrices.find(vectorN.x())->second[i.x()][j.x()];
            int DnG = ditheringMatrices.find(vectorN.y())->second[i.y()][j.y()];
            int DnB = ditheringMatrices.find(vectorN.z())->second[i.z()][j.z()];

            if(re.x()>DnR)
            {
                color.setX(color.x()+1);
            }
            if(re.y()>DnG)
            {
                color.setY(color.y()+1);
            }
            if(re.z()>DnB)
            {
                color.setZ(color.z()+1);
            }
            int newR = round(color.x() * 255 / (Kr - 1));
            int newG = round(color.y() * 255 / (Kg - 1));
            int newB = round(color.z() * 255 / (Kb - 1));

            processedImage.setPixel(x, y, qRgb(newR, newG, newB));

        }
    }
    painter->drawImage(0, 0, processedImage);
    imageTransformed = processedImage.copy();
}

QVector3D OrderedDithering::estimateN()
{
    double nR = std::min(std::ceil(std::sqrt(256.0/(Kr-1.0))), 16.0);
    double nG = std::min(std::ceil(std::sqrt(256.0/(Kg-1.0))), 16.0);
    double nB = std::min(std::ceil(std::sqrt(256.0/(Kb-1.0))), 16.0);
    nR = std::max(nR, 2.0);
    nG = std::max(nG, 2.0);
    nB = std::max(nB, 2.0);

    nR = roundUpToAllowed(nR);
    nG = roundUpToAllowed(nG);
    nB = roundUpToAllowed(nB);

    return QVector3D(nR, nG, nB);
}

int OrderedDithering::roundUpToAllowed(double n)
{
    std::vector<int> allowedNumbers = {2, 3, 4, 6, 8, 12, 16};


    for(size_t i=0; i<allowedNumbers.size(); i++)
    {
        if(allowedNumbers[i]>=n)
        {
            return allowedNumbers[i];
        }
    }
        return allowedNumbers.back();
}



std::map<int, std::vector<std::vector<int>>> OrderedDithering::generateDitheringMatrices() {
    std::map<int, std::vector<std::vector<int>>> ditheringMatrices;

    ditheringMatrices[2] = {
        {0, 2},
        {3, 1}
    };

    ditheringMatrices[3] = {
        {6, 8, 4},
        {1, 0, 3},
        {5, 2, 7}
    };

    ditheringMatrices[4] = {
        {0, 8, 2, 10},
        {12, 4, 14, 6},
        {3, 11, 1, 9},
        {15, 7, 13, 5}
    };

    ditheringMatrices[6] = {
        {24, 32, 16, 26, 34, 18},
        {4, 0, 12, 6, 2, 14},
        {20, 8, 28, 22, 10, 30},
        {27, 35, 19, 25, 33, 17},
        {7, 3, 15, 5, 1, 13},
        {23, 11, 31, 21, 9, 29}
    };

    ditheringMatrices[8] = {
        {0, 32, 8, 40, 2, 34, 10, 42},
        {48, 16, 56, 24, 50, 18, 58, 26},
        {12, 44, 4, 36, 14, 46, 6, 38},
        {60, 28, 52, 20, 62, 30, 54, 22},
        {3, 35, 11, 43, 1, 33, 9, 41},
        {51, 19, 59, 27, 49, 17, 57, 25},
        {15, 47, 7, 39, 13, 45, 5, 37},
        {63, 31, 55, 23, 61, 29, 53, 21}
    };



    ditheringMatrices[12] = {
        {96, 128, 64, 104, 136, 72, 98, 130, 66, 106, 138, 74},
        {16, 0, 48, 24, 8, 56, 18, 2, 50, 26, 10, 58},
        {80, 32, 112, 88, 40, 120, 82, 34, 114, 90, 42, 122},
        {108, 140, 76, 100, 132, 68, 110, 142, 78, 102, 134, 70},
        {28, 12, 60, 20, 4, 52, 30, 14, 62, 22, 6, 54},
        {92, 44, 124, 84, 36, 116, 94, 46, 126, 86, 38, 118},
        {99, 131, 67, 107, 139, 75, 97, 129, 65, 105, 137, 73},
        {19, 3, 51, 27, 11, 59, 17, 1, 49, 25, 9, 57},
        {83, 36, 115, 91, 43, 123, 81, 33, 113, 89, 41, 121},
        {111, 143, 79, 103, 135, 71, 109, 141, 77, 101, 133, 69},
        {31, 15, 63, 23, 7, 55, 29, 13, 61, 21, 5, 53},
        {95, 47, 127, 87, 39, 119, 93, 45, 125, 85, 37, 117}
    };

    ditheringMatrices[16] = {
        {0, 128, 32, 160, 8, 136, 40, 168, 2, 130, 34, 162, 10, 138, 42, 170},
        {192, 64, 224, 96, 200, 72, 232, 104, 194, 66, 226, 98, 202, 74, 234, 106},
        {48, 176, 16, 144, 56, 184, 24, 152, 50, 178, 18, 146, 58, 186, 26, 154},
        {240, 112, 208, 80, 248, 120, 216, 88, 242, 114, 210, 82, 250, 122, 218, 90},
        {12, 140, 44, 172, 4, 132, 36, 164, 14, 142, 46, 174, 6, 134, 38, 166},
        {204, 76, 236, 108, 196, 68, 228, 100, 206, 78, 238, 110, 198, 70, 230, 102},
        {60, 188, 28, 156, 52, 180, 20, 148, 62, 190, 30, 158, 54, 182, 22, 150},
        {252, 124, 220, 92, 244, 116, 212, 84, 254, 126, 222, 94, 246, 118, 214, 86},
        {3, 131, 35, 163, 11, 139, 43, 171, 1, 129, 33, 161, 9, 137, 41, 169},
        {195, 67, 227, 99, 203, 75, 235, 107, 193, 65, 225, 97, 201, 73, 233, 105},
        {51, 179, 19, 147, 59, 187, 27, 155, 49, 177, 17, 145, 57, 185, 25, 153},
        {243, 115, 211, 83, 251, 123, 219, 91, 241, 113, 209, 81, 249, 121, 217, 89},
        {15, 143, 47, 175, 7, 135, 39, 167, 13, 141, 45, 173, 5, 133, 37, 165},
        {207, 79, 239, 111, 199, 71, 231, 103, 205, 77, 237, 109, 197, 69, 229, 101},
        {63, 191, 31, 159, 55, 183, 23, 151, 61, 189, 29, 157, 53, 181, 21, 149},
        {255, 127, 223, 95, 247, 119, 215, 87, 253, 125, 221, 93, 245, 117, 213, 85}

    };

    return ditheringMatrices;
}



