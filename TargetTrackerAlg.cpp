#include"TargetTrackerAlg.h"
#include <math.h>
#include "kcftracker.hpp"
TargetTrackerAlg::TargetTrackerAlg()
	:match_distance_threshold(20.0)
{
	tracker_manager_ptr = shared_ptr<MultiTrackerManager>(new MultiTrackerManager);
	object_detector_ptr = shared_ptr<objdector>(new objdector);
}
void TargetTrackerAlg::process(cv::Mat frame)
{
	std::vector<cv::Rect> detected_boxes;
	object_detector_ptr->detect(frame, detected_boxes);
    std::vector<Point> tracked_poses;
	tracker_manager_ptr->get_tracked_poses(tracked_poses);
	for(auto box:detected_boxes)
	{
		match_box(box,tracked_poses);
	}
	tracker_manager_ptr->update(frame);
}
void TargetTrackerAlg::match_box(cv::Rect& box, std::vector<Point>& poses)
{
	double pos_x = double(box.x + box.width >> 1);
	double pos_y = double(box.y + box.height>> 1);
	int i;
	for (i = 0;i<poses.size();i++)
	{
		if (abs(poses[i].x - pos_x) + abs(poses[i].y - pos_y)<=match_distance_threshold)
		{
			break;
		}
	}
	if (i == poses.size())
	{
		shared_ptr<Tracker> tracker_ptr = shared_ptr<Tracker>(new KCFTracker());
		tracker_manager_ptr->addTracker(tracker_ptr, box);
	}
}