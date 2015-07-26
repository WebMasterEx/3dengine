#include "custommodel.h"

void ModelCustom::Initialize() {
	
}

void ModelCustom::Shutdown() {
	mesh->Release();
	Model::Shutdown();
}

void ModelCustom::Draw() {
	beforeDraw();
	mesh->DrawSubset(0);
	afterDraw();
}