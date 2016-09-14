#include "TargetObject.h"
TargetObject::TargetObject(Point pos, double w, double h)
	:m_w(w),m_h(h),m_border(cv::Rect(0,0,500,500)),frame_stop_threshold(50),
	m_minMovedistance(20.0)
{
	obj_trace.clear();
	obj_trace.push_back(pos);
}
void TargetObject::update(cv::Rect rec)
{
	m_w = double(rec.width);
	m_h = double(rec.height);
	Point pos;
	pos.x = double(rec.x + rec.width>>1);
	pos.y = double(rec.y + rec.height>>1);
	obj_trace.push_back(pos);
}
Point& TargetObject::getLastPos()
{
	return obj_trace.back();
}
bool TargetObject::needRemove()
{
	if(isOutofBorder()||isStopped())
		return true;
	return false;
}
bool TargetObject::isOutofBorder()
{
	Point pos = obj_trace.back();
	//if(pos in m_border)
		//return true;
	return false;
}
bool TargetObject::isStopped()
{
	int steps = obj_trace.size();
	if(steps<=frame_stop_threshold)
		return false;
	double movedistance = 0.0;
	int i = steps - frame_stop_threshold;
	for (;i<steps; ++i)
	{
		movedistance+=abs(obj_trace[i+1].x - obj_trace[i].x) + abs(obj_trace[i+1].y - obj_trace[i].y);
	}
	return movedistance<m_minMovedistance;
}