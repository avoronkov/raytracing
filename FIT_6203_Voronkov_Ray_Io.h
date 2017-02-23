#pragma once

#include "FIT_6203_Voronkov_Ray_Scene.h"
#include "FIT_6203_Voronkov_Ray_Box.h"
#include "FIT_6203_Voronkov_Ray_Polygon.h"
#include "FIT_6203_Voronkov_Ray_Quadric.h"
#include "FIT_6203_Voronkov_Ray_QuadroBox.h"
#include "FIT_6203_Voronkov_Ray_Sphere.h"
#include "FIT_6203_Voronkov_Ray_RenderSet.h"
#include "FIT_6203_Voronkov_Ray_Matrix.h"

class CFIT_6203_Voronkov_Ray_Io
{
private:
	static bool uncommentString(CString * str);
	static bool readUString(CArchive & ar, CString * str);

	static bool readSphere(CArchive *m_arc_in, Sphere * sph);
	static bool readBox(CArchive *m_arc_in, Box * box);
	static bool readPolygon(CArchive *m_arc_in, Polygone * polygon);
	static bool readQuadric(CArchive *m_arc_in, Quadric * quadric);
	static bool readQuadroBox(CArchive *m_arc_in, QuadroBox * quadro_box);
	static bool readMatrix3(CArchive *m_arc_in, Matrix * matrix);
	static bool writeMatrix3(CArchive *out, const Matrix & matrix);
	static bool readMatrix4(CArchive *m_arc_in, Matrix * matrix);
	static bool writeMatrix4(CArchive *out, const Matrix & matrix);

	static bool readOptics(CArchive *in, Primitive * p);
public:
	static bool loadScene(CArchive * in, Scene * scene);
	static bool loadRenderSet(CArchive * in, RenderSet * r_set);
	static bool saveRenderSet(CArchive * out, const RenderSet & r_set);
	
	static bool saveBmp(CArchive * m_arc, const CDC * pDC, const CSize & size, int offset);
	static void write4bytes(int n, unsigned char *out);
	static void write2bytes(int n, unsigned char *out);
	static int CFIT_6203_Voronkov_Ray_Io::getRasterRowLength(int cols);
	static int CFIT_6203_Voronkov_Ray_Io::getImageSize(const CSize & img_size);
};

typedef CFIT_6203_Voronkov_Ray_Io Io;
