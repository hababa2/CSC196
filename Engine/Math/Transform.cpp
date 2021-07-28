#include "Transform.h"

namespace nh
{
	void Transform::Update()
	{
		Matrix33 mxs;
		mxs.Scale(scale);

		Matrix33 mxr;
		mxr.Rotate(rotation);

		Matrix33 mxt;
		mxt.Translate(position);

		matrix = mxs * mxr * mxt;
	}

	void Transform::Update(const Matrix33& mx)
	{
		Matrix33 mxs;
		mxs.Scale(lScale);

		Matrix33 mxr;
		mxr.Rotate(lRotation);

		Matrix33 mxt;
		mxt.Translate(lPosition);

		matrix = mxs * mxr * mxt * mx;

		position = matrix.GetTranslation();
		rotation = matrix.GetRotation();
		scale = matrix.GetScale();
	}
}