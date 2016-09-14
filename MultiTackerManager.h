#pragma once
#include "tracker.h"
#include "TargetObject.h"
#include <memory>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <string>
#include <map>
using namespace std;
class MultiTrackerManager {
public:
	MultiTrackerManager();
	void addTracker(shared_ptr<Tracker>  tracker_ptr, cv::Rect rec);
	void update(cv::Mat image);
	void eliminate(shared_ptr<Tracker>  tracker_ptr);
	void get_tracked_poses(std::vector<Point>& poses);
	//void getdata();//以一定的形式返回跟踪数据给分析器
private:
	std::vector<shared_ptr<Tracker> > tracker_ptr_vector;
	std::vector<shared_ptr<TargetObject> > object_vec;
	std::map<shared_ptr<Tracker>, shared_ptr<TargetObject> > tracker_map_obj;
};