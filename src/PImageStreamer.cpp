#include "include/PImageStreamer.h"

PImageStreamer::PImageStreamer(QObject *parent)
    : QObject{parent}
{

}

void PImageStreamer::LoadImage()
{
    /*QString Imagename = QFileDialog::getOpenFileName(
                    this,
                    tr("Open Images"),
                    "C://",
                    tr("Tiff Files (*.tif);; Raw file (*.raw)"));

     if ( Imagename.isNull())
        {
             QMessageBox::warning(this,"Error!","Image not valid!");
        }*/
}
