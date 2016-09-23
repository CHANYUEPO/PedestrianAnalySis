#pragma once
#include "objdetector.h"
class ObjectDetector :public objdetector
{
public:
	ObjectDetector();
	void  detect(const cv::Mat & frame, std::vector<cv::Rect>& box);
};
