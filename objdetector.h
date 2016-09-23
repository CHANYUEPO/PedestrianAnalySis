#pragma once
#include <opencv2/opencv.hpp>
class objdetector
{
public:
	objdetector() {}
	virtual ~objdetector() {}
	virtual void  detect(const cv::Mat & frame, std::vector<cv::Rect>& box) {}
};
