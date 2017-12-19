#pragma once
#include "DotNetUtilities.h"
#include "Mesh/GUA_OM.h"
#include "Mesh/DP.h"
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include <OpenMesh/Tools/Utils/getopt.h>
#include <vector>



static const Mouse::button physical_to_logical_map[] = {
	Mouse::NONE, Mouse::ROTATE, Mouse::MOVEXY, Mouse::MOVEZ,
	Mouse::MOVEZ, Mouse::MOVEXY, Mouse::MOVEXY, Mouse::MOVEXY,
};



namespace OpenMesh_EX {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	Tri_Mesh *mesh;
	xform xf;
	xform xfpanel;
	GLCamera camera;
	float fov = 0.7f;
	std::vector<float> y;
	point points;
	point nearest;
	bool clicked = false;
	//OpenMesh::VPropHandleT<OMT::Point> cogs;
	std::vector<std::vector<point>> pnts;
	std::vector<OMT::FIter> faces;

	GLuint textures[100];
	std::string textureNames[100];
	int textureNum = 0;
	
	Mouse::button Mouse_State = Mouse::ROTATE;


	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
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
	private: System::Windows::Forms::OpenFileDialog^  openTextureDialog;
	private: System::Windows::Forms::SaveFileDialog^  saveModelDialog;
	private: System::Windows::Forms::ToolStripMenuItem^  saveModelToolStripMenuItem;
	private: HKOGLPanel::HKOGLPanelControl^  hkoglPanelControl1;
	private: HKOGLPanel::HKOGLPanelControl^  hkoglPanelControl2;
	private: Form^ newpanel;
	private: System::Windows::Forms::ToolStripComboBox^  toolStripComboBox1;
	private: System::Windows::Forms::ToolStripMenuItem^  textureToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  loadTextureToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  textboxToolStripMenuItem;
	private: HKOGLPanel::HKOGLPanelControl^  hkoglPanelControl3;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::ListBox^  listBox1;

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
			HKOGLPanel::HKCOGLPanelCameraSetting^  hkcoglPanelCameraSetting4 = (gcnew HKOGLPanel::HKCOGLPanelCameraSetting());
			HKOGLPanel::HKCOGLPanelPixelFormat^  hkcoglPanelPixelFormat4 = (gcnew HKOGLPanel::HKCOGLPanelPixelFormat());
			HKOGLPanel::HKCOGLPanelCameraSetting^  hkcoglPanelCameraSetting5 = (gcnew HKOGLPanel::HKCOGLPanelCameraSetting());
			HKOGLPanel::HKCOGLPanelPixelFormat^  hkcoglPanelPixelFormat5 = (gcnew HKOGLPanel::HKCOGLPanelPixelFormat());
			HKOGLPanel::HKCOGLPanelCameraSetting^  hkcoglPanelCameraSetting6 = (gcnew HKOGLPanel::HKCOGLPanelCameraSetting());
			HKOGLPanel::HKCOGLPanelPixelFormat^  hkcoglPanelPixelFormat6 = (gcnew HKOGLPanel::HKCOGLPanelPixelFormat());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadModelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveModelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripComboBox1 = (gcnew System::Windows::Forms::ToolStripComboBox());
			this->textureToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadTextureToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->textboxToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openModelDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->openTextureDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveModelDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->hkoglPanelControl1 = (gcnew HKOGLPanel::HKOGLPanelControl());
			this->hkoglPanelControl2 = (gcnew HKOGLPanel::HKOGLPanelControl());
			this->hkoglPanelControl3 = (gcnew HKOGLPanel::HKOGLPanelControl());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(32, 32);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->fileToolStripMenuItem,
					this->toolStripComboBox1, this->textureToolStripMenuItem, this->textboxToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1213, 27);
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
			this->fileToolStripMenuItem->Size = System::Drawing::Size(38, 23);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// loadModelToolStripMenuItem
			// 
			this->loadModelToolStripMenuItem->Name = L"loadModelToolStripMenuItem";
			this->loadModelToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->loadModelToolStripMenuItem->Text = L"Load Model";
			this->loadModelToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::loadModelToolStripMenuItem_Click);
			// 
			// saveModelToolStripMenuItem
			// 
			this->saveModelToolStripMenuItem->Name = L"saveModelToolStripMenuItem";
			this->saveModelToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->saveModelToolStripMenuItem->Text = L"Save Model";
			this->saveModelToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::saveModelToolStripMenuItem_Click);
			// 
			// toolStripComboBox1
			// 
			this->toolStripComboBox1->Name = L"toolStripComboBox1";
			this->toolStripComboBox1->Size = System::Drawing::Size(121, 23);
			this->toolStripComboBox1->Click += gcnew System::EventHandler(this, &MyForm::toolStripComboBox1_Click);
			// 
			// textureToolStripMenuItem
			// 
			this->textureToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->loadTextureToolStripMenuItem });
			this->textureToolStripMenuItem->Name = L"textureToolStripMenuItem";
			this->textureToolStripMenuItem->Size = System::Drawing::Size(61, 23);
			this->textureToolStripMenuItem->Text = L"Texture";
			// 
			// loadTextureToolStripMenuItem
			// 
			this->loadTextureToolStripMenuItem->Name = L"loadTextureToolStripMenuItem";
			this->loadTextureToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->loadTextureToolStripMenuItem->Text = L"loadTexture";
			this->loadTextureToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::loadTextureToolStripMenuItem_Click);
			// 
			// textboxToolStripMenuItem
			// 
			this->textboxToolStripMenuItem->Name = L"textboxToolStripMenuItem";
			this->textboxToolStripMenuItem->Size = System::Drawing::Size(88, 23);
			this->textboxToolStripMenuItem->Text = L"目前texture: ";
			// 
			// openModelDialog
			// 
			this->openModelDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openModelDialog_FileOk);
			// 
			// openTextureDialog
			// 
			this->openTextureDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openTextureDialog_FileOk);
			// 
			// saveModelDialog
			// 
			this->saveModelDialog->DefaultExt = L"obj";
			this->saveModelDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::saveModelDialog_FileOk);
			// 
			// hkoglPanelControl1
			// 
			hkcoglPanelCameraSetting4->Far = 1000;
			hkcoglPanelCameraSetting4->Fov = 45;
			hkcoglPanelCameraSetting4->Near = -1000;
			hkcoglPanelCameraSetting4->Type = HKOGLPanel::HKCOGLPanelCameraSetting::CAMERATYPE::ORTHOGRAPHIC;
			this->hkoglPanelControl1->Camera_Setting = hkcoglPanelCameraSetting4;
			this->hkoglPanelControl1->Location = System::Drawing::Point(0, 30);
			this->hkoglPanelControl1->Name = L"hkoglPanelControl1";
			hkcoglPanelPixelFormat4->Accumu_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat4->Alpha_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat4->Stencil_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			this->hkoglPanelControl1->Pixel_Format = hkcoglPanelPixelFormat4;
			this->hkoglPanelControl1->Size = System::Drawing::Size(496, 441);
			this->hkoglPanelControl1->TabIndex = 2;
			this->hkoglPanelControl1->Load += gcnew System::EventHandler(this, &MyForm::hkoglPanelControl1_Load);
			this->hkoglPanelControl1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::hkoglPanelControl1_Paint);
			this->hkoglPanelControl1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::KeyDown);
			this->hkoglPanelControl1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl1_MouseDown);
			this->hkoglPanelControl1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl1_MouseMove);
			this->hkoglPanelControl1->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl1_MouseWheel);
			// 
			// hkoglPanelControl2
			// 
			hkcoglPanelCameraSetting5->Far = 1000;
			hkcoglPanelCameraSetting5->Fov = 45;
			hkcoglPanelCameraSetting5->Near = -1000;
			hkcoglPanelCameraSetting5->Type = HKOGLPanel::HKCOGLPanelCameraSetting::CAMERATYPE::ORTHOGRAPHIC;
			this->hkoglPanelControl2->Camera_Setting = hkcoglPanelCameraSetting5;
			this->hkoglPanelControl2->Location = System::Drawing::Point(715, 30);
			this->hkoglPanelControl2->Name = L"hkoglPanelControl2";
			hkcoglPanelPixelFormat5->Accumu_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat5->Alpha_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat5->Stencil_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			this->hkoglPanelControl2->Pixel_Format = hkcoglPanelPixelFormat5;
			this->hkoglPanelControl2->Size = System::Drawing::Size(496, 441);
			this->hkoglPanelControl2->TabIndex = 3;
			this->hkoglPanelControl2->Load += gcnew System::EventHandler(this, &MyForm::hkoglPanelControl1_Load);
			this->hkoglPanelControl2->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panel_Paint);
			this->hkoglPanelControl2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::KeyDown);
			this->hkoglPanelControl2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl2_MouseDown);
			this->hkoglPanelControl2->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl2_MouseMove);
			this->hkoglPanelControl2->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl2_MouseWheel);
			// 
			// hkoglPanelControl3
			// 
			hkcoglPanelCameraSetting6->Far = 1000;
			hkcoglPanelCameraSetting6->Fov = 45;
			hkcoglPanelCameraSetting6->Near = -1000;
			hkcoglPanelCameraSetting6->Type = HKOGLPanel::HKCOGLPanelCameraSetting::CAMERATYPE::ORTHOGRAPHIC;
			this->hkoglPanelControl3->Camera_Setting = hkcoglPanelCameraSetting6;
			this->hkoglPanelControl3->Location = System::Drawing::Point(502, 30);
			this->hkoglPanelControl3->Name = L"hkoglPanelControl3";
			hkcoglPanelPixelFormat6->Accumu_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat6->Alpha_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat6->Stencil_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			this->hkoglPanelControl3->Pixel_Format = hkcoglPanelPixelFormat6;
			this->hkoglPanelControl3->Size = System::Drawing::Size(207, 183);
			this->hkoglPanelControl3->TabIndex = 5;
			this->hkoglPanelControl3->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::hkoglPanelControl3_Paint);
			// 
			// button6
			// 
			this->button6->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->button6->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->button6->Location = System::Drawing::Point(502, 381);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(200, 47);
			this->button6->TabIndex = 18;
			this->button6->Text = L"Texture!!!";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			// 
			// button4
			// 
			this->button4->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->button4->Font = (gcnew System::Drawing::Font(L"新細明體", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->button4->Location = System::Drawing::Point(502, 350);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(80, 25);
			this->button4->TabIndex = 17;
			this->button4->Text = L"Load Texture";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// listBox1
			// 
			this->listBox1->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->listBox1->FormattingEnabled = true;
			this->listBox1->HorizontalScrollbar = true;
			this->listBox1->ItemHeight = 12;
			this->listBox1->Location = System::Drawing::Point(502, 256);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(207, 88);
			this->listBox1->TabIndex = 16;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listBox1_SelectedIndexChanged);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(1213, 490);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->hkoglPanelControl3);
			this->Controls->Add(this->hkoglPanelControl1);
			this->Controls->Add(this->hkoglPanelControl2);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"OpenMesh_EX";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
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
			pnts.clear();
			faces.clear();
			mesh->refreshPlane();
			hkoglPanelControl1->Invalidate();
			hkoglPanelControl2->Invalidate();
		}
		if (e->KeyCode == Keys::Enter)
		{
			for (int i = 0; i < faces.size(); i++)
				mesh->property(mesh->confirmed, faces[i]) = true;

			pnts.clear();
			faces.clear();
			mesh->refreshPlane();
			hkoglPanelControl1->Invalidate();
			hkoglPanelControl2->Invalidate();
		}
	}


	private: System::Void panel_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
	{
		glEnable(GL_COLOR_MATERIAL);
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		point center;
		center[0] = 0.0;
		center[1] = 0.0;
		center[2] = 0.0;
		camera.setupGL(xfpanel * center, 1.0);

		glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		glMultMatrixd((double *)xfpanel);
		if (mesh != NULL) {
			
			mesh->RenderTextureOn();
			/*std::cout << "outer: " << std::endl;
			for (int i = 0; i < outerpnts.size(); i++) {
				std::cout << i << ": " << plane->point(outerpnts[i]).data()[0] << " " << plane->point(outerpnts[i]).data()[1] << " " << plane->point(outerpnts[i]).data()[2];
				std::cout << " 2D: " << plane->property(cogs, outerpnts[i])[0] << " " << plane->property(cogs, outerpnts[i])[1] << " " << plane->property(cogs, outerpnts[i])[2] << std::endl;
			}
			std::cout << "inner: " << std::endl;
			for (int i = 0; i < innerpnts.size(); i++) {
				std::cout << i << ": " << plane->point(innerpnts[i]).data()[0] << " " << plane->point(innerpnts[i]).data()[1] << " " << plane->point(innerpnts[i]).data()[2];
				std::cout << " 2D: " << plane->property(cogs, innerpnts[i])[0] << " " << plane->property(cogs, innerpnts[i])[1] << " " << plane->property(cogs, innerpnts[i])[2] << std::endl;
			}*/
			//std::cout << std::endl;
			//turn the points around the faces into Viterators

		}
		

	}

	private: System::Void hkoglPanelControl3_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-1, 1, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glPushMatrix();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.02f, 0.3f, 0.55f, 1.0f);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPushMatrix();
		if (mesh != NULL) {
			glBindTexture(GL_TEXTURE_2D, TextureApp::GenTexture((char *)mesh->currenttexture.c_str()));
		}
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0); glVertex2d(-1, -1);
		glTexCoord2d(1, 0); glVertex2d(1, -1);
		glTexCoord2d(1, 1); glVertex2d(1, 1);
		glTexCoord2d(0, 1); glVertex2d(-1, 1);
		glEnd();
		glPopMatrix();

		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);

		glPopMatrix();

		//hkoglPanelControl2->Invalidate();
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
		camera.setupGL(xf * center, 1.0);

		glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		glMultMatrixd((double *)xf);
		if (mesh != NULL)
			mesh->Render_SolidWireframe();
		glPopMatrix();
		glColor3f(255, 0, 0);
		if (clicked) {
			glPointSize(10);
			glBegin(GL_POINTS);
			glVertex3f(points[0], points[1], points[2] + 0.001);
			glEnd();

			if (mesh != NULL) {
				//check for the nearest vertices
				for (int i = 0; i < 3; i++)
					nearest[i] = mesh->point(mesh->vv_iter(mesh->vertices_begin()).handle()).data()[i];
				for (OMT::VIter v_it = mesh->vertices_begin(); v_it != mesh->vertices_end(); ++v_it)
				{
					point p;
					double dist = 0, distcompr = 0;
					for (int i = 0; i < 3; i++)
						p[i] = mesh->point(v_it.handle()).data()[i];
					point nearcompare = xf*nearest;
					point pcompare = xf*p;
					dist = sqrt(pow((points[0] - pcompare[0]), 2) + pow((points[1] - pcompare[1]), 2) + pow((points[2] - pcompare[2]), 2));
					distcompr = sqrt(pow((points[0] - nearcompare[0]), 2) + pow((points[1] - nearcompare[1]), 2) + pow((points[2] - nearcompare[2]), 2));
					if (dist < distcompr) {
						nearest = p;
					}
				}


				//check the nearest face 
				point face[3];
				point facecenter;
				OMT::FIter currentface = mesh->faces_begin();
				int k = 0;
				for (OMT::FVIter fv_it = mesh->fv_iter(mesh->faces_begin()); fv_it; ++fv_it)
				{
					for (int j = 0; j < 3; j++) {
						face[k][j] = mesh->point(fv_it.handle()).data()[j];
					}
					k++;
				}
				facecenter = (face[0] + face[1] + face[2]);
				for (int i = 0; i < 3; i++)
					facecenter[i] = facecenter[i] / 3;

				glColor4f(1.0, 0.96, 0.49, 1.0);
				//std::cout << "mouse in GUA_OM:" << clickPoint[0] << " " << clickPoint[1] << " " << clickPoint[2] << std::endl;
				for (OMT::FIter f_it = mesh->faces_begin(); f_it != mesh->faces_end(); ++f_it)
				{
					point p[3];
					point gcenter;
					double dist = 0, distcompr = 0;
					int i = 0;
					for (OMT::FVIter fv_it = mesh->fv_iter(f_it); fv_it; ++fv_it)
					{
						for (int j = 0; j < 3; j++) {
							p[i][j] = mesh->point(fv_it.handle()).data()[j];
						}
						i++;
					}
					gcenter = (p[0] + p[1] + p[2]);
					for (int i = 0; i < 3; i++)
						gcenter[i] = gcenter[i] / 3;
					point fcompare = xf * facecenter;
					point gcompare = xf * gcenter;
					dist = sqrt(pow((points[0] - gcompare[0]), 2) + pow((points[1] - gcompare[1]), 2) + pow((points[2] - gcompare[2]), 2));
					distcompr = sqrt(pow((points[0] - fcompare[0]), 2) + pow((points[1] - fcompare[1]), 2) + pow((points[2] - fcompare[2]), 2));
					if (dist < distcompr) {
						facecenter = gcenter;
						currentface = f_it;
						for (int i = 0; i < 3; i++) {
							face[i] = p[i];
						}
					}
				}
				bool faceexists = false;
				bool neighboringface = false;
				if (faces.size() == 0) {
					neighboringface = true;
				}
				for (int i = 0; i < faces.size(); i++) {
					if (currentface == faces[i])
						faceexists = true;
				}
				if (faces.size() != 0) {
					for (int i = 0; i < faces.size(); i++) {
						for (OMT::FFIter ff_it = mesh->ff_iter(currentface); ff_it; ++ff_it) {
							if (ff_it.handle() == faces[i]) {
								neighboringface = true;
								break;
							}
						}
					}

				}
				if (!faceexists && neighboringface && !mesh->property(mesh->confirmed,currentface)) {
					std::vector<point> facetemp;
					for (int i = 0; i < 3; i++)
						facetemp.push_back(face[i]);
					pnts.push_back(facetemp);
					faces.push_back(currentface);
					std::vector<OMT::VHandle> face_vhandles;
					for (OMT::FVIter fv_it = mesh->fv_iter(currentface); fv_it; ++fv_it)
					{
						OMT::VIter v_it;
						bool exists = false;
						for (v_it = mesh->plane->vertices_begin(); v_it != mesh->plane->vertices_end(); ++v_it) {
							if (mesh->plane->point(v_it.handle()) == mesh->point(fv_it.handle())) {
								exists = true;
								break;
							}
						}
						if (exists)
							face_vhandles.push_back(v_it.handle());
						else
							face_vhandles.push_back(mesh->plane->add_vertex(mesh->point(fv_it.handle())));

					}
					mesh->setPlaneFacetoMeshFace(currentface, mesh->plane->add_face(face_vhandles));
					mesh->setOuterPoints();
					mesh->setWeight();
					mesh->Parameterize();
					hkoglPanelControl2->Invalidate();
				}
				
			}
			clicked = false;

		}

		point realnear = xf*nearest;
		glPointSize(10);
		glColor3f(255, 0, 0);
		glBegin(GL_POINTS);
		glVertex3f(realnear[0], realnear[1], realnear[2]);
		glEnd();

		glColor3f(0, 0, 255);
		for (int i = 0; i < pnts.size(); i++) {
			point out[3];
			for (int j = 0; j < 3; j++)
				out[j] = xf * pnts[i][j];
			glBegin(GL_TRIANGLES);
			glVertex3f(out[0][0], out[0][1], out[0][2] + 0.0001);
			glVertex3f(out[1][0], out[1][1], out[1][2] + 0.0001);
			glVertex3f(out[2][0], out[2][1], out[2][2] + 0.0001);
			glEnd();
		}

		if (mesh != NULL) {
			for (OMT::FIter f_it = mesh->faces_begin(); f_it != mesh->faces_end(); ++f_it)
			{
				point p[3];
				if (mesh->property(mesh->confirmed, f_it)) {
					point out[3];
					int i = 0;
					glColor3f(0, 255, 0);
					glBegin(GL_TRIANGLES);
					for (OMT::FVIter fv_it = mesh->fv_iter(f_it); fv_it; ++fv_it)
					{
						//glNormal3dv(normal(fv_it.handle()));
						for (int j = 0; j < 3; j++)
							p[i][j] = mesh->point(fv_it.handle()).data()[j];
						for (int j = 0; j < 3; j++)
							out[i] = xf * p[i];
						
						//glVertex3dv(point(fv_it.handle()).data());
						i++;
						//std::cout << p[0] << std::endl;
						//std::cout << point(fv_it.handle()).data()[0] << " " << point(fv_it.handle()).data()[1] << " " << point(fv_it.handle()).data()[2] << " " << std::endl;
					}
					glVertex3f(out[0][0], out[0][1], out[0][2] + 0.0001);
					glVertex3f(out[1][0], out[1][1], out[1][2] + 0.0001);
					glVertex3f(out[2][0], out[2][1], out[2][2] + 0.0001);
					glEnd();
				}
			}
		}

		/*glPointSize(8.0);
		glBegin(GL_POINTS);
		glColor4f(1.0, 0.0, 0.0, 1.0);
		glVertex3dv(point(vertex_handle(0)));
		glEnd();*/
		if (mesh != NULL) {

		}


	}
	private: System::Void hkoglPanelControl1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		if (e->Button == System::Windows::Forms::MouseButtons::Left ||
			e->Button == System::Windows::Forms::MouseButtons::Middle)
		{
			point center;
			Mouse_State = Mouse::NONE;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State,
				xf * center,
				1.0, xf);
			point surface_point;
			if (camera.read_depth(e->X, hkoglPanelControl1->Height - e->Y, surface_point)) {
				points = surface_point;
				clicked = true;
			}
		}
	}
	private: System::Void hkoglPanelControl1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		if (e->Button == System::Windows::Forms::MouseButtons::Left)
		{
			point center;
			Mouse_State = Mouse::ROTATE;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State,
				xf * center,
				1.0, xf);

			hkoglPanelControl1->Invalidate();
		}

		if (e->Button == System::Windows::Forms::MouseButtons::Middle)
		{
			point center;
			Mouse_State = Mouse::MOVEXY;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State,
				xf * center,
				1.0, xf);
			hkoglPanelControl1->Invalidate();
		}
	}
	private: System::Void hkoglPanelControl1_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		if (e->Delta < 0)
		{
			point center;
			Mouse_State = Mouse::WHEELDOWN;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State,
				xf * center,
				1.0, xf);
			hkoglPanelControl1->Invalidate();
		}
		else
		{
			point center;
			Mouse_State = Mouse::WHEELUP;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State,
				xf * center,
				1.0, xf);
			hkoglPanelControl1->Invalidate();
		}
	}

	private: System::Void hkoglPanelControl2_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		if (e->Button == System::Windows::Forms::MouseButtons::Left ||
			e->Button == System::Windows::Forms::MouseButtons::Middle)
		{
			point center;
			Mouse_State = Mouse::NONE;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State,
				xfpanel * center,
				1.0, xfpanel);
		}
	}

	private: System::Void hkoglPanelControl2_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		if (e->Button == System::Windows::Forms::MouseButtons::Left)
		{
			point center;
			Mouse_State = Mouse::ROTATE;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State,
				xfpanel * center,
				1.0, xfpanel);

			hkoglPanelControl2->Invalidate();
		}

		if (e->Button == System::Windows::Forms::MouseButtons::Middle)
		{
			point center;
			Mouse_State = Mouse::MOVEXY;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State,
				xfpanel * center,
				1.0, xfpanel);
			hkoglPanelControl2->Invalidate();
		}
	}
	private: System::Void hkoglPanelControl2_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		if (e->Delta < 0)
		{
			point center;
			Mouse_State = Mouse::WHEELDOWN;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State,
				xfpanel * center,
				1.0, xfpanel);
			hkoglPanelControl2->Invalidate();
		}
		else
		{
			point center;
			Mouse_State = Mouse::WHEELUP;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State,
				xfpanel * center,
				1.0, xfpanel);
			hkoglPanelControl2->Invalidate();
		}
	}


	private: System::Void loadModelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		openModelDialog->Filter = "Model(*.obj)|*obj";
		openModelDialog->Multiselect = false;
		openModelDialog->ShowDialog();
	}
	private: System::Void loadTextureToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		openTextureDialog->Filter = "Image Files(*.BMP;*.JPG;*.GIF)|*.BMP;*.JPG;*.GIF";
		openTextureDialog->Multiselect = false;
		openTextureDialog->ShowDialog();
	}
	private: System::Void toolStripComboBox1_Click(System::Object^  sender, System::EventArgs^  e) {

	}
	private: System::Void openModelDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
	{
		std::string filename;
		MarshalString(openModelDialog->FileName, filename);

		if (mesh != NULL)
			delete mesh;

		mesh = new Tri_Mesh;
		
		if (ReadFile(filename, mesh))
			std::cout << filename << std::endl;
		mesh->plane = new Tri_Mesh;
		mesh->initTexture();
		

		hkoglPanelControl1->Invalidate();
	}
	private: System::Void openTextureDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
	{
		hkoglPanelControl3->Refresh();
		std::string filename;
		MarshalString(openTextureDialog->FileName, filename);
		this->textboxToolStripMenuItem->Text = "新增texture: " + openTextureDialog->FileName;
		std::cout << "open texture" << std::endl;
		std::cout << filename << std::endl;
		//plane->initTexture();

		/*if (mesh != NULL) {
		mesh->addTexture(filename);
		}*/
		std::cout << "Loaded Texture:" << filename << std::endl;
		listBox1->Items->Add(openTextureDialog->FileName);
		char *f = new char[filename.length() + 1];
		strcpy(f, filename.c_str());
		//textures[textureNum] = TextureApp::GenTexture(f);
		mesh->addTexture(filename);
		textureNames[textureNum] = filename;
		std::cout << "texture index: " << textureNum << std::endl;
		textureNum++;

		hkoglPanelControl1->Invalidate();
		hkoglPanelControl3->Invalidate();
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

		if (SaveFile(filename, mesh))
			std::cout << filename << std::endl;
	}


	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}


	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		openTextureDialog->Filter = "Image Files(*.BMP;*.JPG;*.GIF)|*.BMP;*.JPG;*.GIF";
		openTextureDialog->Multiselect = false;
		openTextureDialog->ShowDialog();
	}
	private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		std::string filename = textureNames[listBox1->SelectedIndex];
		this->textboxToolStripMenuItem->Text = "目前texture: " + openTextureDialog->FileName;
		std::cout << "selected " << listBox1->SelectedIndex << std::endl;

		for (int i=0;i<faces.size();i++)
		{
			for (OMT::FVIter fv_it = mesh->fv_iter(faces[i]); fv_it; ++fv_it) {
				for (int k = 0; k < mesh->property(mesh->cogs, fv_it.handle()).size(); k++) {
					if (mesh->property(mesh->cogs, fv_it.handle())[k].texture == mesh->property(mesh->usingtext, faces[i])) {
						mesh->property(mesh->cogs, fv_it.handle())[k].texture = filename;
					}
				}
			}
			mesh->property(mesh->usingtext, faces[i]) = filename;
		}
		mesh->currenttexture = filename;
		hkoglPanelControl2->Refresh();
		hkoglPanelControl3->Refresh();
	}
	private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
		if (listBox1->SelectedIndex != -1) {
			if (mesh != NULL) {
				std::string filename = textureNames[listBox1->SelectedIndex];
				//mesh->addTexture(filename);
			}
		}
	}
};
}

