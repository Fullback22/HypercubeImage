// HypercubeImage.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "HypercubeImage.h"

int main()
{
    HypercubeImage image;
    image.generateRandomImage(50,60,2051);
 
    //image.save("testNew1.hyper");
    //cv::Mat test1{ image[21] };
    HypercubeImage image2;
    image2.load("testPy1.hyper");
    cv::Mat test2{ image2[0] };
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
