#include "pch.h"
#include "App.h"

FOXEXPORT FoxTail::App::App() {

	m_current = this;
	BeforeInit();
	Init();
	AfterInit();
}

void FoxTail::App::Init()
{

}
