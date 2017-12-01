#pragma once

#include "DotNetUtilities.h"
#include "Mesh/GUA_OM.h"
#include "Mesh/DP.h"
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include <OpenMesh/Tools/Utils/getopt.h>

namespace panelOpenMesh_EX {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	Tri_Mesh *panelmesh;

	xform panelxf;
	GLCamera panelcamera;
	float panelfov = 0.7f;
	Mouse::button panelMouse_State = Mouse::ROTATE;

	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MeshForm : public System::Windows::Forms::Form
	{
	public:
		MeshForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MeshForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  loadModelToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openModelDialog;
	private: System::Windows::Forms::SaveFileDialog^  saveModelDialog;
	private: System::Windows::Forms::ToolStripMenuItem^  saveModelToolStripMenuItem;
	private: HKOGLPanel::HKOGLPanelControl^  hkoglPanelControl1;
	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			HKOGLPanel::HKCOGLPanelCameraSetting^  hkcoglPanelCameraSetting1 = (gcnew HKOGLPanel::HKCOGLPanelCameraSetting());
			HKOGLPanel::HKCOGLPanelPixelFormat^  hkcoglPanelPixelFormat1 = (gcnew HKOGLPanel::HKCOGLPanelPixelFormat());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadModelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveModelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openModelDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveModelDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->hkoglPanelControl1 = (gcnew HKOGLPanel::HKOGLPanelControl());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(613, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->loadModelToolStripMenuItem,
					this->saveModelToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(38, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// loadModelToolStripMenuItem
			// 
			this->loadModelToolStripMenuItem->Name = L"loadModelToolStripMenuItem";
			this->loadModelToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->loadModelToolStripMenuItem->Text = L"Load Model";
			this->loadModelToolStripMenuItem->Click += gcnew System::EventHandler(this, &MeshForm::loadModelToolStripMenuItem_Click);
			// 
			// saveModelToolStripMenuItem
			// 
			this->saveModelToolStripMenuItem->Name = L"saveModelToolStripMenuItem";
			this->saveModelToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->saveModelToolStripMenuItem->Text = L"Save Model";
			this->saveModelToolStripMenuItem->Click += gcnew System::EventHandler(this, &MeshForm::saveModelToolStripMenuItem_Click);
			// 
			// openModelDialog
			// 
			this->openModelDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MeshForm::openModelDialog_FileOk);
			// 
			// saveModelDialog
			// 
			this->saveModelDialog->DefaultExt = L"obj";
			this->saveModelDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MeshForm::saveModelDialog_FileOk);
			// 
			// hkoglPanelControl1
			// 

			hkcoglPanelCameraSetting1->Far = 1000;
			hkcoglPanelCameraSetting1->Fov = 45;
			hkcoglPanelCameraSetting1->Near = -1000;
			hkcoglPanelCameraSetting1->Type = HKOGLPanel::HKCOGLPanelCameraSetting::CAMERATYPE::ORTHOGRAPHIC;
			this->hkoglPanelControl1->Camera_Setting = hkcoglPanelCameraSetting1;
			this->hkoglPanelControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->hkoglPanelControl1->Location = System::Drawing::Point(0, 24);
			this->hkoglPanelControl1->Name = L"hkoglPanelControl1";
			hkcoglPanelPixelFormat1->Accumu_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat1->Alpha_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat1->Stencil_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			this->hkoglPanelControl1->Pixel_Format = hkcoglPanelPixelFormat1;
			this->hkoglPanelControl1->Size = System::Drawing::Size(613, 430);
			this->hkoglPanelControl1->TabIndex = 2;
			this->hkoglPanelControl1->Load += gcnew System::EventHandler(this, &MeshForm::hkoglPanelControl1_Load);
			this->hkoglPanelControl1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MeshForm::hkoglPanelControl1_Paint);
			this->hkoglPanelControl1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MeshForm::hkoglPanelControl1_MouseDown);
			this->hkoglPanelControl1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MeshForm::hkoglPanelControl1_MouseMove);
			this->hkoglPanelControl1->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &MeshForm::hkoglPanelControl1_MouseWheel);
			this->hkoglPanelControl1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MeshForm::KeyDown);
			// 
			// MeshForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(613, 454);
			this->Controls->Add(this->hkoglPanelControl1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MeshForm";
			this->Text = L"OpenMesh_EX";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void hkoglPanelControl1_Load(System::Object^  sender, EventArgs^  e)
	{

	}

	private: System::Void KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
	{
		// Determine whether the keystroke is a number from the top of the keyboard.
		if (e->KeyCode == Keys::Space)
		{

			hkoglPanelControl1->Invalidate();
		}

	}

	private: System::Void hkoglPanelControl1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
	{
		glEnable(GL_COLOR_MATERIAL);
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		point center;
		center[0] = 0.0;
		center[1] = 0.0;
		center[2] = 0.0;
		panelcamera.setupGL(panelxf * center, 1.0);

		glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		glMultMatrixd((double *)panelxf);
		if (panelmesh != NULL)
			panelmesh->Render_SolidWireframe();
		glPopMatrix();




		/*glPointSize(8.0);
		glBegin(GL_POINTS);
		glColor4f(1.0, 0.0, 0.0, 1.0);
		glVertex3dv(point(vertex_handle(0)));
		*/


	}
	private: System::Void hkoglPanelControl1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		if (e->Button == System::Windows::Forms::MouseButtons::Left ||
			e->Button == System::Windows::Forms::MouseButtons::Middle)
		{
			point center;
			panelMouse_State = Mouse::NONE;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			panelcamera.mouse(e->X, e->Y, panelMouse_State,
				panelxf * center,
				1.0, panelxf);
			point surface_point;
		}
	}
	private: System::Void hkoglPanelControl1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		if (e->Button == System::Windows::Forms::MouseButtons::Left)
		{
			point center;
			panelMouse_State = Mouse::ROTATE;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			panelcamera.mouse(e->X, e->Y, panelMouse_State,
				panelxf * center,
				1.0, panelxf);

			hkoglPanelControl1->Invalidate();
		}

		if (e->Button == System::Windows::Forms::MouseButtons::Middle)
		{
			point center;
			panelMouse_State = Mouse::MOVEXY;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			panelcamera.mouse(e->X, e->Y, panelMouse_State,
				panelxf * center,
				1.0, panelxf);
			hkoglPanelControl1->Invalidate();
		}
	}
	private: System::Void hkoglPanelControl1_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		if (e->Delta < 0)
		{
			point center;
			panelMouse_State = Mouse::WHEELDOWN;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			panelcamera.mouse(e->X, e->Y, panelMouse_State,
				panelxf * center,
				1.0, panelxf);
			hkoglPanelControl1->Invalidate();
		}
		else
		{
			point center;
			panelMouse_State = Mouse::WHEELUP;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			panelcamera.mouse(e->X, e->Y, panelMouse_State,
				panelxf * center,
				1.0, panelxf);
			hkoglPanelControl1->Invalidate();
		}
	}
	private: System::Void loadModelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		openModelDialog->Filter = "Model(*.obj)|*obj";
		openModelDialog->Multiselect = false;
		openModelDialog->ShowDialog();
	}
	private: System::Void openModelDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
	{
		std::string filename;
		MarshalString(openModelDialog->FileName, filename);

		if (panelmesh != NULL)
			delete panelmesh;

		panelmesh = new Tri_Mesh;

		if (ReadFile(filename, panelmesh))
			std::cout << filename << std::endl;

		hkoglPanelControl1->Invalidate();
	}
	private: System::Void saveModelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		saveModelDialog->Filter = "Model(*.obj)|*obj";
		saveModelDialog->ShowDialog();
	}
	private: System::Void saveModelDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
	{
		std::string filename;
		MarshalString(saveModelDialog->FileName, filename);

		if (SaveFile(filename, panelmesh))
			std::cout << filename << std::endl;
	}
	};
}