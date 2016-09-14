#pragma once
#include <vector>
#include <opencv2/opencv.hpp>
using namespace std;
struct Point{
	double x, y;
};
class TargetObject {
public:
	TargetObject(Point pos,double w,double h);
	void update(cv::Rect rec);
	Point& getLastPos();
	bool needRemove();

protected:
	bool isStopped();
	bool isOutofBorder();
private:
	double m_w, m_h;
	cv::Rect m_border;
	double m_minMovedistance;
	int frame_stop_threshold;
	std::vector<Point> obj_trace;
};