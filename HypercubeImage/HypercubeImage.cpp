#include "HypercubeImage.h"

void HypercubeImage::createGrayFormat()
{
	grayFormat_ = cv::Mat::zeros(hypercube_[0].size(), CV_32FC1);
	
	for (size_t i{}; i < grayFormat_.rows; ++i)
	{
		for (size_t j{}; j < grayFormat_.cols; ++j)
		{
			float sumChannels{};
			for (auto& channel : hypercube_)
			{
				sumChannels += channel.at<float>(i, j);
			}
			grayFormat_.at<float>(i, j) = sumChannels/ hypercube_.size();
			//grayFormat_.at<float>(i, j) = 0.0;
		}
	}
	grayFormat_.convertTo(grayFormat_, CV_8UC1, 255);
	cv::Mat sd{ grayFormat_ };
	cv::waitKey;
}

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
	std::normal_distribution<> dis{ 0.5, 0.15 };
	hypercube_.resize(channels, cv::Mat{ rows, cols, CV_32FC1, cv::Scalar{0.0} });
	for (auto& channel : hypercube_)
	{
		for (size_t i{}; i < rows; ++i)
		{
			for (size_t j{}; j < cols; ++j)
			{
				channel.at<float>(i, j) = dis(generator);
			}
		}
	}
	createGrayFormat();
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
	outFile << col() << '\t' << row() << '\t' << channel() << std::endl;

	for (auto& channel : hypercube_)
	{
		for (size_t i{}; i < row(); ++i)
		{
			for (size_t j{}; j < col(); ++j)
			{
				outFile << channel.at<float>(i, j) << '\t';
			}
			outFile << "\n";
		}
		outFile << "\n";
	}
	
	outFile.close();
	return true;
}

bool HypercubeImage::load(const std::string& fileName)
{
	std::string format{ fileName.end() - 5, fileName.end() };
	if (format != "hyper")
		return false;


	std::ifstream inputFile{ fileName };
	inputFile >> leftBorder_;
	inputFile >> rightBorder_;
	int cols{};
	inputFile >> cols;
	int rows{};
	inputFile >> rows;
	size_t channels{};
	inputFile >> channels;

	hypercube_.resize(channels, cv::Mat{ rows, cols, CV_32FC1, cv::Scalar{0.0} });

	int pixelQuantity{ rows * cols };
	for (auto& channel : hypercube_)
	{
		for (size_t i{}; i < rows; ++i)
		{
			for (size_t j{}; j < cols; ++j)
			{
				inputFile >> channel.at<float>(i, j);
				cv::waitKey();
			}
		}
	}
	inputFile.close();
	createGrayFormat();
	return true;
}

int HypercubeImage::channel() const
{
	return hypercube_.size();
}

int HypercubeImage::row() const
{
	if(hypercube_.empty())
		return 0;
	return hypercube_[0].rows;
}

int HypercubeImage::col() const
{
	if (hypercube_.empty())
		return 0;
	return hypercube_[0].cols;
}
