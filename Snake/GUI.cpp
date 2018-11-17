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
    bool validMove = false;
    if (!this->aiEnabled) { 
      validMove = gameManager->doMove(this->currentDirection); 
    }
    else {
      validMove = gameManager->doMove();
    }

    if (!validMove)
    {
      // Invalid move, game over!
      this->msgBox->Enabled = true;
      this->msgBox->Visible = true;
      this->msgBox->Text = gameOverText + "\n\nFinal Score:\n" + this->gameManager->getGame()->getBody().size().ToString();
      // Stop the game timer
      this->gameTimer->Enabled = false;
      this->gameTimer->Stop();
      return;
    }

    // If body parts have been added in this step, add graphic objects for them
    // (existing graphics objects are only updated)
    if (this->gameManager->getGame()->getBody().size() > this->snakeGraphics->Count)
    {
      this->snakeGraphics->Add(
        this->AddNewGraphicsObject(
          this->snakeResource,
          this->gameManager->getGame()->getBody()[this->gameManager->getGame()->getBody().size()]));
    }

    // Update positions
    this->snakeGraphics[this->snakeGraphics->Count - 1]->Location = IndexToPixel(this->gameManager->getGame()->getBody()[0]);
    this->snakeGraphics[this->snakeGraphics->Count - 1]->Update();
    this->snakeGraphics[this->snakeGraphics->Count - 1]->Refresh();
    // (To Do merge this in Body such that this is not needed anymore)
    this->snakeGraphics->Insert(0, this->snakeGraphics[this->snakeGraphics->Count - 1]);
    this->snakeGraphics->RemoveAt(this->snakeGraphics->Count - 1);
      
    // Check for new food spawn
    if (this->gameManager->getGame()->getTargets().size() == 0)
    {
      GridPos randPos;
      do {
        randPos = { 
          (int)round(rand() % gridDims.X),
          (int)round(rand() % gridDims.Y) 
        };
      } 
      while (!this->gameManager->getGame()->addNewTarget(randPos));

      foodGraphics->Location = IndexToPixel(this->gameManager->getGame()->getTargets()[0]);
      foodGraphics->Image = gcnew Bitmap(Image::FromFile(this->foodResource), gridSize.X, gridSize.Y);
    }
  }

  // Handle keyboard input
  void GUI::KeyHandler(Object^ sender, KeyEventArgs^ e)
  {
    switch (e->KeyCode)
    {
      //
      // D: Right
      //
    case (Keys::D):
      this->currentDirection = 0;
      break;
      //
      // W: Up
      //
    case (Keys::W):
      this->currentDirection = 1;
      break;
      //
      // A: Left
    case (Keys::A):
      this->currentDirection = 2;
      break;
      //
      // S: Down
      //
    case (Keys::S): 
      this->currentDirection = 3;
      break;
      //
      // Enter: Toggle AI
      //
    case (Keys::Enter):
      this->aiEnabled = !this->aiEnabled;
      this->aiStatusBox->Visible = this->aiEnabled;
      break;
      //
      // Plus ('+=' button on keyboard): Speed up
      //
    case (Keys::Oemplus):
      if (this->gameTimer->Interval > 1) // maximum speed
        this->gameTimer->Interval /= this->gameTickSpeedupFactor;
      break;
      //
      // Minus ('-_' button on keyboard): Speed down
      //
    case (Keys::OemMinus):
      if (this->gameTimer->Interval < 1000) // minimum speed
        this->gameTimer->Interval *= this->gameTickSpeedupFactor; 
      break;
      //
      // Escape: Pause (toggle)
      //
    case (Keys::Escape):
      this->gameTimer->Enabled = !this->gameTimer->Enabled;
        break;
    }
  }

  void GUI::OnClickReset(Object^ sender, MouseEventArgs^ e)
  {
    // Reset game
    for each(PictureBox^ obj in snakeGraphics)
      delete obj;
    this->snakeGraphics = gcnew List<PictureBox^>();
    
    this->gameManager->reset();
    this->gameTimer->Start();
    this->currentDirection = 0;
    
    // Suppress UI
    this->msgBox->Enabled = false;
    this->msgBox->Visible = false;
  }

  void GUI::SetupGame()
  {

    // Setup the AI
    // todo add an AI choice
    this->ai = new AI_Easy();

    Game* game = new Game(
      this->gridDims.X,
      this->gridDims.Y);

    this->gameManager = new GameManager(game, this->ai);
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