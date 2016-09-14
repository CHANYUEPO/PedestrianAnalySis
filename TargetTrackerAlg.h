#pragma once
#include <opencv2/opencv.hpp>
#include "MultiTackerManager.h"
#include "ObjectDetector.h"
#include <memory>
class TargetTrackerAlg
{
public:
	explicit TargetTrackerAlg();
	void process(cv::Mat frame);
	void match_box(cv::Rect& box,std::vector<Point>& pos);
private:
	shared_ptr<MultiTrackerManager> tracker_manager_ptr;
	shared_ptr<ObjectDetector> object_detector_ptr;
	double match_distance_threshold;
};
