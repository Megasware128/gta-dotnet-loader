//#include "peds.h"
//#include "vehicles.h"

#pragma managed

[System::Composition::Export(Megasware128::GTA::Abstractions::Game::IPools::typeid)]
public ref class Pools : public Megasware128::GTA::Abstractions::Game::IPools
{
public:
	virtual property System::Collections::Generic::IEnumerable<Megasware128::GTA::Abstractions::Game::IPed^>^ Peds
	{
		System::Collections::Generic::IEnumerable<Megasware128::GTA::Abstractions::Game::IPed^>^ get();
	}
	virtual property System::Collections::Generic::IEnumerable<Megasware128::GTA::Abstractions::Game::IVehicle^>^ Vehicles
	{
		System::Collections::Generic::IEnumerable<Megasware128::GTA::Abstractions::Game::IVehicle^>^ get();
	}
};