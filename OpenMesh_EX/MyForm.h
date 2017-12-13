#pragma once

#include "DotNetUtilities.h"
#include "Mesh/GUA_OM.h"
#include "Mesh/DP.h"
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include <OpenMesh/Tools/Utils/getopt.h>

#include <vector>
#include <Eigen\Sparse>
#define PI 3.14159265

using namespace Eigen;


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
	Tri_Mesh *plane;
	xform xf;
	xform xfpanel;
	GLCamera camera;
	GLCamera camera2;
	float fov = 0.7f;
	std::vector<float> y;
	point points;
	point nearest;
	bool clicked = false;
	OpenMesh::VPropHandleT<OMT::Point> cogs;
	std::vector<std::vector<point>> pnts;
	std::vector<OMT::FIter> faces;
	std::vector<OMT::VHandle> outerpnts;
	std::vector<OMT::VHandle> innerpnts;
	std::vector<std::vector<double>> weights;
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
	private: System::Windows::Forms::SaveFileDialog^  saveModelDialog;
	private: System::Windows::Forms::ToolStripMenuItem^  saveModelToolStripMenuItem;
	private: HKOGLPanel::HKOGLPanelControl^  hkoglPanelControl1;
	private: HKOGLPanel::HKOGLPanelControl^  hkoglPanelControl2;
	private: Form^ newpanel;
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
			HKOGLPanel::HKCOGLPanelCameraSetting^  hkcoglPanelCameraSetting5 = (gcnew HKOGLPanel::HKCOGLPanelCameraSetting());
			HKOGLPanel::HKCOGLPanelPixelFormat^  hkcoglPanelPixelFormat5 = (gcnew HKOGLPanel::HKCOGLPanelPixelFormat());
			HKOGLPanel::HKCOGLPanelCameraSetting^  hkcoglPanelCameraSetting6 = (gcnew HKOGLPanel::HKCOGLPanelCameraSetting());
			HKOGLPanel::HKCOGLPanelPixelFormat^  hkcoglPanelPixelFormat6 = (gcnew HKOGLPanel::HKCOGLPanelPixelFormat());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadModelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveModelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openModelDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveModelDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->hkoglPanelControl1 = (gcnew HKOGLPanel::HKOGLPanelControl());
			this->hkoglPanelControl2 = (gcnew HKOGLPanel::HKOGLPanelControl());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(32, 32);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(12, 4, 0, 4);
			this->menuStrip1->Size = System::Drawing::Size(2034, 44);
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
			this->fileToolStripMenuItem->Size = System::Drawing::Size(64, 36);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// loadModelToolStripMenuItem
			// 
			this->loadModelToolStripMenuItem->Name = L"loadModelToolStripMenuItem";
			this->loadModelToolStripMenuItem->Size = System::Drawing::Size(268, 38);
			this->loadModelToolStripMenuItem->Text = L"Load Model";
			this->loadModelToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::loadModelToolStripMenuItem_Click);
			// 
			// saveModelToolStripMenuItem
			// 
			this->saveModelToolStripMenuItem->Name = L"saveModelToolStripMenuItem";
			this->saveModelToolStripMenuItem->Size = System::Drawing::Size(268, 38);
			this->saveModelToolStripMenuItem->Text = L"Save Model";
			this->saveModelToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::saveModelToolStripMenuItem_Click);
			// 
			// openModelDialog
			// 
			this->openModelDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openModelDialog_FileOk);
			// 
			// saveModelDialog
			// 
			this->saveModelDialog->DefaultExt = L"obj";
			this->saveModelDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::saveModelDialog_FileOk);
			// 
			// hkoglPanelControl1
			// 
			hkcoglPanelCameraSetting5->Far = 1000;
			hkcoglPanelCameraSetting5->Fov = 45;
			hkcoglPanelCameraSetting5->Near = -1000;
			hkcoglPanelCameraSetting5->Type = HKOGLPanel::HKCOGLPanelCameraSetting::CAMERATYPE::ORTHOGRAPHIC;
			this->hkoglPanelControl1->Camera_Setting = hkcoglPanelCameraSetting5;
			this->hkoglPanelControl1->Location = System::Drawing::Point(0, 36);
			this->hkoglPanelControl1->Margin = System::Windows::Forms::Padding(6, 6, 6, 6);
			this->hkoglPanelControl1->Name = L"hkoglPanelControl1";
			hkcoglPanelPixelFormat5->Accumu_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat5->Alpha_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat5->Stencil_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			this->hkoglPanelControl1->Pixel_Format = hkcoglPanelPixelFormat5;
			this->hkoglPanelControl1->Size = System::Drawing::Size(993, 918);
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
			hkcoglPanelCameraSetting6->Far = 1000;
			hkcoglPanelCameraSetting6->Fov = 45;
			hkcoglPanelCameraSetting6->Near = -1000;
			hkcoglPanelCameraSetting6->Type = HKOGLPanel::HKCOGLPanelCameraSetting::CAMERATYPE::ORTHOGRAPHIC;
			this->hkoglPanelControl2->Camera_Setting = hkcoglPanelCameraSetting6;
			this->hkoglPanelControl2->Location = System::Drawing::Point(1038, 36);
			this->hkoglPanelControl2->Margin = System::Windows::Forms::Padding(6, 6, 6, 6);
			this->hkoglPanelControl2->Name = L"hkoglPanelControl2";
			hkcoglPanelPixelFormat6->Accumu_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat6->Alpha_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat6->Stencil_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			this->hkoglPanelControl2->Pixel_Format = hkcoglPanelPixelFormat6;
			this->hkoglPanelControl2->Size = System::Drawing::Size(993, 918);
			this->hkoglPanelControl2->TabIndex = 3;
			this->hkoglPanelControl2->Load += gcnew System::EventHandler(this, &MyForm::hkoglPanelControl1_Load);
			this->hkoglPanelControl2->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panel_Paint);
			this->hkoglPanelControl2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::KeyDown);
			this->hkoglPanelControl2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl2_MouseDown);
			this->hkoglPanelControl2->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl2_MouseMove);
			this->hkoglPanelControl2->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl2_MouseWheel);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(2034, 1020);
			this->Controls->Add(this->hkoglPanelControl1);
			this->Controls->Add(this->hkoglPanelControl2);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(6, 6, 6, 6);
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
			plane = NULL;
			hkoglPanelControl1->Invalidate();
			hkoglPanelControl2->Invalidate();
			faces.clear();

		}
		if (e->KeyCode == Keys::Enter)
		{

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
		camera2.setupGL(xfpanel * center, 1.0);

		glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		glMultMatrixd((double *)xfpanel);
		if (plane != NULL) {
			plane->Render_SolidWireframe();
			setOuterPoints();
			setWeight();
			Parameterize();
			std::cout <<"outer: "<<std::endl;
			for (int i = 0; i < outerpnts.size(); i++) {
				std::cout << i << ": " << plane->point(outerpnts[i]).data()[0] << " " << plane->point(outerpnts[i]).data()[1] << " " << plane->point(outerpnts[i]).data()[2];
				std::cout << " 2D: " << plane->property(cogs, outerpnts[i])[0] << " " << plane->property(cogs, outerpnts[i])[1] << " " << plane->property(cogs, outerpnts[i])[2] << std::endl;
			}
			std::cout << "inner: " << std::endl;
			for (int i = 0; i < innerpnts.size(); i++) {
				std::cout << i << ": " << plane->point(innerpnts[i]).data()[0] << " " << plane->point(innerpnts[i]).data()[1] << " " << plane->point(innerpnts[i]).data()[2];
				std::cout << " 2D: " << plane->property(cogs, innerpnts[i])[0] << " " << plane->property(cogs, innerpnts[i])[1] << " " << plane->property(cogs, innerpnts[i])[2] << std::endl;
			}
			std::cout << std::endl;
			//turn the points around the faces into Viterators
		}
		if (plane != NULL) {
			for (OMT::VIter v_it = plane->vertices_begin(); v_it != plane->vertices_end(); ++v_it)
			{
				//std::cout << v_it << ": " << plane->point(v_it.handle()).data()[0] << " " << plane->point(v_it.handle()).data()[1] << " " << plane->point(v_it.handle()).data()[2] << std::endl;
			}

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
					plane = new Tri_Mesh;
					plane->add_property(cogs);
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
				if (!faceexists && neighboringface) {
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
						for (v_it = plane->vertices_begin(); v_it != plane->vertices_end(); ++v_it) {
							if (plane->point(v_it.handle()) == mesh->point(fv_it.handle())) {
								exists = true;
								break;
							}
						}
						if (exists)
							face_vhandles.push_back(v_it.handle());
						else
							face_vhandles.push_back(plane->add_vertex(mesh->point(fv_it.handle())));
					}
					plane->add_face(face_vhandles);
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
			camera2.mouse(e->X, e->Y, Mouse_State,
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
			camera2.mouse(e->X, e->Y, Mouse_State,
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
			camera2.mouse(e->X, e->Y, Mouse_State,
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
			camera2.mouse(e->X, e->Y, Mouse_State,
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
			camera2.mouse(e->X, e->Y, Mouse_State,
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
	private: System::Void openModelDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
	{
		std::string filename;
		MarshalString(openModelDialog->FileName, filename);

		if (mesh != NULL)
			delete mesh;

		mesh = new Tri_Mesh;
		plane = new Tri_Mesh;
		plane->add_property(cogs);

		if (ReadFile(filename, mesh))
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

		if (SaveFile(filename, mesh))
			std::cout << filename << std::endl;
	}


	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}


	private: void setOuterPoints() {
		outerpnts.clear();
		innerpnts.clear();
		OMT::VertexHandle heh, heh_init;
		std::cout << plane->faces_end() << std::endl;
		for (OMT::VIter v_it = plane->vertices_begin(); v_it != plane->vertices_end(); ++v_it) {
			std::cout <<"start: "<< plane->point(v_it.handle()).data()[0] << " " << plane->point(v_it.handle()).data()[1] << " " << plane->point(v_it.handle()).data()[2] << std::endl;
			heh = heh_init = v_it.handle();
			if (plane->is_boundary(heh_init)) 
				break;
		}
		//!((plane->is_boundary(plane->halfedge_handle(voh_it)) && plane->is_boundary(plane->opposite_halfedge_handle(plane->halfedge_handle(voh_it))))) ||
		for (OMT::VOHEIter voh_it = plane->voh_iter(heh_init); voh_it; ++voh_it) {
			// Iterate over all outgoing halfedges...
			if (plane->is_boundary(plane->to_vertex_handle(voh_it))) {
				heh = plane->to_vertex_handle(voh_it);
				std::cout << "second: " << plane->point(plane->to_vertex_handle(voh_it))[0] << " " << plane->point(plane->to_vertex_handle(voh_it))[1] << " " << plane->point(plane->to_vertex_handle(voh_it))[2] << std::endl;
				outerpnts.push_back(heh);
				break;
			}
		}
		// We can do this as often as we want:
		while (heh != heh_init) {
			for (OMT::VOHEIter voh_it = plane->voh_iter(heh); voh_it; ++voh_it) {
				// Iterate over all outgoing halfedges...
				bool exists = false;
				for (int i = 0; i < outerpnts.size(); i++) {
					if (plane->to_vertex_handle(plane->halfedge_handle(voh_it)) == outerpnts[i]) {
						exists = true;
						break;
					}
				}
				if ((plane->is_boundary(plane->to_vertex_handle(voh_it)))
					&& !exists) {		
					heh = plane->to_vertex_handle(voh_it);
					std::cout << plane->point(plane->to_vertex_handle(voh_it))[0] << " " << plane->point(plane->to_vertex_handle(voh_it))[1] << " " << plane->point(plane->to_vertex_handle(voh_it))[2] << std::endl;
					outerpnts.push_back(heh);
					break;
				}
			}
		}
		for (OMT::VIter v_it = plane->vertices_begin(); v_it != plane->vertices_end(); ++v_it) {
			bool exists = false;
			for (int i = 0; i < outerpnts.size(); i++) {
				if (outerpnts[i] == v_it.handle()) {
					exists = true;
					break;
				}
			}
			if (!exists)
				innerpnts.push_back(v_it.handle());
		}
		
	}

	private: void setWeight() {
		
		OMT::VHandle firstpnt;
		OMT::VHandle secondpnt;
		weights.clear();
		double cog;
		for (int i = 0; i < innerpnts.size(); i++) {
			std::vector<double> circleweight;
			for (OMT::VVIter vvit = plane->vv_iter(innerpnts[i]); vvit; ++vvit) {
				bool firstpntset = false;
				for (OMT::VVIter vvitvvit = plane->vv_iter(vvit); vvitvvit; ++vvitvvit) {
					for (OMT::VVIter vvcomp = plane->vv_iter(innerpnts[i]); vvcomp; ++vvcomp) {
						if (mesh->point(vvitvvit.handle()) == mesh->point(vvcomp.handle()) && firstpntset) {
							secondpnt = vvitvvit.handle();
							break;
						}
						if (mesh->point(vvitvvit.handle()) == mesh->point(vvcomp.handle())) {
							firstpnt = vvitvvit.handle();
							firstpntset = true;
						}
					}
				}
				OMT::Vec3d firstvct = mesh->point(firstpnt) - mesh->point(innerpnts[i]);
				OMT::Vec3d secondvct = mesh->point(secondpnt) - mesh->point(innerpnts[i]);
				OMT::Vec3d vvitvct = mesh->point(vvit.handle()) - mesh->point(innerpnts[i]);
				double weight = (tan((calcAngle(firstvct, vvitvct) / 2) * PI / 180.0) + tan((calcAngle(vvitvct, secondvct) / 2) * PI / 180.0)) / vvitvct.length();
				circleweight.push_back(weight);
			}
			weights.push_back(circleweight);
		}
	}

	private: void Parameterize() {
		int size = 4;
		double scale = 0;
		double distance = 0;
		double currentdist = 0;
		std::vector<double> oneline;
		for (int i = 0; i < outerpnts.size(); i++) {
			distance += sqrt(pow(plane->point(outerpnts[i%outerpnts.size()]).data()[0] - plane->point(outerpnts[(i + 1) % outerpnts.size()]).data()[0], 2) +
				pow(plane->point(outerpnts[i%outerpnts.size()]).data()[1] - plane->point(outerpnts[(i + 1) % outerpnts.size()]).data()[1], 2) +
				pow(plane->point(outerpnts[i%outerpnts.size()]).data()[2] - plane->point(outerpnts[(i + 1) % outerpnts.size()]).data()[2], 2));
		}
		std::cout << distance << std::endl;
		scale = distance / size;
		for (int i = 0; i < outerpnts.size(); i++) {
			double pntdistance = sqrt(pow(plane->point(outerpnts[i%outerpnts.size()]).data()[0] - plane->point(outerpnts[(i + 1) % outerpnts.size()]).data()[0], 2) +
				pow(plane->point(outerpnts[i%outerpnts.size()]).data()[1] - plane->point(outerpnts[(i + 1) % outerpnts.size()]).data()[1], 2) +
				pow(plane->point(outerpnts[i%outerpnts.size()]).data()[2] - plane->point(outerpnts[(i + 1) % outerpnts.size()]).data()[2], 2));
			currentdist += pntdistance / scale;
			oneline.push_back(currentdist);
		}

		// smoothing mesh argv[1] times
		OMT::Point               cog;
		plane->remove_property(cogs);
		plane->add_property(cogs);
		for (int i = 0; i < outerpnts.size(); i++)
		{
			plane->property(cogs, outerpnts[i]).vectorize(0.0f);
			if (oneline[i] <= 1) {
				plane->property(cogs, outerpnts[i]) = OMT::Point(oneline[i], 0, 0);
			}
			else if (oneline[i] <= 2) {
				plane->property(cogs, outerpnts[i]) = OMT::Point(1, oneline[i] - 1, 0);
			}
			else if (oneline[i] <= 3) {
				plane->property(cogs, outerpnts[i]) = OMT::Point(1 - (oneline[i] - 2), 1, 0);
			}
			else if (oneline[i] <= 4) {
				plane->property(cogs, outerpnts[i]) = OMT::Point(0, 1 - (oneline[i] - 3), 0);
			}
		}

		if (innerpnts.size() > 0) {
			SparseMatrix<double> A(innerpnts.size(), innerpnts.size());
			std::vector<VectorXd> B;
			B.resize(2); //B is 2D

			B[0].resize(innerpnts.size());
			B[1].resize(innerpnts.size());

			for (int i = 0; i < innerpnts.size(); i++) {
				for (int j = 0; j < innerpnts.size(); j++) {
					int k = 0;
					if (i == j) {
						double totalweight = 0;
						for (int w = 0; w < weights[i].size(); w++)
							totalweight += weights[i][w];
						A.insert(i, j) = totalweight;
					}
					if (i != j) {
						for (OMT::VVIter vvit = plane->vv_iter(innerpnts[i]); vvit; ++vvit) {
							if (vvit.handle() == innerpnts[j]) {
								A.insert(i, j) = weights[i][k] * -1;
								break;
							}
							k++;
						}
					}
				}
			}
			A.makeCompressed();

			for (int i = 0; i < innerpnts.size(); i++) {
				double outerweightx = 0;
				double outerweighty = 0;
				for (int j = 0; j < outerpnts.size(); j++) {
					int k = 0;
					for (OMT::VVIter vvit = plane->vv_iter(innerpnts[i]); vvit; ++vvit) {
						if (vvit.handle() == outerpnts[j]) {
							outerweightx += weights[i][k] * plane->property(cogs, outerpnts[j])[0];
							outerweighty += weights[i][k] * plane->property(cogs, outerpnts[j])[1];
							break;
						}
						k++;
					}
				}
				B[0][i] = outerweightx;
				B[1][i] = outerweightx;
			}

			SparseQR<SparseMatrix<double>, COLAMDOrdering<int>> linearSolver;
			linearSolver.compute(A);

			std::vector<VectorXd> X;
			X.resize(2);

			X[0] = linearSolver.solve(B[0]);
			X[1] = linearSolver.solve(B[1]);


			for (int i = 0; i < innerpnts.size(); i++) {
				plane->property(cogs, innerpnts[i]).vectorize(0.0f);
				plane->property(cogs, innerpnts[i]) = OMT::Point(X[0][i], X[1][i], 0);
			}
		}
		/*for (v_it = mesh.vertices_begin(); v_it != v_end; ++v_it)
			if (!mesh.is_boundary(*v_it))
				mesh.set_point(*v_it, mesh.property(cogs, *v_it));*/



		
		/*for (int i = 0; i < outerpnts.size(); i++)
		{
			mesh->property(cogs, outerpnts[i]).vectorize(0.0f);
			if (i == 0)
				continue;
			for (vv_it = mesh.vv_iter(*v_it); vv_it; ++vv_it)
			{
				mesh.property(cogs, *v_it) += mesh.point(*vv_it);
			}
			mesh.property(cogs, *v_it) /= valence;
		}

		for (v_it = mesh.vertices_begin(); v_it != v_end; ++v_it)
			if (!mesh.is_boundary(*v_it))
				mesh.set_point(*v_it, mesh.property(cogs, *v_it));*/
	}
	
	double calcAngle(OMT::Point pnt1, OMT::Point pnt2){
		return (std::acos(dot(pnt1, pnt2) / (mag(pnt1)*mag(pnt2)))*180)/ 3.1415926535;
	}

	float dot(OMT::Point a, OMT::Point b)  //calculates dot product of a and b
	{
		return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
	}

	float mag(OMT::Point a)  //calculates magnitude of a
	{
		return std::sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	}

};
}

