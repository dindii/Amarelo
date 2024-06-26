#pragma once

#include "Hittable.h"	
#include <memory>
#include <vector>
namespace Amrl
{
	class HittableList
	{
	public:
		HittableList() = default;
		HittableList(std::shared_ptr<Hittable> obj) { Add(obj); }

		void Clear() { m_Hittables.clear(); }
		void Add(std::shared_ptr<Hittable> obj) { m_Hittables.push_back(obj); }

		bool Hit(const Ray& ray, const Interval& bounds, HitRecord& result) const;





	private:
		std::vector<std::shared_ptr<Hittable>> m_Hittables;
	};
}