#include "../../include/astrocore/component/transform2D.h"

using namespace Astrocore;

// NOTE: Per the OpenGL docs, transforms should be done in the order: scale, rotate, translate

Transform2D::Transform2D()
{
	position = {0,0};
	rotation = 0;
	scale = {1,1};
}

Transform2D::Transform2D(Vector2 initialPosition, float initialRotationDegrees)
{
	Transform2D();
	this->position = {initialPosition.x, initialPosition.y, 0};
	this->rotation = initialRotationDegrees * PI/180.0f;
}

// Copy constructor
Transform2D::Transform2D(Transform2D* other)
{
	this->position = {other->GetPosition().x, other->GetPosition().y, 0};
	this->scale = other->GetScale();
	this->rotation = other->GetRotation();
}

Transform2D::Transform2D(Matrix transformMat)
{
	Transform2D();
	SetMatrix(transformMat);
}

void Transform2D::SetMatrix(Matrix newMat)
{
	Quaternion quat = QuaternionIdentity();
	Vector3 tempScale = {1,1,1};
	Transform2D::MatrixDecompose(newMat, &(this->position), &quat, &tempScale);
    this->scale = {tempScale.x, tempScale.y};

    // 'Normalize' the rotation by applying the inverse scale factor to the matrix
    Matrix inverseScale = MatrixScale(1.0f/ scale.x, 1.0f / scale.y, 1.0f);
	this->rotation = QuaternionToEuler(QuaternionFromMatrix(MatrixMultiply(newMat, inverseScale))).z;
}

void Transform2D::Translate(Vector2 translation)
{
	this->position = Vector3Add(position, {translation.x, translation.y, 0});
}

void Transform2D::TranslateLocal(Vector2 translation)
{
	Vector2 rotated = Vector2Transform(translation, MatrixRotateZ(rotation));
	position = Vector3Add(position, {rotated.x, rotated.y, 0});
}

void Transform2D::RotateDegrees(float rotationDelta)
{
	this->Rotate((rotationDelta * PI / 180.0f));
}

void Transform2D::Rotate(float rotationDelta)
{
	this->rotation += rotationDelta;
}

void Transform2D::Scale(Vector2 scaleDelta)
{
	scale = Vector2Multiply(scale, scaleDelta);
}

// Setters
void Transform2D::SetPosition(Vector2 newPosition)
{
	position = {newPosition.x, newPosition.y};
}

void Transform2D::SetRotationDegrees(float rotationDegrees)
{
	SetRotation(rotationDegrees * PI/180.0f );
}

void Transform2D::SetRotation(float rotation)
{
	this->rotation = rotation;
}

void Transform2D::SetScale(float scaleX, float scaleY)
{
	scale = {scaleX, scaleY};
}


void Transform2D::SetTransform(Vector2 position, float rotation, Vector2 scale)
{
	Scale(scale);
	Rotate(rotation);
	Translate(position);
}

Matrix Transform2D::GetMatrix()
{
	Matrix matToReturn = MatrixIdentity();
    matToReturn = MatrixMultiply(matToReturn, MatrixScale(scale.x, scale.y, 1)); 
    matToReturn = MatrixMultiply(matToReturn, MatrixRotateZ(rotation));
    matToReturn = MatrixMultiply(matToReturn, MatrixTranslate(position.x, position.y, 0));
    //
	
     
	return matToReturn;
}

Vector2 Transform2D::GetPosition()
{
	return {position.x, position.y};
}

Vector2 Transform2D::GetScale()
{
	return {scale.x, scale.y};
}

float Transform2D::GetRotation()
{
	return rotation;
}

float Transform2D::GetRotationDegrees()
{
	return GetRotation() * 180.0f/PI;
}

// Copy from raymath because the vcpkg doesn't have the current version of the header file for some reason...
void Transform2D::MatrixDecompose(Matrix mat, Vector3 *translation, Quaternion *rotation, Vector3 *scale)
{
    // Extract translation.
    translation->x = mat.m12;
    translation->y = mat.m13;
    translation->z = mat.m14;

    // Extract upper-left for determinant computation
    const float a = mat.m0;
    const float b = mat.m4;
    const float c = mat.m8;
    const float d = mat.m1;
    const float e = mat.m5;
    const float f = mat.m9;
    const float g = mat.m2;
    const float h = mat.m6;
    const float i = mat.m10;
    const float A = e*i - f*h;
    const float B = f*g - d*i;
    const float C = d*h - e*g;

    // Extract scale
    const float det = a*A + b*B + c*C;
    Vector3 abc = { a, b, c };
    Vector3 def = { d, e, f };
    Vector3 ghi = { g, h, i };

    float scalex = Vector3Length(abc);
    float scaley = Vector3Length(def);
    float scalez = Vector3Length(ghi);
    Vector3 s = { scalex, scaley, scalez };

    if (det < 0) s = Vector3Negate(s);

    *scale = s;

    // Remove scale from the matrix if it is not close to zero
    Matrix clone = mat;
    if (!FloatEquals(det, 0))
    {
        clone.m0 /= s.x;
        clone.m5 /= s.y;
        clone.m10 /= s.z;

        // Extract rotation
        *rotation = QuaternionFromMatrix(clone);
    }
    else
    {
        // Set to identity if close to zero
        *rotation = QuaternionIdentity();
    }
}