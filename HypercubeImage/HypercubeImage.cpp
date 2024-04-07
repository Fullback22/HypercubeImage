#include "HypercubeImage.h"

HypercubeImage::HypercubeImage()
{
}

HypercubeImage::HypercubeImage(const HypercubeImage& drop):
	leftBorder_{drop.leftBorder_},
	rightBorder_{drop.rightBorder_}
{
	hypercube_ = drop.hypercube_;
	drop.rgbFormat_.copyTo(rgbFormat_);
	drop.grayFormat_.copyTo(grayFormat_);
}

HypercubeImage& HypercubeImage::operator=(const HypercubeImage& drop)
{
	if (this == &drop)
		return *this;
	leftBorder_ = drop.leftBorder_;
	rightBorder_ = drop.rightBorder_;
	hypercube_ = drop.hypercube_;
	drop.rgbFormat_.copyTo(rgbFormat_);
	drop.grayFormat_.copyTo(grayFormat_);
	return *this;
}

void HypercubeImage::generateRandomImage(int const rows, int const cols, int channels)
{
	std::random_device rd{};
	std::mt19937 generator{ rd() };
	std::normal_distribution<> dis{ 120, 30 };
	hypercube_.resize(channels, cv::Mat{ rows, cols, CV_8UC1, cv::Scalar{0} });
	for (auto& channel : hypercube_)
	{
		for (size_t i{}; i < rows; ++i)
		{
			for (size_t j{}; j < cols; ++j)
			{
				channel.at<uchar>(i, j) = dis(generator);
			}
		}
	}
}

cv::Mat& HypercubeImage::operator[](size_t const chanel)
{
	if (chanel < hypercube_.size())
		return hypercube_[chanel];
	else
		throw (std::string{ "Out of range" });
}

const cv::Mat& HypercubeImage::operator[](size_t const chanel) const
{
	if (chanel < hypercube_.size())
		return hypercube_[chanel];
	else
		throw (std::string{ "Out of range" });
}

bool HypercubeImage::save(const std::string& fileName)
{
	std::string format{ fileName.end() - 5, fileName.end() };
	if (format != "hyper")
		return false;
	std::ofstream outFile{ fileName, std::ios_base::trunc };
	outFile << leftBorder_ << '\t' << rightBorder_ << std::endl;
	outFile << hypercube_.size() << std::endl;

	return true;
}
