#pragma once
#include <opencv2/opencv.hpp>
class objdector
{
public:
	objdector() {}
	virtual ~objdector() {}
	virtual void  detect(const cv::Mat & frame, std::vector<cv::Rect>& box) {}
};
