#include "pch.h"
#include "App.hpp"

FoxTail::App::App() {
	current = this;
	BeforeInit();
	Init();
	AfterInit();
}

void FoxTail::App::Init()
{

}
