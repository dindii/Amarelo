#include "HittableList.h"


bool HittableList::Hit(const Ray& ray, const Interval& bounds, HitRecord& result) const
{
	HitRecord tempResult;
	bool hitAnything = false;
	
	double closestHit = bounds.Max();

	for (const std::shared_ptr<Hittable>& object : m_Hittables)
	{
		//Sobrescreve os valores com as entidades mais proximas do raio. 
		//Ao achar uma entidade "mais perto até o momento", usa o intervalo da camera até essa entidade
		//Por conta disso, todas as entidades restantes que serão pegas, estarão na mesma distancia desta (improvavel)
		//ou mais perto. Porque alteramos o intervalo, então o maximo que iremos é até a atual entidade mas nunca após.
		//No fim, vamos diminuindo cada vez mais o intervalo (porque provavelmente tudo que não é a atual entidade, está mais proximo)
		//e por conta disso, vamos sobrescrevendo os valores. No final, teremos sempre o valor mais perto em evidencia
		//pois a) começamos pela entidade mais proxima e o intervalo nunca chegará na mais distante, logo escrevemos o valor só da mais proxima.
		// ou  b) começamos pela distante, escrevemos o valor, e depois vamos pra mais proxima (pois o intervalo cobre) e escrevemos o valor.
		if (object->Hit(ray, Interval(bounds.Min(), closestHit), tempResult))
		{
			hitAnything = true;
			closestHit = tempResult.t;
			result = tempResult;
		}
	}
	
	return hitAnything;

}
