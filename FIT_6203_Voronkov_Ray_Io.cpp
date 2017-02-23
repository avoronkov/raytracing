#include "stdafx.h"
#include "FIT_6203_Voronkov_Ray_Io.h"

bool CFIT_6203_Voronkov_Ray_Io::uncommentString(CString * str)
{
	int com_index;
	if ((com_index = str->Find("//")) >= 0)
	{
		(*str) = str->Left(com_index);
		if (str->GetLength() == 0){
			return true;
		}
	}
	(*str) = str->Trim();

	if (str->GetLength() == 0){
		return true;
	}
	return true;
}
bool CFIT_6203_Voronkov_Ray_Io::readUString(CArchive & ar, CString * str)
{
	while (true)
	{
		if (! ar.ReadString(*str)) AfxThrowArchiveException(CArchiveException::endOfFile);
		if (uncommentString(str) == false){
			AfxThrowArchiveException(CArchiveException::genericException);
		}
		if (str->GetLength() > 0) return true;
	}
}

bool CFIT_6203_Voronkov_Ray_Io::readSphere(CArchive *m_arc_in, Sphere * sph)
{
	CString buf;
	double x0, y0, z0;
	readUString(*m_arc_in, &buf);
	if ( sscanf_s(buf.GetBuffer(), "%lf %lf %lf", &x0, &y0, &z0) != 3){
		AfxThrowArchiveException(CArchiveException::genericException);
	}
	double r;
	readUString(*m_arc_in, &buf);
	if ( sscanf_s(buf.GetBuffer(), "%lf", &r) != 1){
		AfxThrowArchiveException(CArchiveException::genericException);
	}
	sph->setCenter(x0, y0, z0);
	sph->setRadius(r);
	return true;
}
bool CFIT_6203_Voronkov_Ray_Io::readBox(CArchive *m_arc_in, Box * box)
{
	CString buf;
	double x_min, y_min, z_min;
	double x_max, y_max, z_max;
	readUString(*m_arc_in, &buf);
	if ( sscanf_s(buf.GetBuffer(), "%lf %lf %lf", &x_min, &y_min, &z_min) != 3){
		AfxThrowArchiveException(CArchiveException::genericException);
	}
	readUString(*m_arc_in, &buf);
	if ( sscanf_s(buf.GetBuffer(), "%lf %lf %lf", &x_max, &y_max, &z_max) != 3){
		AfxThrowArchiveException(CArchiveException::genericException);
	}
	box->setMin(x_min, y_min, z_min);
	box->setMax(x_max, y_max, z_max);
	return true;
}
bool CFIT_6203_Voronkov_Ray_Io::readPolygon(CArchive *m_arc_in, Polygone * polygon)
{
	CString buf;
	int count = 0;
	readUString(*m_arc_in, &buf);
	if ( sscanf_s(buf.GetBuffer(), "%d", &count) != 1){
		AfxThrowArchiveException(CArchiveException::genericException);
	}
	polygon->setVertexCount(count);
	double x, y, z;
	for (int i=0; i<count; i++)
	{
		readUString(*m_arc_in, &buf);
		if ( sscanf_s(buf.GetBuffer(), "%lf %lf %lf", &x, &y, &z) != 3){
			AfxThrowArchiveException(CArchiveException::genericException);
		}
		polygon->insertPoint(i, x, y, z);
	}
	polygon->checkPolygon();
	return true;
}
bool CFIT_6203_Voronkov_Ray_Io::readQuadric(CArchive *m_arc_in, Quadric * quadric)
{
	CString buf;
	double A, E, H, B, C, F, D, G, I, J;
	readUString(*m_arc_in, &buf);
	if ( sscanf_s(buf.GetBuffer(), "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", 
			&A, &E, &H, &B, &C, &F, &D, &G, &I, &J) != 10){
		AfxThrowArchiveException(CArchiveException::genericException);
	}
	*quadric = Quadric(A, E, H, B, C, F, D, G, I, J);
	return true;
}
bool CFIT_6203_Voronkov_Ray_Io::readQuadroBox(CArchive *m_arc_in, QuadroBox * quadro_box)
{
	CString buf;
	double A, E, H, B, C, F, D, G, I, J;
	readUString(*m_arc_in, &buf);
	if ( sscanf_s(buf.GetBuffer(), "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", 
			&A, &E, &H, &B, &C, &F, &D, &G, &I, &J) != 10){
		AfxThrowArchiveException(CArchiveException::genericException);
	}
	Quadric quadric = Quadric(A, E, H, B, C, F, D, G, I, J);

	double hx, hy, hz, lx, ly, lz;
	readUString(*m_arc_in, &buf);	
	if (sscanf_s(buf.GetBuffer(), "%lf %lf %lf", &hx, &hy, &hz) != 3){
		AfxThrowArchiveException(CArchiveException::genericException);
	}
	readUString(*m_arc_in, &buf);	
	if (sscanf_s(buf.GetBuffer(), "%lf %lf %lf", &lx, &ly, &lz) != 3){
		AfxThrowArchiveException(CArchiveException::genericException);
	}
	// normalize
	if (hx < lx){
		double tmp = lx;
		lx = hx;
		hx = tmp;
	}
	if (hy < ly){
		double tmp = ly;
		ly = hy;
		hy = tmp;
	}
	if (hz < lz){
		double tmp = lz;
		lz = hz;
		hz = tmp;
	}
	Box box = Box(lx, ly, lz, hx, hy, hz);
	(*quadro_box) = QuadroBox(quadric, box);
	return true;
}
bool CFIT_6203_Voronkov_Ray_Io::readMatrix4(CArchive *m_arc_in, Matrix * matrix)
{
	double fx, fy, fz, fw;
	CString buf;
	for (int i=0; i<4; i++)
	{
		readUString(*m_arc_in, &buf);
		if (sscanf_s(buf.GetBuffer(), "%lf %lf %lf %lf", &fx, &fy, &fz, &fw) != 4){
			AfxThrowArchiveException(CArchiveException::genericException);
		}
		matrix->setRaw(i, 0, fx);
		matrix->setRaw(i, 1, fy);
		matrix->setRaw(i, 2, fz);
		matrix->setRaw(i, 3, fw);
	}
	return true;
}
bool CFIT_6203_Voronkov_Ray_Io::writeMatrix4(CArchive *out, const Matrix & matrix)
{
	CString str;
	for (int i=0; i<4; i++){
		str.Format("%.6lf %.6lf %.6lf %.6lf\r\n", 
			matrix.getRaw(i, 0), matrix.getRaw(i, 1), matrix.getRaw(i, 2), matrix.getRaw(i, 3));
		out->WriteString(str);
	}
	return true;
}
bool CFIT_6203_Voronkov_Ray_Io::readOptics(CArchive *in, Primitive * p)
{
	CString str;
	double kar, kag, kab;
	double kdr, kdg, kdb;
	double ksr, ksg, ksb;
	double power;
	double kt;
	double n1, n2;

	readUString(*in, &str);
	if (sscanf_s(str.GetBuffer(), "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf  %lf %lf", 
			&kar, &kag, &kab, &kdr, &kdg, &kdb, &ksr, &ksg, &ksb, &power, &kt, &n1, &n2) != 13){
		AfxThrowArchiveException(CArchiveException::genericException);
	}
	p->setOptics(kar, kag, kab, kdr, kdg, kdb, ksr, ksg, ksb, power, kt, n1, n2);
	return true;
}
bool CFIT_6203_Voronkov_Ray_Io::readMatrix3(CArchive *m_arc_in, Matrix * matrix)
{
	double fx, fy, fz;
	CString buf;
	for (int i=0; i<3; i++)
	{
		readUString(*m_arc_in, &buf);
		if (sscanf_s(buf.GetBuffer(), "%lf %lf %lf", &fx, &fy, &fz) != 3){
			AfxThrowArchiveException(CArchiveException::genericException);
		}
		matrix->setRaw(i, 0, fx);
		matrix->setRaw(i, 1, fy);
		matrix->setRaw(i, 2, fz);
		matrix->setRaw(i, 3, 0);
	}
	matrix->setRaw(3, 0, 0);
	matrix->setRaw(3, 1, 0);
	matrix->setRaw(3, 2, 0);
	matrix->setRaw(3, 3, 1);
	return true;
}
bool CFIT_6203_Voronkov_Ray_Io::writeMatrix3(CArchive *out, const Matrix & matrix)
{
	CString str;
	for (int i=0; i<3; i++){
		str.Format("%.6lf %.6lf %.6lf\r\n", 
			matrix.getRaw(i, 0), matrix.getRaw(i, 1), matrix.getRaw(i, 2));
		out->WriteString(str);
	}
	return true;
}
bool CFIT_6203_Voronkov_Ray_Io::loadScene(CArchive * in, Scene * scene)
{
	CString str;
	bool flag_no_warning = true;
//// read scene header
	
	// read ambient light
	double ar, ag, ab;
	readUString(*in, &str);
	if (sscanf_s(str.GetBuffer(), "%lf %lf %lf", &ar, &ag, &ab) != 3){
		AfxThrowArchiveException(CArchiveException::genericException);
	}
	scene->setAmbientColor(Color(ar, ag, ab));

	// read lights
	//// read number of lights
	int countLights;
	readUString(*in, &str);
	if (sscanf_s(str.GetBuffer(), "%d", &countLights) != 1){
		AfxThrowArchiveException(CArchiveException::genericException);
	}
	for (int i=0; i<countLights; i++)
	{
		double lx, ly, lz, cr, cg, cb;
		readUString(*in, &str);
		if (sscanf_s(str.GetBuffer(), "%lf %lf %lf %lf %lf %lf", &lx, &ly, &lz, &cr, &cg, &cb) != 6){
			AfxThrowArchiveException(CArchiveException::genericException);
		}
		scene->addLight(Light(Point(lx, ly, lz), Color(cr, cg, cb)));
	}

//// read scene sections
	int count = -1;
	while (true)
	{
		count ++;
		CString tmp;
		try{
			readUString(*in, &str);
		}catch(...){
			return flag_no_warning;
		}
		if (str == "SPH"){
			Sphere * s = new Sphere();
			readSphere(in, s);
			readOptics(in, s);
			if (!s->isCorrect()){
				flag_no_warning = false;
				
				tmp.Format("Warning: %d", count);
				AfxMessageBox(tmp);
				delete s;
				continue;
			}
			scene->addPrimitive(s);
			TRACE("sphere loaded\n");
		}
		else if (str == "BOX"){
			Box * b = new Box();
			readBox(in, b);
			readOptics(in, b);
			if (!b->isCorrect()){
				flag_no_warning = false;
				tmp.Format("Warning: %d", count);
				AfxMessageBox(tmp);
				delete b;
				continue;
			}
			scene->addPrimitive(b);
			TRACE("box loaded\n");
		}
		else if (str == "PLG"){
			Polygone * p = new Polygone();
			readPolygon(in, p);
			readOptics(in, p);
			if (!p->isCorrect()){
				flag_no_warning = false;
				tmp.Format("Warning: %d", count);
				AfxMessageBox(tmp);
				delete p;
				continue;
			}
			scene->addPrimitive(p);
			TRACE("polygon loaded\n");
		}
		else if (str == "QDR"){
			QuadroBox * q = new QuadroBox();
			readQuadroBox(in, q);
			readOptics(in, q);
			if (!q->isCorrect()){
				flag_no_warning = false;
				tmp.Format("Warning: %d", count);
				AfxMessageBox(tmp);
				delete q;
				continue;
			}
			scene->addPrimitive(q);
			TRACE("quadric loaded\n");
		}
		else{
			AfxThrowArchiveException(CArchiveException::genericException);
		}
	}
	return flag_no_warning;
}
bool CFIT_6203_Voronkov_Ray_Io::loadRenderSet(CArchive * in, RenderSet * r_set)
{
	CString str;
	// read scroll sizes
	int width, height;
	readUString(*in, &str);
	if (sscanf_s(str.GetBuffer(), "%d %d", &width, &height) != 2){
		AfxThrowArchiveException(CArchiveException::genericException);
	}
	r_set->setScrollSize(width, height);
	// Read backgroung color
	int r, g, b;
	readUString(*in, &str);
	if (sscanf_s(str.GetBuffer(), "%d %d %d", &r, &g, &b) != 3){
		AfxThrowArchiveException(CArchiveException::genericException);
	}
	r_set->setBackground(RGB(r, g, b));
	// read gamma
	double gamma;
	readUString(*in, &str);
	if (sscanf_s(str.GetBuffer(), "%lf", &gamma) != 1){
		AfxThrowArchiveException(CArchiveException::genericException);
	}
	r_set->setGamma(gamma);
	// read tree depth
	int tree_depth;
	readUString(*in, &str);
	if (sscanf_s(str.GetBuffer(), "%d", &tree_depth) != 1){
		AfxThrowArchiveException(CArchiveException::genericException);
	}
	r_set->setTreeDepth(tree_depth);
	//read quality
	readUString(*in, &str);
	if (str.CompareNoCase(CString("rough")) == 0){
		r_set->setQuality(RenderSet::Q_ROUGH);
	}
	else if (str.CompareNoCase(CString("normal")) == 0){
		r_set->setQuality(RenderSet::Q_NORMAL);
	}
	else if (str.CompareNoCase(CString("fine")) == 0){
		r_set->setQuality(RenderSet::Q_FINE);
	}
	else{
		AfxThrowArchiveException(CArchiveException::genericException);
	}
	// read center_z
	double z;
	readUString(*in, &str);
	if (sscanf_s(str.GetBuffer(), "%lf", &z) != 1){
		AfxThrowArchiveException(CArchiveException::genericException);
	}
	// read rotation matrix
	Matrix rotate;
	readMatrix3(in, &rotate);
	// set camera
	r_set->setCamera(Camera(z, rotate));
	// everything is ok.
	return true;
}
bool CFIT_6203_Voronkov_Ray_Io::saveRenderSet(CArchive * out, const RenderSet & r_set)
{
	CString str;
	
	// write scroll sizes
	CSize scroll_sizes = r_set.scrollSize();
	str.Format("%d %d\r\n", scroll_sizes.cx, scroll_sizes.cy);
	out->WriteString(str);
	
	//write background
	COLORREF back = r_set.background();
	str.Format("%d %d %d\r\n", GetRValue(back), GetGValue(back), GetBValue(back));
	out->WriteString(str);
	
	//write gamma
	str.Format("%.5lf\r\n", r_set.gamma());
	out->WriteString(str);

	// write tree depth
	str.Format("%d\r\n", r_set.treeDepth());
	out->WriteString(str);

	// write quality
	int quality = r_set.quality();
	if (quality == RenderSet::Q_ROUGH){
		str.Format("rough\r\n");
	}
	else if (quality == RenderSet::Q_NORMAL){
		str.Format("normal\r\n");
	}
	else if (quality == RenderSet::Q_FINE){
		str.Format("fine\r\n");
	}
	else{
		ASSERT (false);
	}
	out->WriteString(str);

	// write center_z
	const Camera & cam = r_set.camera();
	double z = cam.centerZ();
	str.Format("%.5lf\r\n", z);
	out->WriteString(str);

	// write rotate matrix
	const Matrix & matr = cam.matrixRotate();
	CFIT_6203_Voronkov_Ray_Io::writeMatrix3(out, matr);
	
	return true;
}
bool CFIT_6203_Voronkov_Ray_Io::saveBmp(CArchive * m_arc, const CDC * pDC, 
										const CSize & size, int offset)
{
	ASSERT (m_arc != NULL && pDC != NULL);

	unsigned char * buf = new unsigned char[40];
	buf[0] = 'B';
	buf[1] = 'M';

	write4bytes(getImageSize(size), &buf[2]);
	write4bytes(14 + 40, &buf[10]);
	m_arc->Write(buf, 14); // write file header
	
	write4bytes(40, &buf[0]); // Size of information header
//	CSize img_size = size;
	int row_length = getRasterRowLength(size.cx);
	write4bytes(size.cx , &buf[4]); // image width
	write4bytes(size.cy , &buf[8]); // image height

	write2bytes(1, &buf[12]); // Number of color planes
	write2bytes(24, &buf[14]); // bits per pixel
	write4bytes(0, &buf[16]); // compression method
	write4bytes(row_length * size.cy, &buf[20]); // Number of bytes of bitmap data
	memset(&buf[24], 0, 16);

	m_arc->Write(buf, 40);
	
	// writing bitmap data
	unsigned char * row = new unsigned char[row_length];
	COLORREF c_color;
	for (int i=0; i<size.cy; i++)
	{
		for(int j=0; j<size.cx; j++)
		{
			c_color = pDC->GetPixel(j+offset, size.cy - 1 - i+offset);
			row[3 * j]     = GetBValue(c_color);
			row[3 * j + 1] = GetGValue(c_color);
			row[3 * j + 2] = GetRValue(c_color);
		}
		m_arc->Write(row, row_length);
	}
	delete[] row;
	delete[] buf;
	return true;
}
void CFIT_6203_Voronkov_Ray_Io::write4bytes(int n, unsigned char *out)
{
	out[0] = (unsigned char)(n % 256);
	out[1] = (unsigned char) ((n >> 8) % 256);
	out[2] = (unsigned char) ((n >> 16) % 256);
	out[3] = (unsigned char) ((n >> 24) % 256);
}
void CFIT_6203_Voronkov_Ray_Io::write2bytes(int n, unsigned char *out)
{
	out[0] = (unsigned char)(n % 256);
	out[1] = (unsigned char) ((n >> 8) % 256);
}
int CFIT_6203_Voronkov_Ray_Io::getImageSize(const CSize & img_size)
{
	int res = 0;
//	CSize img_size = m_img->size();
	res += (14 + 40);
	int rowlength =  getRasterRowLength(img_size.cx);
	res += rowlength * img_size.cy;
	return res;
}
int CFIT_6203_Voronkov_Ray_Io::getRasterRowLength(int cols)
{
	cols *= 3;
	if ((cols % 4) == 0) return  cols;
	return  ((cols >> 2) + 1) << 2;
}