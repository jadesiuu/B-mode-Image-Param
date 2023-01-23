#include "imageParam.h"
using namespace std;

imageParam::imageParam()
{
    numElement = 128; //Define variables to given values
    numSample = 3338;
    numScanline = 127; 
    elementPosition = genElementPosition(); //Call genElementPosition and assign to elementPosition 
    scanlinePosition = genScanlinePosition(numScanline, PITCH, elementPosition); //Call genScanlinePosition and assign 2D array to scanlinePosition
}

imageParam::~imageParam()
{
    deletePositionArray(); //Release the 2D arrays dynamically allocated for different variables  
}

// Create an array containing the element location (in x-direction) of the ultrasound transducer
float *imageParam::genElementPosition()
{
    float* elePosition;

    elePosition = new float[numElement]; //Define elementPosition as a new float array with numElement

    for (int i = 0; i < numElement; i++) // Use for loop to assign each element of the elementPosition array
    {
        elePosition[i] = (i - ((float)(numElement - 1.0))/2.0)*PITCH; //Equation from assignment 3
    }

    return elePosition;

}

float2 **imageParam::genScanlinePosition(int numScanline, const float PITCH, float* elementLocation)
{
    cout << "Desired imaging depth: "; //Ask user for desired imaging depth
    cin >> desiredDepth; //Inputs user data

    cout << "Desired number of pixels per scanline: "; //Ask user for desired number of pixels per scanline
    cin >> numPixel; //Inputs user data 

    float2** scanlinePosition = new float2*[numScanline]; //Define scanlinePostion as a new float2 pointer array 
    float depSize = desiredDepth/(numPixel-1);

    for (int i = 0; i < numScanline; i++) //Use nested for loop to populate 2D array 
    {
        scanlinePosition[i] = new float2[numPixel]; 

        for (int j = 0; j < numPixel; j++)
        {
            scanlinePosition[i][j].x = (i-((numScanline-1.0)/2.0))*PITCH; //Accesses the x components of the array
            scanlinePosition[i][j].y = depSize*j; //Accesses they y components of the array 
        }
    }

    return scanlinePosition;

}

float imageParam::getXPosition(int scanline, int pixel)
{     
    return scanlinePosition[scanline][pixel].x; //Returns the x component of data stored in scanlinePosition
}

float imageParam::getYPosition(int scanline, int pixel)
{
    return scanlinePosition[scanline][pixel].y; //Returns the y component of data stored in scanlinePosition
}

float imageParam::getElementPosition(int element)
{
    return elementPosition[element]; //Returns the positionof an element
}

int imageParam::getNumElement()
{
    return numElement; //Returns the respective private data components 
}

int imageParam::getNumSample()
{
    return numSample; //Returns the respective private data components
}

int imageParam::getNumScanline() 
{
    return numScanline; //Returns the respective private data components
}

int imageParam::getNumPixel() 
{
    return numPixel; //Returns the respective private data components
}

void imageParam::deletePositionArray()
{
    delete elementPosition; //Releases memory allocated for elementPosition

    for (int i =0; i < numScanline; i++) 
    {
        delete scanlinePosition[i];
    }

    delete scanlinePosition; //Releases memory allocated for scanlinePosition
}









