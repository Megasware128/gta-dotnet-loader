#include "pools.h"

#pragma unmanaged
#include <CPools.h>
#include <CHeli.h>

#pragma managed
#include "PoolEnumerator.h"
#include "peds.h"
#include "vehicles.h"

#ifdef GTASA
typedef CCopPed CSecondaryPed;
typedef CHeli CSecondaryVehicle;
#else
typedef CPlayerPed CSecondaryPed;
typedef CAutomobile CSecondaryVehicle;
#endif // GTASA


using namespace System::Collections::Generic;
using namespace System::Linq;
using namespace Megasware128::GTA::Abstractions::Game;

ref class Peds : IEnumerable<IPed^>
{
public:
	virtual IEnumerator<IPed^>^ GetEnumerator()
	{
		auto enumerator = gcnew PoolEnumerator<CPed, Ped, CSecondaryPed>(CPools::ms_pPedPool);
		return safe_cast<IEnumerator<IPed^>^>(enumerator);
	}

	virtual System::Collections::IEnumerator^ GetEnumerator2() = System::Collections::IEnumerable::GetEnumerator
	{
		return GetEnumerator();
	}
};

IEnumerable<IPed^>^ Pools::Peds::get()
{
	return gcnew ::Peds();
}

ref class Vehicles : IEnumerable<IVehicle^>
{
	public:
	virtual IEnumerator<IVehicle^>^ GetEnumerator()
	{
		auto enumerator = gcnew PoolEnumerator<CVehicle, Vehicle, CSecondaryVehicle>(CPools::ms_pVehiclePool);
		return safe_cast<IEnumerator<IVehicle^>^>(enumerator);
	}

	virtual System::Collections::IEnumerator^ GetEnumerator2() = System::Collections::IEnumerable::GetEnumerator
	{
		return GetEnumerator();
	}
};

IEnumerable<IVehicle^>^ Pools::Vehicles::get()
{
	return gcnew ::Vehicles();
}
