#include "HittableList.h"

bool HittableList::hit(const Ray& r, double t_min, double t_max, hit_record& record) const
{
    hit_record current_record;
    bool isHitted = false;
    double closestT = t_max;

    for (const std::shared_ptr<Hittable> object : objects)
    {
        object->hit(r, t_min, t_max, current_record);
        if(current_record.t < closestT)
        {
            isHitted = true;
            closestT = current_record.t;
            record = current_record;
        }
    }

    return isHitted;

}
