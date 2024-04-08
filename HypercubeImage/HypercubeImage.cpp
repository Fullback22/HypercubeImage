#include "HypercubeImage.h"

void HypercubeImage::createGrayFormat()
{
	hypercube_[0].copyTo(grayFormat_);
	for (size_t i{}; i < grayFormat_.rows; ++i)
	{
		for (size_t j{}; j < grayFormat_.cols; ++j)
		{
			int sumChannels{};
			for (auto& channel : hypercube_)
			{
				sumChannels += channel.at<uchar>(i, j);
			}
			grayFormat_.at<uchar>(i, j) = sumChannels/ hypercube_.size();
		}
	}
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
	std::ofstream outFile{ fileName, std::ios_base::trunc | std::ios::binary };
	outFile.write((char*)&leftBorder_, sizeof(float));
	outFile.write((char*)&rightBorder_, sizeof(float));
	outFile.write((char*)&hypercube_[0].rows, sizeof(int));
	outFile.write((char*)&hypercube_[0].cols, sizeof(int));
	size_t chaelQuantity{ hypercube_.size() };
	outFile.write((char*)&chaelQuantity, sizeof(size_t));
	int bytesQuantity{ sizeof(uchar) };
	outFile.write((char*)&bytesQuantity, sizeof(int));
	
	//outFile << hypercube_[0].rows << '\t' << hypercube_[0].cols << '\t' << hypercube_.size()<<'\t'<< sizeof(uchar) << std::endl;
	int pixelQuantity{ hypercube_[0].rows * hypercube_[0].cols };
	for (auto& channel : hypercube_)
	{
		outFile.write((char*)channel.data, pixelQuantity * sizeof(uchar));
	}
	
	outFile.close();
	return true;
}

bool HypercubeImage::load(const std::string& fileName)
{
	std::string format{ fileName.end() - 5, fileName.end() };
	if (format != "hyper")
		return false;
	std::ifstream inputFile{ fileName, std::ios::binary };

	inputFile.read((char*)&leftBorder_, sizeof(float));
	inputFile.read((char*)&rightBorder_, sizeof(float));
	int rows{};
	inputFile.read((char*)&rows, sizeof(int));
	int cols{};
	inputFile.read((char*)&cols, sizeof(int));
	size_t channels{};
	inputFile.read((char*)&channels, sizeof(size_t));
	int bytesQuantity{ };
	inputFile.read((char*)&bytesQuantity, sizeof(int));

	hypercube_.resize(channels, cv::Mat{ rows, cols, CV_8UC1, cv::Scalar{0} });

	int pixelQuantity{ rows * cols };
	for (auto& channel : hypercube_)
	{
		inputFile.read((char*)channel.data, pixelQuantity * sizeof(uchar));
	}
	
	inputFile.close();
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
