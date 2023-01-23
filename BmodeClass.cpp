#include "BmodeClass.h"
using namespace std;

BmodeClass::BmodeClass()
{
    imparams = NULL; // Define imparams, RFData, and next to NULL 
    RFData = NULL;
    next = NULL;
    line = 0; //Define line equal to zero
}

BmodeClass::BmodeClass(imageParam *params,dataBuffer *data,int numline)
{
    imparams = params; //Set imparams, RFData, and line equal to its counterpart parameters
    RFData = data;
    line = numline;
    scanline = createScanline(imparams->getNumPixel()); //Call createScanLine to allocate memory for scanline
    beamform(); //Call beamform to beamform the scanline
}

BmodeClass::~BmodeClass()
{
    deleteScanline(); //Release the arrays dynamically allocated for scanline
}

float *BmodeClass::createScanline(int numPixel)
{
    float* mem = new float[numPixel]; //Declare mem as a float pointer and define it as a new float array
    return mem; // Return mem
}

void BmodeClass::beamform()
{
    float tForward = 0.0; //Reset all floats to 0
    float tBackward = 0.0;
    float tTotal = 0.0;
    float sampling = 0.0;
    float pReal = 0.0;
    float pImag = 0.0;

    for (int i = 0; i < imparams->getNumPixel(); ++i) //Nested for loop to iterate through 2D array
    {
        for (int j = 0; j < imparams->getNumElement(); ++j)
        {
            tForward = (imparams->getYPosition(line,i))/(imparams->SOS); //tForward is located here since its a 1D array

            tBackward = (sqrt(pow(imparams->getYPosition(line,i),2)+ pow(imparams->getXPosition(line,i) - imparams->getElementPosition(j),2)))/(imparams->SOS); //Use equation given in assignment

            tTotal = tForward + tBackward;

            sampling = floor(tTotal*(imparams->FS));

            if (sampling > imparams->getNumSample())
            {
                cerr << "Invalid sample number" << endl; //Prints out error message to user if sampling number is greater than the number of samples
            }

            if (sampling < imparams->getNumSample())
            {
                pReal += (RFData->getRealRFData(j,sampling)); //Calulating pReal and pImag
                pImag += (RFData->getImagRFData(j,sampling));
            }

        }

        scanline[i] = sqrt(pow(pReal,2) + pow(pImag,2)); //Storing values in scanline array, calculates the echo magnitude

        pReal = 0.0; //Reset pReal and pImag
        pImag = 0.0;

    }
}

void BmodeClass::getScanline(float *data)
{
    for (int i = 0; i < imparams->getNumPixel(); i++) //Iterates through scanline
    {
        data[i] = scanline[i]; //Copy content from scanline to data element-by-element
    }
}

void BmodeClass::deleteScanline()
{
    delete scanline;
}