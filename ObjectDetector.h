#pragma once
#include "objdector.h"
class ObjectDetector :public objdector
{
public:
	ObjectDetector();
	void  detect(const cv::Mat & frame, std::vector<cv::Rect>& box);
};
