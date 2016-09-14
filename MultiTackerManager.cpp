#include "MultiTackerManager.h"
MultiTrackerManager::MultiTrackerManager()
{
	tracker_ptr_vector.clear();
	object_vec.clear();
	tracker_map_obj.clear();
}
void MultiTrackerManager::addTracker(shared_ptr<Tracker> tracker_ptr, cv::Rect rec)
{
	tracker_ptr_vector.push_back(tracker_ptr);
    Point pos;
	pos.x = double(rec.x + rec.width>>1);
	pos.y = double(rec.y + rec.height>>1);
	shared_ptr<TargetObject> object_ptr(new TargetObject(pos, rec.width, rec.height));
	object_vec.push_back(object_ptr);
	tracker_map_obj[tracker_ptr] = object_ptr;
}
void MultiTrackerManager::eliminate(shared_ptr<Tracker> tracker_ptr)
{
	std::vector<shared_ptr<Tracker> >::iterator iter;
	for (iter = tracker_ptr_vector.begin();iter != tracker_ptr_vector.end();iter++)
	{
		if (*iter == tracker_ptr)
		{
			vector<shared_ptr<TargetObject> >::iterator obj_iter;
			obj_iter = std::find(object_vec.begin(), object_vec.end(), tracker_map_obj[tracker_ptr]);
			if (obj_iter != object_vec.end())
			{
				object_vec.erase(obj_iter);
			}
			std::map<shared_ptr<Tracker>, shared_ptr<TargetObject> >::iterator map_iter = find(tracker_map_obj.begin(), tracker_map_obj.end(), tracker_ptr);
			if (map_iter != tracker_map_obj.end())
			{
				tracker_map_obj.erase(map_iter);
			}
			tracker_ptr_vector.erase(iter);
			break;
		}
	}
}
void MultiTrackerManager::update(cv::Mat image)
{
	if (object_vec.size() == 0)
		return;
	std::vector<shared_ptr<Tracker> >::iterator iter;
	for (iter = tracker_ptr_vector.begin();iter!=tracker_ptr_vector.end();iter++)
	{

		if (tracker_map_obj[(*iter)]->needRemove())
		{

			eliminate((*iter));
			break;
		}
		cv::Rect rec=(*iter)->update(image);
        tracker_map_obj[(*iter)]->update(rec);
	}

}
void MultiTrackerManager::get_tracked_poses(std::vector<Point>& poses)
{
	for (int i = 0;i < object_vec.size();i++)
	{
		poses.push_back(object_vec[i]->getLastPos());
	}
}