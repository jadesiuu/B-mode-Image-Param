#include "dataBuffer.h"
using namespace std;

dataBuffer::dataBuffer()
{
    numElement = 0; // Initialize numElement, numSample and scanline equal to 0
    numSample = 0;
    scanline = 0;
    dataMatrix = NULL; // Initialize dataMatrix and next to NULL (pointers)
    next = NULL;
}

dataBuffer::dataBuffer(std::ifstream *imagFile, std::ifstream *realFile, int inputNumElement, int inputNumSample, int inputScanline)
{
    numElement = inputNumElement; //Set numElement, numSample, and scanline to their input counterparts
    numSample = inputNumSample;
    scanline = inputScanline; 
    dataMatrix = createDataMatrix(); //Call createDataMatrix to allocate 2D complex array then assign it to dataMatrix
    loadRFData(dataMatrix, imagFile, realFile); //Call loadRFData to populate matrix
} 

dataBuffer::~dataBuffer()
{
    deleteDataMatrix(); //Release the 2D array dynamically allocated to dataMatrix
}

complex **dataBuffer::createDataMatrix()
{
    complex** RFData = new complex*[numElement]; //Declare a complex double pointer called RFData and define it a a complex pointer with numElement to create a complex array

    for (int i = 0; i < numElement; i++)
    {
        RFData[i] = new complex[numSample]; //Allocate 2D array of numElement and numSample
    }

    return RFData;
}

int dataBuffer::loadRFData(complex **RFData, std::ifstream *imagFile, std::ifstream *realFile) 
{ 
    char line[50]; //Define max number of characters so that all data is read
    
    for (int i = 0; i < numElement; i++) //Populate dataBuffer using a nested for loop
    {
        for (int j = 0; j < numSample; j++)
        {
            realFile->getline(line,50); //Read though and retrieve data stored in real file 
            imagFile->getline(line,50); //Read thorugh and retrieve data stored in imag file

            RFData[i][j].real = atof(line); //Stores real and imag into array and converts characters to floats
            RFData[i][j].imag = atof(line);
        }
    }
    
    return 0; //Return 0 after porpulating dataMatrix sucessfully
}

float dataBuffer::getRealRFData(int element,int sample)
{
    return dataMatrix[element][sample].real; //Return real component of the complex data stored in dataMatrix
}
float dataBuffer::getImagRFData(int element,int sample)
{
    return dataMatrix[element][sample].imag; //Return imaginary component of the complex data store in dataMatrix
}

void dataBuffer::deleteDataMatrix()
{
    for (int i = 0; i < numElement; i++) //For loop iterates through dataMatrix to delete all items
    {
        delete dataMatrix[i]; //Destroy allocated memory
    }

    delete dataMatrix; //Release 2D array 
}




