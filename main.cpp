#include <Windows.h>
#include "csystem.h"
#include "mygame.h"

bool Init();
bool Update();
bool Render();
bool Shutdown();

CGame* game;
CSystem* engine;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int iCmdShow) {
	game = new CGame();

	engine = new CSystem();
	engine->setCallback(EVENT_INIT, Init);
	engine->setCallback(EVENT_UPDATE, Update);
	engine->setCallback(EVENT_RENDER, Render);
	engine->setCallback(EVENT_SHUTDOWN, Shutdown);

	engine->Initialize(new CWindow("Engine", GetModuleHandle(NULL)));

	engine->Run();



	delete game;
	delete engine;

	return 0;
}

bool Init() {
	game->setEngine(engine);
	return game->Init();
}

bool Update() {
	return game->Update();
}

bool Render() {
	return game->Render(engine->getInterpolation());
}

bool Shutdown() {
	return game->Shutdown();
}