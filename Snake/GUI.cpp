#include "GUI.h"

using namespace System;
using namespace System::Windows::Forms;

namespace Snake {

  // Update the screen on a frame clock trigger
  void GUI::FrameUpdate(Object^ sender, EventArgs^ e)
  {

    this->game->step(currentDirection);

    // If body parts have been added in this step, add graphic objects for them
    unsigned int nrNewParts = this->game->getBody().size() - this->graphics->Count;
    for (unsigned int i = 0; i < nrNewParts; i++)
    {
      PictureBox^ newObj = gcnew PictureBox();
      newObj->Image = gcnew Bitmap(Image::FromFile("./Resources/box.bmp"), gridSize.X, gridSize.Y);
      this->Controls->Add(newObj);
      this->graphics->Add(newObj);
    }

    // Update head position
    this->graphics[0]->Location = Point(
      this->game->getBody()[0].x * gridSize.X,
      this->game->getBody()[0].y * gridSize.Y);

    this->graphics[0]->Update();
    this->graphics[0]->Refresh();

    /*if (currentDirection == 0)
    {
      this->graphics[0]->Location = Point(
        this->graphics[0]->Location.X + gridSize.X, 
        this->graphics[0]->Location.Y);
    }
    else if (currentDirection == 1)
    {
      this->graphics[0]->Location = Point(
        this->graphics[0]->Location.X, 
        this->graphics[0]->Location.Y - gridSize.Y);
    }
    else if (currentDirection == 2)
    {
      this->graphics[0]->Location = Point(
        this->graphics[0]->Location.X - gridSize.X, 
        this->graphics[0]->Location.Y);
    }
    else if (currentDirection == 3)
    {
      this->graphics[0]->Location = Point(
        this->graphics[0]->Location.X, 
        this->graphics[0]->Location.Y + gridSize.Y);
    }
    this->graphics[0]->Update();
    this->graphics[0]->Refresh();
    */

    
  }

  // Handle keyboard input
  void GUI::KeyHandler(Object^ sender, KeyEventArgs^ e)
  {
    switch (e->KeyCode)
    {
    case (Keys::D): // Right
      this->currentDirection = 0;
      break;
    case (Keys::W): // Up
      this->currentDirection = 1;
      break;
    case (Keys::A): // Left
      this->currentDirection = 2;
      break;
    case (Keys::S): // Right
      this->currentDirection = 3;
      break;
    }

  }

    // Start the application
    void main(cli::array<String^>^ args)
  {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    Snake::GUI gui;
    Application::Run(%gui);
  }

}