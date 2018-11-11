#include "GUI.h"
#include <iostream>

using namespace System;
using namespace System::Windows::Forms;

namespace Snake {

  Point GUI::IndexToPixel(Point pixel)
  {
    return Point(
      pixel.X * this->gridSize.X,
      pixel.Y * this->gridSize.Y);
  }

  Point GUI::IndexToPixel(BodyPart pos)
  {
    return IndexToPixel(Point(pos.x, pos.y));
  }

  PictureBox^ GUI::AddNewGraphicsObject(String^ resource, BodyPart location)
  {
    PictureBox^ newObj = gcnew PictureBox();
    newObj->Image = gcnew Bitmap(resource);
    newObj->Size = System::Drawing::Size(gridSize.X, gridSize.Y);
    newObj->Location = IndexToPixel(location);
    newObj->SizeMode = PictureBoxSizeMode::StretchImage;
    this->Controls->Add(newObj);
    return newObj;
  }

  // Update the screen on a frame clock trigger
  void GUI::FrameUpdate(Object^ sender, EventArgs^ e)
  {

    // Find the direction, either from keyboard input or the configured AI
    int direction;
    if (!this->aiEnabled) { 
      direction = this->currentDirection; 
    }
    else {
      direction = this->game->computeAIMove();
    }

    if (!this->game->step(direction))
    {
      // Invalid move, game over!
      this->msgBox->Enabled = true;
      this->msgBox->Visible = true;
      this->msgBox->Text = gameOverText + "\n\nFinal Score:\n" + this->game->getBody().size().ToString();
      // Stop the game timer
      this->gameTimer->Enabled = false;
      this->gameTimer->Stop();
      return;
    }

    // If body parts have been added in this step, add graphic objects for them
    // (existing graphics objects are only updated)
    if (this->game->getBody().size() > this->snakeGraphics->Count)
    {
      this->snakeGraphics->Add(
        this->AddNewGraphicsObject(this->snakeResource, this->game->getBody()[this->game->getBody().size()]));
    }

    // Update positions
    this->snakeGraphics[this->snakeGraphics->Count - 1]->Location = IndexToPixel(this->game->getBody()[0]);
    this->snakeGraphics[this->snakeGraphics->Count - 1]->Update();
    this->snakeGraphics[this->snakeGraphics->Count - 1]->Refresh();
    // (To Do merge this in Body such that this is not needed anymore)
    this->snakeGraphics->Insert(0, this->snakeGraphics[this->snakeGraphics->Count - 1]);
    this->snakeGraphics->RemoveAt(this->snakeGraphics->Count - 1);
      
    // Check for new food spawn
    if (this->game->getTargets().size() == 0)
    {
      GridPos randPos;
      do {
        randPos = { 
          (int)round(rand() % gridDims.X),
          (int)round(rand() % gridDims.Y) 
        };
      } 
      while (!this->game->addNewTarget(randPos));

      foodGraphics->Location = IndexToPixel(this->game->getTargets()[0]);
      foodGraphics->Image = gcnew Bitmap(Image::FromFile(this->foodResource), gridSize.X, gridSize.Y);
    }
  }

  // Handle keyboard input
  void GUI::KeyHandler(Object^ sender, KeyEventArgs^ e)
  {
    switch (e->KeyCode)
    {
      // Right
    case (Keys::D):
      this->currentDirection = 0;
      break;
      // Up
    case (Keys::W):
      this->currentDirection = 1;
      break;
      // Left
    case (Keys::A):
      this->currentDirection = 2;
      break;
      // Down
    case (Keys::S): 
      this->currentDirection = 3;
      break;
      // Enter: Toggle AI
    case (Keys::Enter):
      this->aiEnabled = !this->aiEnabled;
      this->aiStatusBox->Visible = this->aiEnabled;
      break;
      // Plus ('+=' button on keyboard): Speed up
    case (Keys::Oemplus):
      this->gameTimer->Interval /= this->gameTickSpeedupFactor;
      break;
      // Minus ('-_' button on keyboard): Speed down
    case (Keys::OemMinus):
      this->gameTimer->Interval *= this->gameTickSpeedupFactor; 
      break;
    }

  }

  void GUI::OnClickReset(Object^ sender, MouseEventArgs^ e)
  {
    // Reset game
    for each(PictureBox^ obj in snakeGraphics)
      delete obj;
    this->snakeGraphics = gcnew List<PictureBox^>();
    
    this->game->reset();
    this->gameTimer->Start();
    this->currentDirection = 0;
    
    // Suppress UI
    this->msgBox->Enabled = false;
    this->msgBox->Visible = false;
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