#pragma once
#include"Computer.h"
#include"ComputerTree.h"
#include <msclr\marshal_cppstd.h>
#include <chrono>
#include<Windows.h>
#include"RunCommand.h"


namespace RDTool
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{

	public:
		static ComputerTree<Computer>* selectedTree;
		MainWindow(ComputerTree<Computer>* tree)
		{
			_tree = tree;
			selectedTree = new ComputerTree<Computer>();
			InitializeComponent();
			populateViewTree(tree, computerTree);
			isRemoving = false;
		}
	private: System::Windows::Forms::TextBox^  cmdBox;
	private: System::Windows::Forms::Label^  computerCountLabel;
			 int numOfComputers = 0;
	public:
		static System::String^ cmd;
		System::Windows::Forms::Panel^ createPanel(System::String^ name, System::String^ status, System::Windows::Forms::FlowLayoutPanel^ display);
		void populateViewTree(ComputerTree<Computer>* tree, System::Windows::Forms::TreeView ^ view);
		static void paintPanels(ComputerTree<Computer>* tree);
		static void runCommand(String^ cmd);
		static bool isRemoving;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Windows::Forms::TreeView^  computerTree;
		ComputerTree<Computer>* _tree;

		System::Windows::Forms::Label^  label1;
		//private: System::Windows::Forms::Button^  labViewButton;
		System::Windows::Forms::Button^  remoteButton;
		System::Windows::Forms::Button^  test;
	private: static System::Windows::Forms::FlowLayoutPanel^  computerDisplay;






		System::Windows::Forms::MenuStrip^  menuStrip1;
		System::Windows::Forms::ToolStripMenuItem^  commandToolStripMenuItem;

		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->computerTree = (gcnew System::Windows::Forms::TreeView());
			this->computerDisplay = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->test = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->commandToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cmdBox = (gcnew System::Windows::Forms::TextBox());
			this->computerCountLabel = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// computerTree
			// 
			this->computerTree->CheckBoxes = true;
			this->computerTree->Dock = System::Windows::Forms::DockStyle::Left;
			this->computerTree->Location = System::Drawing::Point(0, 24);
			this->computerTree->Name = L"computerTree";
			this->computerTree->RightToLeftLayout = true;
			this->computerTree->ShowNodeToolTips = true;
			this->computerTree->Size = System::Drawing::Size(188, 1017);
			this->computerTree->TabIndex = 0;
			this->computerTree->AfterCheck += gcnew System::Windows::Forms::TreeViewEventHandler(this, &MainWindow::computerTree_AfterSelect);
			// 
			// computerDisplay
			// 
			this->computerDisplay->AutoScroll = true;
			this->computerDisplay->Dock = System::Windows::Forms::DockStyle::Fill;
			this->computerDisplay->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->computerDisplay->Location = System::Drawing::Point(188, 24);
			this->computerDisplay->Name = L"computerDisplay";
			this->computerDisplay->Size = System::Drawing::Size(1716, 1017);
			this->computerDisplay->TabIndex = 1;
			// 
			// test
			// 
			this->test->Location = System::Drawing::Point(0, 0);
			this->test->Name = L"test";
			this->test->Size = System::Drawing::Size(75, 23);
			this->test->TabIndex = 0;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->commandToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1904, 24);
			this->menuStrip1->TabIndex = 2;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// commandToolStripMenuItem
			// 
			this->commandToolStripMenuItem->Name = L"commandToolStripMenuItem";
			this->commandToolStripMenuItem->Size = System::Drawing::Size(76, 20);
			this->commandToolStripMenuItem->Text = L"Command";
			this->commandToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::commandToolStripMenuItem_Click);
			// 
			// cmdBox
			// 
			this->cmdBox->AcceptsReturn = true;
			this->cmdBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cmdBox->Location = System::Drawing::Point(188, -3);
			this->cmdBox->Name = L"cmdBox";
			this->cmdBox->Size = System::Drawing::Size(1417, 27);
			this->cmdBox->TabIndex = 3;
			// 
			// computerCountLabel
			// 
			this->computerCountLabel->AutoSize = true;
			this->computerCountLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->computerCountLabel->Location = System::Drawing::Point(1644, 0);
			this->computerCountLabel->Name = L"computerCountLabel";
			this->computerCountLabel->Size = System::Drawing::Size(176, 22);
			this->computerCountLabel->TabIndex = 4;
			this->computerCountLabel->Text = L"Computers loaded: 0";
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(1904, 1041);
			this->Controls->Add(this->computerCountLabel);
			this->Controls->Add(this->cmdBox);
			this->Controls->Add(this->computerDisplay);
			this->Controls->Add(this->computerTree);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MainWindow";
			this->Text = L"RDTool";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: System::Void computerTree_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e)
	{
		this->computerTree->UseWaitCursor = true;
		this->computerDisplay->UseWaitCursor = true;
		this->isRemoving = true;
		//College level selected
		if (e->Node->Level == 0)
		{
			if (e->Node->Checked)
			{
				//Expand all children
				e->Node->ExpandAll();

				int size = e->Node->GetNodeCount(false);
				for (int i = 0; i < size; i++)
				{
					if (!e->Node->Nodes[i]->Checked)
					{
						//Select every child of the node and set to true
						e->Node->Nodes[i]->Checked = true;
					}
				}
			}
			else
			{

				int size = e->Node->GetNodeCount(false);
				e->Node->Collapse();
				for (int i = 0; i < size; i++)
				{
					if (e->Node->Nodes[i]->Checked)
					{
						e->Node->Nodes[i]->Checked = false;
					}
				}
			}
		}
		//Lab level selected
		else if (e->Node->Level == 1)
		{
			if (e->Node->Checked)
			{
				int size = e->Node->GetNodeCount(false);
				e->Node->ExpandAll();
				for (int i = 0; i < size; i++)
				{
					if (!e->Node->Nodes[i]->Checked)
					{
						e->Node->Nodes[i]->Checked = true;
					}
				}
			}
			else
			{
				int size = e->Node->GetNodeCount(false);
				e->Node->Collapse();
				e->Node->ExpandAll();
				for (int i = 0; i < size; i++)
				{
					if (e->Node->Nodes[i]->Checked)
					{
						e->Node->Nodes[i]->Checked = false;
					}
				}
			}
		}
		//Last level is selected
		else
		{
			if (e->Node->Checked)
			{
				//This will add the computer selected from the viewTree and add it to the selected tree
				string name = msclr::interop::marshal_as<std::string>(e->Node->Name);
				ComputerTree<Computer>*temp = _tree->find(name);
				selectedTree->insert(temp->getInfo());
				String^ labelName = e->Node->Name;
				String^ labelStatus;

				//This will set the label for the panel
				temp->getInfo()->checkUser();
				int status = temp->getInfo()->getStatus();
				if (status == 1)
				{
					string foo = " In use by: ";
					string bar = temp->getInfo()->getUser();
					foo += bar;
					labelStatus = gcnew String(foo.c_str());
				}
				else if (status == 2)
				{
					labelStatus = L"Unavailable";
				}
				else
				{
					labelStatus = L"Available";
				}
				//This creates the panel then checks the user of the panel;
				Panel^ test = createPanel(labelName, labelStatus, computerDisplay);

				//Adds the panel to the display
				computerDisplay->Controls->Add(test);
				numOfComputers++;
				String^ computerCount = L"Computers Loaded: " + numOfComputers;
				computerCountLabel->Text = computerCount;


			}
			else
			{
				//This will remove the panel and computer from the tree
				string name = msclr::interop::marshal_as<std::string>(e->Node->Name);
				ComputerTree<Computer>*temp = _tree->find(name);
				String^ labelName = e->Node->Name;
				selectedTree->remove(temp->getInfo());
				computerDisplay->Controls->RemoveByKey(e->Node->Name);
				numOfComputers--;
				String^ computerCount = L"Computers Loaded: " + numOfComputers;
				computerCountLabel->Text = computerCount;
			}
		}
		this->computerTree->UseWaitCursor = false;
		this->computerDisplay->UseWaitCursor = false;
		this->isRemoving = false;

	}
			 //This is the event listener for the remote button
	public: System::Void remoteButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		//creates the button from the sender
		Button^ ctrl = safe_cast<Button^>(sender);

		//Gets the panel name (Which is the name of the computer) then calls remote desktop on it
		string name = msclr::interop::marshal_as<std::string>(ctrl->Parent->Name->ToString());
		selectedTree->find(name)->getInfo()->remoteDesktop();
	}
			//This is the event listener for the lab view button
	public: System::Void labViewButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		//creates the button from the sender
		Button^ ctrl = safe_cast<Button^>(sender);

		//Gets the panel name (which is the name of the computer) and calls lab view on it
		string name = msclr::interop::marshal_as<std::string>(ctrl->Parent->Name->ToString());
		selectedTree->find(name)->getInfo()->labView();
	}
			//This is the event listener for the magic packets button
			//TODO: Need to test this
	public: System::Void magicButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		//creates the button from the sender
		Button^ ctrl = safe_cast<Button^>(sender);

		//Gets the panel name(which is the name of the computer) and calls the magic packts on it
		string name = msclr::interop::marshal_as<std::string>(ctrl->Parent->Name->ToString());
		selectedTree->find(name)->getInfo()->turnOn();
	}
	private: System::Void commandToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		string command = msclr::interop::marshal_as<std::string>(cmdBox->Text);
		cmdBox->Text = L"";
		selectedTree->generateReport(command);
		String^ message = "Report Finshed. Check Your Desktop.";
		String^ caption = "Command Tool";
		MessageBoxButtons buttons = MessageBoxButtons::OK;
		MessageBox::Show(this, message, caption, buttons);
		
	}
};
}




