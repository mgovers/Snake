#include "GUI.h"

using namespace System;
using namespace System::Windows::Forms;

//start the application, don't do any stuff here
void main(cli::array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Snake::GUI gui;
	Application::Run(%gui);
}