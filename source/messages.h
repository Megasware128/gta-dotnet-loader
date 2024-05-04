#pragma once
#pragma managed

[System::Composition::Export(Megasware128::GTA::Abstractions::Game::IMessages::typeid)]
public ref class Messages : public Megasware128::GTA::Abstractions::Game::IMessages {
public:
	virtual void Show(System::String^ message);
	virtual void Show(System::String^ message, int duration);
};
