#pragma once

#include "FIT_6203_Voronkov_Ray_Primitive.h"
#include "FIT_6203_Voronkov_Ray_Light.h"

class CFIT_6203_Voronkov_Ray_Scene
{
private:
	Color m_ambient;	// ���������� ���� 
	CArray<Light> m_lights;  // ��������� �����
	CArray<Primitive*> m_prims; // ���������
	double m_max_coords[3]; // ���������� ����������� ����� �����
	double m_min_coords[3];
public:
	CFIT_6203_Voronkov_Ray_Scene();
	~CFIT_6203_Voronkov_Ray_Scene();

	void setAmbientColor(const Color & color);
	void addLight(const Light & light);
	void addPrimitive(Primitive * p);

	int countPrimitives() const; // ���������� ����������
	int countLights() const; // ���������� ���������� �����

	const Color & ambientColor() const;
	const Light & light(int i) const;
	Primitive * primitive(int i);

	WireFrame getWireFrame() const;

	double getMax(int coord) const;
	double getMin(int coord) const;

	bool intersect(const Ray & ray, Ray * reflecred, Ray * normal, Primitive ** pprim);

//	Color countTotalDiffuseLight(const Ray & normal, const Color & factor)const;
	Color countDiffuseLight(const Ray & normal, const Color & factor, int light_idx)const;
	Color countSpecularLight(const Ray & normal, Point to_eye, const Color & factor, int light_idx, double power)const;
	int lightIsVisible(const Point & point, const Point & light)const;
	int lightIsVisible(const Point & point, int light_idx)const;
};

typedef CFIT_6203_Voronkov_Ray_Scene Scene;