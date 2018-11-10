#pragma once

#include "GameObject.h"
#include <stdio.h>
#include <iostream>

namespace Snake {

 using namespace System;
 using namespace System::Collections::Generic;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for GUI
	/// </summary>
	public ref class GUI : public System::Windows::Forms::Form
	{
	public:
		GUI(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

   this->KeyPreview = true;
   this->KeyDown += gcnew KeyEventHandler(KeyHandler);

   graphics = gcnew List<PictureBox^>();

   PictureBox^ newObj = gcnew PictureBox();
   newObj->Location = Point(100, 100);
   newObj->Image = gcnew Bitmap("./Resources/box.bmp");
   this->Controls->Add(newObj);

   graphics->Add(newObj);
   }

  void UpdateScreen(Object^ sender, EventArgs^ e)
  {
    if (currentDirection == 0)
    {
      this->graphics[0]->Location = Point(this->graphics[0]->Location.X+gridSize, this->graphics[0]->Location.Y);
    }
    else if (currentDirection == 1)
    {
      this->graphics[0]->Location = Point(this->graphics[0]->Location.X, this->graphics[0]->Location.Y - gridSize);
    }
    else if (currentDirection == 2)
    {
      this->graphics[0]->Location = Point(this->graphics[0]->Location.X - gridSize, this->graphics[0]->Location.Y);
    }
    else if (currentDirection == 3)
    {
      this->graphics[0]->Location = Point(this->graphics[0]->Location.X, this->graphics[0]->Location.Y + gridSize);
    }

    std::cout << "Moved to " << this->graphics[0]->Location.X << "," << this->graphics[0]->Location.X << std::endl;
    this->graphics[0]->Update();
    this->graphics[0]->Refresh();
  }

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GUI()
		{
			if (components)
			{
				delete components;
			}
		}
 private: System::ComponentModel::IContainer^  components;
 protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


		/// The timer that performs screen update
  unsigned int gameTickPeriod = 200;

  // The graphics objects present in the GUI
  List<PictureBox^>^ graphics;

  // The current direction input
  unsigned int currentDirection = 0;
 private: System::Windows::Forms::Timer^  timer1;

  const int gridSize = 50;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
    this->components = (gcnew System::ComponentModel::Container());
    this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
    this->SuspendLayout();
    // 
    // timer1
    // 
    this->timer1->Tick += gcnew System::EventHandler(this, &GUI::UpdateScreen);
    this->timer1->Interval = gameTickPeriod;
    this->timer1->Start();
    // 
    // GUI
    // 
    this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
    this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
    this->ClientSize = System::Drawing::Size(480, 480);
    this->Name = L"GUI";
    this->Text = L"GUI";
    this->ResumeLayout(false);

  }
#pragma endregion

  static void KeyHandler(Object^ sender, KeyEventArgs^ e)
  {
    GUI^ gui = (GUI^)sender;
    
    if (e->KeyCode == System::Windows::Forms::Keys::D)
    {
      // Up
      gui->currentDirection = 0;
    }
    else if (e->KeyCode == System::Windows::Forms::Keys::W)
    {
      // Up
      gui->currentDirection = 1;
    }
    else if (e->KeyCode == System::Windows::Forms::Keys::A)
    {
      // Up
      gui->currentDirection = 2;
    }
    else if (e->KeyCode == System::Windows::Forms::Keys::S)
    {
      // Up
      gui->currentDirection = 3;
    }
    
    //test
    /*
    Point newLocation = Point(gui->graphics[0]->Location);
    if (e->KeyCode == System::Windows::Forms::Keys::W)
      newLocation.Y -= 10;
    else if (e->KeyCode == System::Windows::Forms::Keys::A)
      newLocation.X -= 10;
    else if (e->KeyCode == System::Windows::Forms::Keys::S)
      newLocation.Y += 10;
    else if (e->KeyCode == System::Windows::Forms::Keys::D)
      newLocation.X += 10;

    if (!newLocation.Equals(gui->graphics[0]->Location))
    {
      gui->graphics[0]->Location = newLocation;
      gui->graphics[0]->Update();
      gui->graphics[0]->Refresh();
    }
    */
  }

	};
}
