#include "GUA_OM.h"
//#include "TextureApp.h"
#define PI 3.14159265

namespace OMT
{
	/*======================================================================*/
	Model::Model()
	{
		request_vertex_status();
		request_edge_status();
		request_face_status();
	}
	Model::~Model()
	{
		release_vertex_status();
		release_edge_status();
		release_face_status();
	}
}
/*======================================================================*/
namespace OMP
{
	Model::Model()
	{
		Mesh.request_vertex_status();
		Mesh.request_edge_status();
		Mesh.request_face_status();
	}
	Model::~Model()
	{
		Mesh.release_vertex_status();
		Mesh.release_edge_status();
		Mesh.release_face_status();
	}
	/*======================================================================*/
	bool Model::ReadFile(std::string _fileName)
	{
		bool isRead = false;
		OpenMesh::IO::Options opt;
		if (OpenMesh::IO::read_mesh(Mesh, _fileName, opt))
		{
			//read mesh from filename OK!
			isRead = true;
		}
		if (isRead)
		{
			// If the file did not provide vertex normals and mesh has vertex normal ,then calculate them
			if (!opt.check(OpenMesh::IO::Options::VertexNormal) && Mesh.has_vertex_normals())
			{
				Mesh.update_normals();
			}
		}
		return isRead;
	}
	bool Model::SaveFile(std::string _fileName)
	{
		bool isSave = false;
		OpenMesh::IO::Options opt;
		if (OpenMesh::IO::write_mesh(Mesh, _fileName, opt))
		{
			//read mesh from filename OK!
			isSave = true;
		}
		return isSave;
	}
	/*======================================================================*/
	void Model::Render_solid()
	{
		FIter f_it;
		FVIter	fv_it;
		glPushAttrib(GL_LIGHTING_BIT);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glEnable(GL_DEPTH_TEST);
		glPolygonOffset(2.0, 2.0);
		glBegin(GL_POLYGON);
		//glColor4f(1.0, 0.5, 1.0, 0.5);
		for (f_it = Mesh.faces_begin(); f_it != Mesh.faces_end(); ++f_it)
		{
			for (fv_it = Mesh.fv_iter(f_it); fv_it; ++fv_it)
			{
				glNormal3dv(Mesh.normal(fv_it.handle()).data());
				glVertex3dv(Mesh.point(fv_it.handle()).data());
			}
		}
		glEnd();
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
	void Model::Render_wireframe()
	{
		MyMesh::HalfedgeHandle _hedge;
		EIter e_it = Mesh.edges_begin();

		glDisable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
		glColor3f(0.0, 0.0, 0.0);
		glLineWidth(1);
		glBegin(GL_LINES);
		for (e_it = Mesh.edges_begin(); e_it != Mesh.edges_end(); ++e_it)
		{
			_hedge = Mesh.halfedge_handle(e_it.handle(), 1);
			std::cout << Mesh.point(Mesh.from_vertex_handle(_hedge)).data() << " " << Mesh.point(Mesh.to_vertex_handle(_hedge)).data() << std::endl;
			glVertex3dv(Mesh.point(Mesh.from_vertex_handle(_hedge)).data());
			glVertex3dv(Mesh.point(Mesh.to_vertex_handle(_hedge)).data());
		}
		glEnd();
		glEnable(GL_LIGHTING);
	}
	/*======================================================================*/
	void Model::RenderSpecifiedPoint()
	{
		glPushAttrib(GL_LIGHTING_BIT);
		glDisable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
		glPointSize(5.0f);
		glBegin(GL_POINTS);
		vector<sp_p>::iterator p_itr = sp_p_list.begin();
		for (p_itr; p_itr != sp_p_list.end(); ++p_itr)
		{
			glColor3f(p_itr->r, p_itr->g, p_itr->b);
			glVertex3dv(p_itr->pt.data());
		}
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
	void Model::RenderSpecifiedVertex()
	{
		glPushAttrib(GL_LIGHTING_BIT);
		glDisable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
		glPointSize(5.0f);
		glBegin(GL_POINTS);
		vector< sp_v >::iterator v_itr = sp_v_list.begin();
		for (v_itr; v_itr != sp_v_list.end(); ++v_itr)
		{
			glColor3f(v_itr->r, v_itr->g, v_itr->b);
			glVertex3dv(Mesh.point(v_itr->vh).data());
		}
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_POLYGON_OFFSET_FILL);
	}
	void Model::RenderSpecifiedFace()
	{
		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPushAttrib(GL_LIGHTING_BIT);
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(0.5, 1.0);
		glDisable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
		glBegin(GL_QUADS);
		FVIter fv_itr;
		vector< sp_f >::iterator f_itr;
		for (f_itr = sp_f_list.begin(); f_itr != sp_f_list.end(); ++f_itr)
		{
			glColor3f(f_itr->r, f_itr->g, f_itr->b);
			for (fv_itr = Mesh.fv_iter(f_itr->fh); fv_itr; ++fv_itr)
			{
				glNormal3dv(Mesh.normal(fv_itr.handle()).data());
				glVertex3dv(Mesh.point(fv_itr.handle()).data());
			}
		}
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_POLYGON_OFFSET_FILL);
		glPolygonMode(GL_FRONT, GL_FILL);
		glEnable(GL_CULL_FACE);
	}

	/*======================================================================*/
	void Model::add_sp_p(Point   _p, float _r, float _g, float _b)
	{
		sp_p input_data;
		input_data.pt = _p;
		input_data.r = _r;
		input_data.g = _g;
		input_data.b = _b;
		sp_p_list.push_back(input_data);
	}
	void Model::add_sp_v(VHandle _v, float _r, float _g, float _b)
	{
		sp_v input_data;
		input_data.vh = _v;
		input_data.r = _r;
		input_data.g = _g;
		input_data.b = _b;
		sp_v_list.push_back(input_data);
	}
	void Model::add_sp_f(FHandle _f, float _r, float _g, float _b)
	{
		sp_f input_data;
		input_data.fh = _f;
		input_data.r = _r;
		input_data.g = _g;
		input_data.b = _b;
		sp_f_list.push_back(input_data);
	}
	void Model::clear_sp_p()
	{
		sp_p_list.clear();
	}
	void Model::clear_sp_v()
	{
		sp_v_list.clear();
	}
	void Model::clear_sp_f()
	{
		sp_f_list.clear();
	}
	/*======================================================================*/
	VHandle Model::addVertex(Point _p)
	{
		int find_result = findVertex(_p);
		if (find_result != -1)
		{
			return Mesh.vertex_handle(find_result);
		}
		else
		{
			return Mesh.add_vertex(_p);
		}
	}
	FHandle Model::addFace(VHandle _v0, VHandle _v1, VHandle _v2, VHandle _v3)
	{
		vector<VHandle> face_vhandles;

		face_vhandles.clear();
		face_vhandles.push_back(_v0);
		face_vhandles.push_back(_v1);
		face_vhandles.push_back(_v2);
		face_vhandles.push_back(_v3);
		return Mesh.add_face(face_vhandles);
	}
	void Model::deleteFace(FHandle _f)
	{
		Mesh.delete_face(_f);
		Mesh.garbage_collection();
	}
	void Model::deleteFace(VHandle _v0, VHandle _v1, VHandle _v2, VHandle _v3)
	{
		/*
		v1				v0
		*<--------------*
		|				|
		|				|
		|				|
		|		f		|
		|				|
		|				|
		|				|
		* --------------*
		v2				v3
		*/

		HEHandle v0v1 = Mesh.find_halfedge(_v0, _v1);
		if (v0v1.is_valid())
		{
			FHandle fh = Mesh.face_handle(v0v1);
			if (fh.is_valid())
			{
				Mesh.delete_face(fh);
				Mesh.garbage_collection();
			}
		}
	}
	/*======================================================================*/
	bool Model::IsVertexVertex(VHandle _vj, VHandle _vi)
	{
		for (VVIter vvit = Mesh.vv_iter(_vi); vvit; ++vvit)
			if (vvit.handle() == _vj)
				return true;
		return false;
	}
	/*======================================================================*/
	int Model::quad_subdivision1(int _face_id)
	{
		/*----------------------------------------------------------------------*/
		//這段是為了解決index問題
		VHandle vq, vw, vt, vr;
		vq = addVertex(Point(0, 0, 100));
		vw = addVertex(Point(1, 0, 100));
		vt = addVertex(Point(1, 1, 100));
		vr = addVertex(Point(0, 1, 100));
		addFace(vq, vw, vt, vr);
		/*----------------------------------------------------------------------*/
		/*收集需要subdivision的face*/
		//初始table
		bool *table = new bool[Mesh.n_faces()];
		for (unsigned i = 0; i < Mesh.n_faces(); i++)
		{
			table[i] = false;
		}

		vector< FHandle > candidate_faces, last_found_face;
		last_found_face.push_back(Mesh.face_handle(_face_id));
		table[_face_id] = true;

		while (last_found_face.size() != 0)
		{
			vector< FHandle > new_found_faces;
			for (vector< FHandle >::iterator crnt_f = last_found_face.begin(); crnt_f != last_found_face.end(); ++crnt_f)
			{
				for (FFIter ff_itr = Mesh.ff_iter(*crnt_f); ff_itr; ++ff_itr)
				{
					if (table[ff_itr.handle().idx()] != true)
					{
						new_found_faces.push_back(ff_itr.handle());
						table[ff_itr.handle().idx()] = true;
					}
				}
			}
			for (vector< FHandle >::iterator f_itr = last_found_face.begin(); f_itr != last_found_face.end(); ++f_itr)
			{
				candidate_faces.push_back(*f_itr);
			}
			last_found_face.assign(new_found_faces.begin(), new_found_faces.end());
		}
		delete table;
		/*----------------------------------------------------------------------*/
		/*對candidate faces做subdivision*/
		/*
		v0		vd		v3
		*-------*-------*
		|		|		|
		|		|		|
		|	  ve|		|
		va*-------*-------*vc
		|		|		|
		|		|		|
		|		|		|
		*-------*-------*
		v1		vb		v2
		*/
		for (vector< FHandle >::iterator face_itr = candidate_faces.begin(); face_itr != candidate_faces.end(); ++face_itr)
		{
			VHandle v[4], va, vb, vc, vd, ve;
			FVIter fv_itr = Mesh.fv_iter(*face_itr);
			for (int i = 0; fv_itr; ++fv_itr)
			{
				v[i++] = fv_itr.handle();
			}

			deleteFace(v[0], v[1], v[2], v[3]);
			va = addVertex((Mesh.point(v[0]) + Mesh.point(v[1])) / 2);
			vb = addVertex((Mesh.point(v[1]) + Mesh.point(v[2])) / 2);
			vc = addVertex((Mesh.point(v[2]) + Mesh.point(v[3])) / 2);
			vd = addVertex((Mesh.point(v[3]) + Mesh.point(v[0])) / 2);
			ve = addVertex((Mesh.point(v[0]) + Mesh.point(v[1]) + Mesh.point(v[2]) + Mesh.point(v[3])) / 4);
			addFace(vd, v[0], va, ve);
			addFace(va, v[1], vb, ve);
			addFace(vb, v[2], vc, ve);
			addFace(vc, v[3], vd, ve);
		}
		/*----------------------------------------------------------------------*/
		deleteFace(vq, vw, vt, vr);//這行只是為了解決index問題
								   /*----------------------------------------------------------------------*/
		return 0;
	}
	int Model::quad_subdivision2(int _face_id)
	{
		/*----------------------------------------------------------------------*/
		//這段是為了解決index問題
		VHandle vq, vw, vt, vr;
		vq = addVertex(Point(0, 0, 100));
		vw = addVertex(Point(1, 0, 100));
		vt = addVertex(Point(1, 1, 100));
		vr = addVertex(Point(0, 1, 100));
		addFace(vq, vw, vt, vr);
		/*----------------------------------------------------------------------*/
		/*收集需要subdivision的face*/
		//初始table
		bool *table = new bool[Mesh.n_faces()];
		for (unsigned i = 0; i < Mesh.n_faces(); i++)
		{
			table[i] = false;
		}

		vector< FHandle > candidate_faces, last_found_face;
		last_found_face.push_back(Mesh.face_handle(_face_id));
		table[_face_id] = true;

		while (last_found_face.size() != 0)
		{
			vector< FHandle > new_found_faces;
			for (vector< FHandle >::iterator crnt_f = last_found_face.begin(); crnt_f != last_found_face.end(); ++crnt_f)
			{
				for (FFIter ff_itr = Mesh.ff_iter(*crnt_f); ff_itr; ++ff_itr)
				{
					if (table[ff_itr.handle().idx()] != true)
					{
						new_found_faces.push_back(ff_itr.handle());
						table[ff_itr.handle().idx()] = true;
					}
				}
			}
			for (vector< FHandle >::iterator f_itr = last_found_face.begin(); f_itr != last_found_face.end(); ++f_itr)
			{
				candidate_faces.push_back(*f_itr);
			}
			last_found_face.assign(new_found_faces.begin(), new_found_faces.end());
		}
		delete table;
		/*----------------------------------------------------------------------*/
		/*對candidate faces做subdivision*/
		/*
		v0		vh		vg		v3
		*-------*-------*-------*
		|		|		|		|
		|		|		|		|
		|	  vi|	  vl|		|
		va *-------*-------*-------*vf
		|		|		|		|
		|		|		|		|
		|	  vj|	  vk|		|
		vb *-------*-------*-------*ve
		|		|		|		|
		|		|		|		|
		|		|		|		|
		*-------*-------*-------*
		v1		vc		vd		v2
		*/
		for (vector< FHandle >::iterator face_itr = candidate_faces.begin(); face_itr != candidate_faces.end(); ++face_itr)
		{
			VHandle v[4], va, vb, vc, vd, ve, vf, vg, vh, vi, vj, vk, vl;
			FVIter fv_itr = Mesh.fv_iter(*face_itr);
			for (int i = 0; fv_itr; ++fv_itr)
			{
				v[i++] = fv_itr.handle();
			}

			deleteFace(v[0], v[1], v[2], v[3]);
			va = addVertex((Mesh.point(v[0]) * 2 + Mesh.point(v[1])) / 3);
			vb = addVertex((Mesh.point(v[0]) + Mesh.point(v[1]) * 2) / 3);
			vc = addVertex((Mesh.point(v[1]) * 2 + Mesh.point(v[2])) / 3);
			vd = addVertex((Mesh.point(v[1]) + Mesh.point(v[2]) * 2) / 3);
			ve = addVertex((Mesh.point(v[2]) * 2 + Mesh.point(v[3])) / 3);
			vf = addVertex((Mesh.point(v[2]) + Mesh.point(v[3]) * 2) / 3);
			vg = addVertex((Mesh.point(v[3]) * 2 + Mesh.point(v[0])) / 3);
			vh = addVertex((Mesh.point(v[3]) + Mesh.point(v[0]) * 2) / 3);

			vi = addVertex((Mesh.point(vh) * 2 + Mesh.point(vc)) / 3);
			vj = addVertex((Mesh.point(vh) + Mesh.point(vc) * 2) / 3);
			vk = addVertex((Mesh.point(vd) * 2 + Mesh.point(vg)) / 3);
			vl = addVertex((Mesh.point(vd) + Mesh.point(vg) * 2) / 3);
			addFace(v[0], va, vi, vh);
			addFace(va, vb, vj, vi);
			addFace(vb, v[1], vc, vj);
			addFace(vc, vd, vk, vj);
			addFace(vd, v[2], ve, vk);
			addFace(ve, vf, vl, vk);
			addFace(vf, v[3], vg, vl);
			addFace(vg, vh, vi, vl);
			addFace(vi, vj, vk, vl);
		}
		/*----------------------------------------------------------------------*/
		deleteFace(vq, vw, vt, vr);//這行只是為了解決index問題
								   /*----------------------------------------------------------------------*/
		return 0;
	}
	/*======================================================================*/
	int Model::findVertex(Point _p)
	{
		for (VIter v_itr = Mesh.vertices_begin(); v_itr != Mesh.vertices_end(); ++v_itr)
			if (Mesh.point(v_itr) == _p)
				return v_itr.handle().idx();
		return -1;
	}
	/*======================================================================*/
};
/*======================================================================*/
void Tri_Mesh::Render_Solid()
{
	FIter f_it;
	FVIter	fv_it;
	//glPushAttrib(GL_LIGHTING_BIT);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glEnable(GL_LIGHTING);
	glPolygonOffset(2.0, 2.0);
	glBegin(GL_TRIANGLES);
	glColor4f(0.81, 0.74, 0.33, 0.3);
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it)
	{
		for (fv_it = fv_iter(f_it); fv_it; ++fv_it)
		{
			glNormal3dv(normal(fv_it.handle()).data());
			glVertex3dv(point(fv_it.handle()).data());
		}
	}
	glEnd();

	glDisable(GL_POLYGON_OFFSET_FILL);
}

void Tri_Mesh::initTexture()
{
	//E:\基礎電腦圖學\Q6\project\OBJTextureApplier-Texturetest\OBJTextureApplier-Texturetest\Release\Textures\background.jpg

	plane->add_property(cogs);
	plane->add_property(planetomesh);
	add_property(usingtext);
	add_property(cogs);
	add_property(confirmed);
	addTexture("Z:/Documents/graphics2017/Release/Textures/background.jpg");
	//currenttexture = textures[0];
	for (OMT::FIter f_it = faces_begin(); f_it != faces_end(); ++f_it) {
		property(usingtext, f_it.handle()) = "NULL";
		property(confirmed, f_it.handle()) = false;
	}
}


void Tri_Mesh::refreshPlane() {
	delete plane;
	plane = new Tri_Mesh;
	plane->add_property(cogs);
	plane->add_property(planetomesh);
	outerpnts.clear();
	innerpnts.clear();
	weights.clear();
}
void Tri_Mesh::addTexture(std::string filename)
{
	char *f = new char[filename.length() + 1];
	strcpy(f, filename.c_str());
	textures.push_back(f);
	currenttexture = textures[textures.size() - 1];
	//currenttexture = TextureApp::GenTexture(f);
	//currenttexture = textures[textures.size() - 1];
}
	


void Tri_Mesh::RenderTextureOn()
{

	glDisable(GL_LIGHTING);
	glPushAttrib(GL_LIGHTING_BIT);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glEnable(GL_DEPTH_TEST);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glPolygonOffset(2.0, 2.0);
	
	//std::cout << "mouse in GUA_OM:" << clickPoint[0] << " " << clickPoint[1] << " " << clickPoint[2] << std::endl;
	for (OMT::FIter f_it = faces_begin(); f_it != faces_end(); ++f_it)
	{
		OMT::Point p[3];
		OMT::Point t[3];
		int i = 0;
		Render_SolidWireframe();
		if (property(usingtext, f_it.handle()) != "NULL") {
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			//glBindTexture(GL_TEXTURE_2D, property(usingtext, f_it.handle()));
			GLuint _textureID = TextureApp::GenTexture((char *)property(usingtext, f_it.handle()).c_str());
			glBindTexture(GL_TEXTURE_2D, _textureID);
			glBegin(GL_TRIANGLES);
			for (OMT::FVIter fv_it = fv_iter(f_it); fv_it; ++fv_it)
			{
				//glNormal3dv(normal(fv_it.handle()));
				
				for (int k = 0; k < property(cogs, fv_it.handle()).size(); k++) {			
					if (property(cogs, fv_it.handle())[k].texture == property(usingtext, f_it.handle())) {
						for (int j = 0; j < 3; j++) {
							t[i][j] = property(cogs, fv_it.handle())[k].pnt[j];
							p[i][j] = point(fv_it.handle()).data()[j];
						}
					}
				}
				//glVertex3dv(point(fv_it.handle()).data());
				//std::cout << i << ": " << t[i][0] << " " << t[i][1] << " " << t[i][2] << std::endl;
				i++;
				//std::cout << p[0] << std::endl;
				//std::cout << point(fv_it.handle()).data()[0] << " " << point(fv_it.handle()).data()[1] << " " << point(fv_it.handle()).data()[2] << " " << std::endl;
			}
			std::cout << std::endl;
			glTexCoord2d(1 - t[0][0], t[0][1]); glVertex3f(p[0][0] + 0.0001, p[0][1] + 0.0001, p[0][2] + 0.0001);
			glTexCoord2d(1 - t[1][0], t[1][1]); glVertex3f(p[1][0] + 0.0001, p[1][1] + 0.0001, p[1][2] + 0.0001);
			glTexCoord2d(1 - t[2][0], t[2][1]); glVertex3f(p[2][0] + 0.0001, p[2][1] + 0.0001, p[2][2] + 0.0001);
			glEnd();
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		}
		//else {
		//	glColor4f(1.0, 0.96, 0.49, 1.0);
		//	glBegin(GL_TRIANGLES);
		//	for (OMT::FVIter fv_it = fv_iter(f_it); fv_it; ++fv_it)
		//	{
		//		//glNormal3dv(normal(fv_it.handle()));
		//		for (int j = 0; j < 3; j++) {
		//			p[i][j] = point(fv_it.handle()).data()[j];
		//		}
		//		//glVertex3dv(point(fv_it.handle()).data());

		//		i++;
		//		//std::cout << p[0] << std::endl;
		//		//std::cout << point(fv_it.handle()).data()[0] << " " << point(fv_it.handle()).data()[1] << " " << point(fv_it.handle()).data()[2] << " " << std::endl;
		//	}
		//	glVertex3f(p[0][0], p[0][1], p[0][2]);
		//	glVertex3f(p[1][0], p[1][1], p[1][2]);
		//	glVertex3f(p[2][0], p[2][1], p[2][2]);
		//	glEnd();
		//}

	}
	//std::cout << "------------" << std::endl;
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);
	glLineWidth(1.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	for (OMT::EIter e_it = edges_begin(); e_it != edges_end(); ++e_it)
	{
		OMT::HEHandle _hedge = halfedge_handle(e_it.handle(), 1);

		OMT::Point curVertex = point(from_vertex_handle(_hedge));
		glVertex3dv(curVertex.data());

		curVertex = point(to_vertex_handle(_hedge));
		glVertex3dv(curVertex.data());
	}
	glEnd();
	glPopAttrib();

	
	
}


void Tri_Mesh::setPoint(GLfloat p0, GLfloat p1, GLfloat p2) {
	clickPoint[0] = p0;
	clickPoint[1] = p1;
	clickPoint[2] = p2;

	//std::cout << "mouse in GUA_OM:" << clickPoint[0] << " " << clickPoint[1] << " " << clickPoint[2] << std::endl;
}

void Tri_Mesh::Render_SolidWireframe()
{
	FIter f_it;
	FVIter	fv_it;

	/*glPointSize(8.0);
	glBegin(GL_POINTS);
	glColor4f(1.0, 0.0, 0.0, 1.0);
	glVertex3dv(point(vertex_handle(0)));
	glEnd();*/
	glDisable(GL_LIGHTING);
	glPushAttrib(GL_LIGHTING_BIT);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glEnable(GL_DEPTH_TEST);
	glPolygonOffset(2.0, 2.0);
	glBegin(GL_TRIANGLES);
	glColor4f(1.0, 0.96, 0.49, 1.0);
	//std::cout << "mouse in GUA_OM:" << clickPoint[0] << " " << clickPoint[1] << " " << clickPoint[2] << std::endl;
	for (f_it = faces_begin(); f_it != faces_end(); ++f_it)
	{
		Point p[3];
		int i = 0;
		for (fv_it = fv_iter(f_it); fv_it; ++fv_it)
		{

			//glNormal3dv(normal(fv_it.handle()));
			for (int j = 0; j < 3; j++) {
				p[i][j] = point(fv_it.handle()).data()[j];
			}
			//glVertex3dv(point(fv_it.handle()).data());
			i++;
			//std::cout << p[0] << std::endl;
			//std::cout << point(fv_it.handle()).data()[0] << " " << point(fv_it.handle()).data()[1] << " " << point(fv_it.handle()).data()[2] << " " << std::endl;
		}
		glVertex3f(p[0][0], p[0][1], p[0][2]);
		glVertex3f(p[1][0], p[1][1], p[1][2]);
		glVertex3f(p[2][0], p[2][1], p[2][2]);

	}
	//std::cout << "------------" << std::endl;
	glEnd();



	//glDisable(GL_POLYGON_OFFSET_FILL);


	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);
	glLineWidth(1.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	for (OMT::EIter e_it = edges_begin(); e_it != edges_end(); ++e_it)
	{
		OMT::HEHandle _hedge = halfedge_handle(e_it.handle(), 1);

		OMT::Point curVertex = point(from_vertex_handle(_hedge));
		glVertex3dv(curVertex.data());

		curVertex = point(to_vertex_handle(_hedge));
		glVertex3dv(curVertex.data());
	}
	glEnd();
	glPopAttrib();
}

void Tri_Mesh::Render_Wireframe()
{
	//glPushAttrib(GL_LIGHTING_BIT);	
	glDisable(GL_LIGHTING);
	glLineWidth(1.0);

	glColor3f(0.0, 0.0, 0.0);

	glBegin(GL_LINES);
	for (OMT::EIter e_it = edges_begin(); e_it != edges_end(); ++e_it)
	{
		OMT::HEHandle _hedge = halfedge_handle(e_it.handle(), 1);

		OMT::Point curVertex = point(from_vertex_handle(_hedge));
		glVertex3dv(curVertex.data());

		curVertex = point(to_vertex_handle(_hedge));
		glVertex3dv(curVertex.data());
	}
	glEnd();

}

void Tri_Mesh::Render_Point()
{
	glPointSize(8.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (OMT::VIter v_it = vertices_begin(); v_it != vertices_end(); ++v_it)
	{
		glVertex3dv(point(v_it).data());
	}
	glEnd();
}


void Tri_Mesh::setOuterPoints() {
		outerpnts.clear();
		innerpnts.clear();
		OMT::VertexHandle heh, heh_init;
		std::cout << plane->faces_end() << std::endl;
		for (OMT::VIter v_it = plane->vertices_begin(); v_it != plane->vertices_end(); ++v_it) {
			std::cout << "start: " << plane->point(v_it.handle()).data()[0] << " " << plane->point(v_it.handle()).data()[1] << " " << plane->point(v_it.handle()).data()[2] << std::endl;
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
		// We n do this as often as we want:
		while (heh != heh_init) {
			for (OMT::VOHEIter voh_it = plane->voh_iter(heh); voh_it; ++voh_it) {
				// Iterate over all outgoing halfedges...
				bool exists = false;
				for (int i = 0; i < outerpnts.size(); i++) {
					if (plane->to_vertex_handle(voh_it) == outerpnts[i]) {
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

void Tri_Mesh::setWeight() {

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
						if (plane->point(vvitvvit.handle()) == plane->point(vvcomp.handle()) && firstpntset) {
							secondpnt = vvitvvit.handle();
							break;
						}
						if (plane->point(vvitvvit.handle()) == plane->point(vvcomp.handle())) {
							firstpnt = vvitvvit.handle();
							firstpntset = true;
						}
					}
				}
				OMT::Vec3d firstvct = plane->point(firstpnt) - plane->point(innerpnts[i]);
				OMT::Vec3d secondvct = plane->point(secondpnt) - plane->point(innerpnts[i]);
				OMT::Vec3d vvitvct = plane->point(vvit.handle()) - plane->point(innerpnts[i]);
				double weight = (tan((calcAngle(firstvct, vvitvct) / 2) * PI / 180.0) + tan((calcAngle(vvitvct, secondvct) / 2) * PI / 180.0)) / vvitvct.length();
				circleweight.push_back(weight);
			}
			weights.push_back(circleweight);
		}
	}

void Tri_Mesh::Parameterize() {
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
		int count = 0;
		for (OMT::FIter f_it = plane->faces_begin(); f_it != plane->faces_end(); ++f_it) {
			count++;
		}
		std::cout << "count: " << count << std::endl;
		
			for (int i = 0; i < outerpnts.size(); i++)
			{
				bool existsinplane = false;
				bool existsinmesh = false;
				int j;
				int mj;
				//add into plane
				for ( j = 0; j < plane->property(cogs, outerpnts[i]).size(); j++) {
					if (plane->property(cogs, outerpnts[i])[j].texture == currenttexture) {
						existsinplane = true;
						break;
					}
				}
				for (mj = 0; mj < property(cogs, plane->property(planetomesh, outerpnts[i])).size(); mj++) {
					if (property(cogs, plane->property(planetomesh, outerpnts[i]))[mj].texture == currenttexture) {
						existsinmesh = true;
						break;
					}
				}
				if (existsinplane) {
					if (oneline[i] <= 1) 
						plane->property(cogs, outerpnts[i])[j].pnt = OMT::Point(oneline[i], 0, 0);
					else if (oneline[i] <= 2) 
						plane->property(cogs, outerpnts[i])[j].pnt = OMT::Point(1, oneline[i] - 1, 0);		
					else if (oneline[i] <= 3) 
						plane->property(cogs, outerpnts[i])[j].pnt = OMT::Point(1 - (oneline[i] - 2), 1, 0);
					else if (oneline[i] <= 4) 
						plane->property(cogs, outerpnts[i])[j].pnt = OMT::Point(0, 1 - (oneline[i] - 3), 0);
				}
				else {
					texturepoint temp;
					temp.texture = currenttexture;
					if (oneline[i] <= 1) {
						temp.pnt = OMT::Point(oneline[i], 0, 0);
						plane->property(cogs, outerpnts[i]).push_back(temp);
					}
					else if (oneline[i] <= 2) {
						temp.pnt = OMT::Point(1, oneline[i] - 1, 0);
						plane->property(cogs, outerpnts[i]).push_back(temp);
					}
					else if (oneline[i] <= 3) {
						temp.pnt = OMT::Point(1 - (oneline[i] - 2), 1, 0);
						plane->property(cogs, outerpnts[i]).push_back(temp);
					}
					else if (oneline[i] <= 4) {
						temp.pnt = OMT::Point(0, 1 - (oneline[i] - 3), 0);
						plane->property(cogs, outerpnts[i]).push_back(temp);
					}
				}

				if (existsinmesh) {
					if (oneline[i] <= 1) 
						property(cogs, plane->property(planetomesh, outerpnts[i]))[mj].pnt = OMT::Point(oneline[i], 0, 0);
					else if (oneline[i] <= 2) 
						property(cogs, plane->property(planetomesh, outerpnts[i]))[mj].pnt = OMT::Point(1, oneline[i] - 1, 0);
					else if (oneline[i] <= 3) 
						property(cogs, plane->property(planetomesh, outerpnts[i]))[mj].pnt = OMT::Point(1 - (oneline[i] - 2), 1, 0);
					else if (oneline[i] <= 4) 
						property(cogs, plane->property(planetomesh, outerpnts[i]))[mj].pnt = OMT::Point(0, 1 - (oneline[i] - 3), 0);
				}
				else {
					texturepoint temp;
					temp.texture = currenttexture;
					if (oneline[i] <= 1) {
						temp.pnt = OMT::Point(oneline[i], 0, 0);
						property(cogs, plane->property(planetomesh, outerpnts[i])).push_back(temp);
					}
					else if (oneline[i] <= 2) {
						temp.pnt = OMT::Point(1, oneline[i] - 1, 0);
						property(cogs, plane->property(planetomesh, outerpnts[i])).push_back(temp);
					}
					else if (oneline[i] <= 3) {
						temp.pnt = OMT::Point(1 - (oneline[i] - 2), 1, 0);
						property(cogs, plane->property(planetomesh, outerpnts[i])).push_back(temp);
					}
					else if (oneline[i] <= 4) {
						temp.pnt = OMT::Point(0, 1 - (oneline[i] - 3), 0);
						property(cogs, plane->property(planetomesh, outerpnts[i])).push_back(temp);
					}
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
							outerweightx += weights[i][k] * plane->property(cogs, outerpnts[j])[plane->property(cogs, outerpnts[j]).size() - 1].pnt[0];
							outerweighty += weights[i][k] * plane->property(cogs, outerpnts[j])[plane->property(cogs, outerpnts[j]).size() - 1].pnt[1];
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

			if (count == 1) {
				for (int i = 0; i < innerpnts.size(); i++) {
					texturepoint temp;
					temp.pnt = OMT::Point(X[0][i], X[1][i], 0);
					temp.texture = currenttexture;
					plane->property(cogs, innerpnts[i]).push_back(temp);
					property(cogs, plane->property(planetomesh, innerpnts[i])).push_back(temp);
				}
			}
			else {
				for (int i = 0; i < innerpnts.size(); i++) {
					plane->property(cogs, innerpnts[i])[plane->property(cogs, innerpnts[i]).size() - 1].pnt = OMT::Point(X[0][i], X[1][i], 0);
					property(cogs, plane->property(planetomesh, innerpnts[i]))[property(cogs, plane->property(planetomesh, innerpnts[i])).size() - 1].pnt = OMT::Point(X[0][i], X[1][i], 0);
				}
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
	
void Tri_Mesh::setPlaneFacetoMeshFace(OMT::FHandle face, OMT::FHandle planeface) {
	for (OMT::FVIter plane_fv_it = plane->fv_iter(planeface); plane_fv_it; ++plane_fv_it) {
		for (OMT::FVIter fv_it = fv_iter(face); fv_it; ++fv_it) {
			if (plane->point(plane_fv_it.handle()).data()[0] == point(fv_it.handle()).data()[0] &&
				plane->point(plane_fv_it.handle()).data()[1] == point(fv_it.handle()).data()[1] && 
				plane->point(plane_fv_it.handle()).data()[2] == point(fv_it.handle()).data()[2]) {
				plane->property(planetomesh, plane_fv_it.handle()) = fv_it.handle();
				break;
			}
		}
	}
	property(usingtext, face) = currenttexture;
	
}

double Tri_Mesh::calcAngle(OMT::Point pnt1, OMT::Point pnt2) {
	return (std::acos(dot(pnt1, pnt2) / (mag(pnt1)*mag(pnt2))) * 180) / 3.1415926535;
}

float Tri_Mesh::dot(OMT::Point a, OMT::Point b)  //calculates dot product of a and b
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

float Tri_Mesh::mag(OMT::Point a)  //calculates magnitude of a
{
	return std::sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}



bool ReadFile(std::string _fileName, Tri_Mesh *_mesh)
{
	bool isRead = false;
	OpenMesh::IO::Options opt;
	if (OpenMesh::IO::read_mesh(*_mesh, _fileName, opt))
	{
		//read mesh from filename OK!
		isRead = true;
	}
	if (isRead)
	{
		// If the file did not provide vertex normals and mesh has vertex normal ,then calculate them
		if (!opt.check(OpenMesh::IO::Options::VertexNormal) && _mesh->has_vertex_normals())
		{
			_mesh->update_normals();
		}
	}
	return isRead;
}

bool SaveFile(std::string _fileName, Tri_Mesh *_mesh)
{
	bool isSave = false;
	if (OpenMesh::IO::write_mesh(*_mesh, _fileName))
	{
		isSave = true;
	}
	return isSave;
}




GLuint TextureApp::GenTexture(char* filepath)
{
	char *format = filepath;
	unsigned int textureID = 0;
	while (*format != 0) format++;
	while (format != filepath && *format != '.') format--;



	IplImage *img = NULL;
	img = cvLoadImage(filepath, 1);

	if (img != NULL)
	{
		cvFlip(img);
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, img->width, img->height, GL_BGR_EXT, GL_UNSIGNED_BYTE, img->imageData);
	}
	else printf("cannot find %s \n", filepath);


	return textureID;
}