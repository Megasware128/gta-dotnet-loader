#pragma managed

[System::Composition::Export(Megasware128::GTA::Abstractions::Game::IHud::typeid)]
public ref class Hud : public Megasware128::GTA::Abstractions::Game::IHud {
public:
	virtual void ShowHelpMessage(System::String^ message, bool quick, bool permanent);
};
