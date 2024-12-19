#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QGraphicsScene;
class ImageItem;
class ImageTransformation;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QGraphicsScene* sceneOrigin;
    QGraphicsScene* sceneTransformed;
    ImageItem* originImage;
    ImageTransformation* imageTrans;
    void UploadImage(QString path);

private slots:
    void on_radioButton_avgDithering_toggled(bool checked);

    void on_spinBox_Kr_valueChanged(int arg1);

    void on_spinBox_Kg_valueChanged(int arg1);

    void on_spinBox_Kb_valueChanged(int arg1);

    void on_radioButton_errorDiffDithering_toggled(bool checked);

    void on_radioButton_orderedDitheringRandom_toggled(bool checked);

    void on_radioButton_orderedDitheringRelative_toggled(bool checked);

    void on_radioButton_popularityAlg_toggled(bool checked);


    void on_pushButton_saveImage_clicked();

    void on_pushButton_uploadImage_clicked();

    void on_spinBox_K_valueChanged(int arg1);

    void on_pushButton_create_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
