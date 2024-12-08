#ifndef TRANSFORM2D_H
#define TRANSFORM2D_H
#include <raylib.h>
#include <raymath.h>

namespace Astrocore
{
	class Transform2D
	{
	private:
		Vector3 position;
		float rotation;
		Vector2 scale;

		void SetTransform(Vector2 position, float rotation, Vector2 scale);
		void MatrixDecompose(Matrix matrix, Vector3* translation, Quaternion* rotation, Vector3* scale);

	public:
		// Constructors
		Transform2D();
		Transform2D(Vector2 initialPosition, float rotation);
		Transform2D(Transform2D* other);
		Transform2D(Matrix transformMat);
		//~Transform2D();
	
		// Modifiers
		void Translate(Vector2 translation);
		void TranslateLocal(Vector2 translation);
		void RotateDegrees(float rotationDelta);
		void Rotate(float rotationDelta);
		void Scale(Vector2 scaleDelta);

		// Setters
		void SetPosition(Vector2 newPosition);
		void SetRotationDegrees(float rotationDegrees);
		void SetRotation(float rotation);
		void SetScale(float scaleX, float scaleY);
		void SetMatrix(Matrix newMat);

		// Getters
		Vector2 GetPosition();
		Vector2 GetScale();
		float GetRotation();
		float GetRotationDegrees();
		Matrix GetMatrix();
	};
}
#endif // !TRANSFORM2D