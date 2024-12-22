#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "imageitem.h"
#include "imagetransformation.h"
#include "algorithms.h"
#include "averagedithering.h"
#include "errordiffusiondithering.h"
#include "ordereddithering.h"
#include "popularityalgorithm.h"
#include <QGraphicsScene>
#include <QImage>
#include <QObject>
#include <QMessageBox>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sceneOrigin = new QGraphicsScene(this);
    ui->graphicsView_origin->setScene(sceneOrigin);
    sceneTransformed = new QGraphicsScene(this);
    ui->graphicsView_transformed->setScene(sceneTransformed);
    QString path = "../../story_lena_lenna";
    UploadImage(path);
    imageTrans = new ImageTransformation(sceneTransformed, originImage->image);
    sceneTransformed->addItem(imageTrans);
    ui->groupBox_paramsDithering->setEnabled(false);
    ui->groupBox_paramsPopularityAlg->setEnabled(false);
    ui->spinBox_Kr->setRange(1, 256);
    ui->spinBox_Kr->setValue(8);

    ui->spinBox_Kg->setRange(1, 256);
    ui->spinBox_Kg->setValue(8);

    ui->spinBox_Kb->setRange(1, 256);
    ui->spinBox_Kb->setValue(8);

    ui->spinBox_K->setRange(1, 16777216);
    ui->spinBox_K->setValue(80);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UploadImage(QString path)
{
    QImage* imageTemp = new QImage(path);
    if(imageTemp->isNull())
    {
        QMessageBox::warning(nullptr, "Error", "Unable to load ");
        delete imageTemp;
        imageTemp = nullptr;
        exit(1);
    }
    else
    {
        originImage = new ImageItem(imageTemp);
        sceneOrigin->addItem(static_cast<QGraphicsItem*>(originImage));
        sceneOrigin->update();
    }
}

void MainWindow::on_radioButton_avgDithering_toggled(bool checked)
{
    if(checked)
    {
        if(imageTrans->algorithm)
        {
            delete imageTrans->algorithm;
            imageTrans->algorithm=nullptr;
        }
        AverageDithering* alg = new AverageDithering(ui->spinBox_Kr->value(), ui->spinBox_Kg->value(), ui->spinBox_Kb->value(), imageTrans->image);
        imageTrans->setAlgorithm(alg);
        ui->groupBox_paramsPopularityAlg->setEnabled(false);
        ui->groupBox_paramsDithering->setEnabled(true);
    }
}




void MainWindow::on_spinBox_Kr_valueChanged(int arg1)
{
    auto* ditheringAlg = dynamic_cast<DitheringAlgorithms*>(imageTrans->algorithm);

    if (ditheringAlg)
    {
        ditheringAlg->Kr = arg1;
        sceneTransformed->update();
    }
}


void MainWindow::on_spinBox_Kg_valueChanged(int arg1)
{
    auto* ditheringAlg = dynamic_cast<DitheringAlgorithms*>(imageTrans->algorithm);

    if (ditheringAlg)
    {
        ditheringAlg->Kg = arg1;
        sceneTransformed->update();
    }

}


void MainWindow::on_spinBox_Kb_valueChanged(int arg1)
{
    auto* ditheringAlg = dynamic_cast<DitheringAlgorithms*>(imageTrans->algorithm);

    if (ditheringAlg)
    {
        ditheringAlg->Kb = arg1;
        sceneTransformed->update();
    }
}


void MainWindow::on_radioButton_errorDiffDithering_toggled(bool checked)
{
    if(checked)
    {
        if(imageTrans->algorithm)
        {
            delete imageTrans->algorithm;
        }
        ErrorDiffusionDithering* alg = new ErrorDiffusionDithering(ui->spinBox_Kr->value(), ui->spinBox_Kg->value(), ui->spinBox_Kb->value(), imageTrans->image);
        imageTrans->setAlgorithm(alg);
        ui->groupBox_paramsPopularityAlg->setEnabled(false);
        ui->groupBox_paramsDithering->setEnabled(true);
    }

}


void MainWindow::on_radioButton_orderedDitheringRandom_toggled(bool checked)
{
    if(checked)
    {
        if(imageTrans->algorithm)
        {
            delete imageTrans->algorithm;
        }
        OrderedDithering* alg = new OrderedDithering(ui->spinBox_Kr->value(), ui->spinBox_Kg->value(), ui->spinBox_Kb->value(), imageTrans->image, true);
        imageTrans->setAlgorithm(alg);
        ui->groupBox_paramsPopularityAlg->setEnabled(false);
        ui->groupBox_paramsDithering->setEnabled(true);
    }
}


void MainWindow::on_radioButton_orderedDitheringRelative_toggled(bool checked)
{
    if(checked)
    {
        if(imageTrans->algorithm)
        {
            delete imageTrans->algorithm;
        }
        OrderedDithering* alg = new OrderedDithering(ui->spinBox_Kr->value(), ui->spinBox_Kg->value(), ui->spinBox_Kb->value(), imageTrans->image, false);
        imageTrans->setAlgorithm(alg);
        ui->groupBox_paramsPopularityAlg->setEnabled(false);
        ui->groupBox_paramsDithering->setEnabled(true);
    }

}


void MainWindow::on_radioButton_popularityAlg_toggled(bool checked)
{
    if(checked)
    {
        if(imageTrans->algorithm)
        {
            delete imageTrans->algorithm;
            imageTrans->algorithm = nullptr;
        }
        PopularityAlgorithm* alg = new PopularityAlgorithm(ui->spinBox_K->value(), imageTrans->image);
        imageTrans->setAlgorithm(alg);
        alg->computeTheMostPopularColors();
        ui->groupBox_paramsPopularityAlg->setEnabled(true);
        ui->groupBox_paramsDithering->setEnabled(false);
    }
}


void MainWindow::on_pushButton_saveImage_clicked()
{
    if (!imageTrans || !imageTrans->algorithm || imageTrans->algorithm->imageTransformed.isNull())
    {
        QMessageBox::warning(nullptr, "Error", "No image available to save.");
        return;
    }

    QString folderPath = QFileDialog::getExistingDirectory(nullptr, "Choose directory", "");

    if (!folderPath.isEmpty())
    {
        QString baseFileName = "image.png";
        QString filePath = folderPath + "/" + baseFileName;

        int counter = 1;

        while (QFile::exists(filePath))
        {
            filePath = folderPath + "/" + "image-" + QString::number(counter++) + ".png";
        }

        bool success = imageTrans->algorithm->imageTransformed.save(filePath, "PNG");

        if (success)
        {
            QMessageBox::information(nullptr, "Success", "Image saved successfully!");
        } else
        {
            QMessageBox::warning(nullptr, "Error", "Failed to save the image.");
        }
    }
}



void MainWindow::on_pushButton_uploadImage_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Wybierz obraz", "", "Obrazy (*.png *.jpg *.jpeg);;Wszystkie pliki (*.*)");

    if (!filePath.isEmpty())
    {
        int sceneWidth = sceneOrigin->width();
        int sceneHeight = sceneOrigin->height();

        QImage* originalImage = new QImage(filePath);


        Qt::AspectRatioMode aspectRatioMode = Qt::KeepAspectRatio;
        *originalImage = originalImage->scaled(sceneWidth, sceneHeight, aspectRatioMode);


        if(originImage->image)
        {
            delete originImage->image;
            originImage->image = nullptr;
        }
        originImage->image = originalImage;
        imageTrans->image = originalImage;
        if(imageTrans->algorithm)
        {
            imageTrans->algorithm->imageOrigin = originalImage;
            auto* popularityAlg = dynamic_cast<PopularityAlgorithm*>(imageTrans->algorithm);

            if (popularityAlg)
            {
                popularityAlg->computeTheMostPopularColors();
            }
        }


        sceneOrigin->update();
        sceneTransformed->update();
    }
}


void MainWindow::on_spinBox_K_valueChanged(int arg1)
{
    auto* popularityAlg = dynamic_cast<PopularityAlgorithm*>(imageTrans->algorithm);

    if (popularityAlg)
    {
        popularityAlg->K = arg1;
        popularityAlg->computeTheMostPopularColors();
        sceneTransformed->update();
    }
}


void MainWindow::on_pushButton_create_clicked()
{
    if(originImage->image)
    {
        delete originImage->image;
        originImage->image;
    }
    int height = 500;
    int width = 500;
    QImage* createImage = new QImage(width, height,  QImage::Format_ARGB32);
    createImage->fill(Qt::black);

    originImage->image = createImage;
    imageTrans->image = createImage;

    QRgb white = qRgb(255, 255, 255);
    QRgb black = qRgb(0, 0, 0);
    int rectSize = height/10;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++) {
            bool isBlack = ((x / rectSize) + (y / rectSize)) % 2 == 0;
            createImage->setPixel(x, y, isBlack ? black : white);
        }
    }

    int start=150;
    int end = 350;
    int h=0;
    int s=0;
    int v = 255;
    for(int y=start; y<end; y++)
    {
        h=0;
        for(int x=start; x<end; x++)
        {
            QColor color = QColor::fromHsv(h, s, v);
            QRgb rgbColor = color.rgb();
            createImage->setPixel(x, y,rgbColor);
            h = (h + 1) % 360;
        }
        s = (s + 1) % 256;

    }
    if(imageTrans->algorithm)
    {
        imageTrans->algorithm->imageOrigin = createImage;
        auto* popularityAlg = dynamic_cast<PopularityAlgorithm*>(imageTrans->algorithm);

        if (popularityAlg)
        {
            popularityAlg->computeTheMostPopularColors();
        }
    }


    sceneOrigin->update();
    sceneTransformed->update();

}

