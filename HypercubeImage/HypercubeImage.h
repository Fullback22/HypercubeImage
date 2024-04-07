#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <random>

#include <opencv2/highgui/highgui.hpp>

class HypercubeImage
{
	float leftBorder_{ 0.35 };
	float rightBorder_{ 2.3 };
	
	std::vector<cv::Mat> hypercube_{ 0 };
	cv::Mat rgbFormat_{};
	cv::Mat grayFormat_{};
public:
	HypercubeImage();
	HypercubeImage(const HypercubeImage& drop);
	HypercubeImage& operator=(const HypercubeImage& drop);

	void generateRandomImage(int const rows, int const cols, int channels);

	cv::Mat& operator[](size_t const chanel);
	const cv::Mat& operator[](size_t const chanel) const;

	bool save(const std::string& fileName);
};

