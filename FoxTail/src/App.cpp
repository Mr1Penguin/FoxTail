#include "pch.h"
#include "App.hpp"

FOXEXPORT FoxTail::App::App() {

	m_current = this;
	BeforeInit();
	Init();
	AfterInit();
}

void FoxTail::App::Init()
{

}
