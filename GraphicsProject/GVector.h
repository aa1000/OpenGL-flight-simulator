#pragma once

class GVector
{

public:
	float x, y, z;

	GVector();
	GVector(float init);
	GVector(float x, float y, float z);
	GVector(const GVector & Other);

	void SetVector(float x, float y, float z);
	void init(float init);
	void ZeroOut();
	float Length() const;
	GVector GetUnitVector();

	GVector& operator=(const GVector& other); // copy assignment

	GVector& operator+=(const GVector& other);

	GVector operator+(const GVector& other);

	GVector operator-(const GVector& other);

	float operator|(const GVector& other); // dot product

	GVector operator*(const float& scalar); // multi scalar

	GVector operator/(const float& scalar); // div scalar

	GVector operator*(const GVector& other); // cross product

	bool operator==(const GVector& other);
};


