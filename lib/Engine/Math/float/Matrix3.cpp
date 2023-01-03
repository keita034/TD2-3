#include "Matrix3.h"
#include"AliceMathF.h"

namespace AliceMathF
{
	Matrix3::Matrix3()
	{
		m[0][0] = 1.0f;
		m[0][1] = 0.0f;
		m[0][2] = 0.0f;

		m[1][0] = 0.0f;
		m[1][1] = 1.0f;
		m[1][2] = 0.0f;

		m[2][0] = 0.0f;
		m[2][1] = 0.0f;
		m[2][2] = 1.0f;
	}

	Matrix3::Matrix3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22)
	{
		m[0][0] = m00;
		m[0][1] = m01;
		m[0][2] = m02;

		m[1][0] = m10;
		m[1][1] = m11;
		m[1][2] = m12;

		m[2][0] = m20;
		m[2][1] = m21;
		m[2][2] = m22;
	}


	Matrix3::Matrix3(const Vector2& scale, float angle, const Vector2& trans)
	{
		AliceMathF::Matrix3 matScale, matRot, matTrans;

		//�X�P�[���A��]�A���s�ړ��s��̌v�Z
		matScale.MakeScaling(scale);
		matRot.MakeRotation(angle);
		matTrans.MakeTranslation(trans);

		//���[���h�s��̍���
		//�ό`�����Z�b�g
		*this = AliceMathF::MakeMat3Identity();
		//���[���h�s��ɃX�P�[�����O�𔽉f
		*this *= matScale;
		//���[���h�s��ɉ�]�𔽉f
		*this *= matRot;
		//���[���h�s��ɕ��s�ړ��𔽉f
		*this *= matTrans;
	}

	Matrix3::Matrix3(const aiMatrix3x3& mat)
	{
		m[0][0] = mat.a1;
		m[0][1] = mat.a2;
		m[0][2] = mat.a3;

		m[1][0] = mat.b1;
		m[1][1] = mat.b2;
		m[1][2] = mat.b3;

		m[2][0] = mat.c1;
		m[2][1] = mat.c2;
		m[2][2] = mat.c3;
	}

	Matrix3 MakeMat3Identity()
	{
		Matrix3 mat;
		return mat;
	}

	Matrix3 MakeInverse(const Matrix3* mat)
	{
		assert(mat);

		//�|���o���@���s���s��
		float sweep[3][6]{};
		//�萔�{�p
		float constTimes = 0.0f;
		//���e����덷
		float MAX_ERR = 1e-10f;
		//�߂�l�p
		Matrix3 retMat;

		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				//weep�̍����ɋt�s������߂�s����Z�b�g
				sweep[i][j] = mat->m[i][j];

				//sweep�̉E���ɒP�ʍs����Z�b�g
				sweep[i][3 + j] = MakeMat3Identity().m[i][j];
			}
		}

		//�S�Ă̗�̑Ίp�����ɑ΂���J��Ԃ�
		for (size_t i = 0; i < 3; i++)
		{
			//�ő�̐�Βl�𒍖ڑΊp�����̐�Βl�Ɖ���
			float max = std::fabs(sweep[i][i]);
			size_t maxIndex = i;

			//i��ڂ��ő�̐�Βl�ƂȂ�s��T��
			for (size_t j = i + 1; j < 3; j++)
			{
				if (std::fabs(sweep[j][i]) > max)
				{
					max = std::fabs(sweep[j][i]);
					maxIndex = j;
				}
			}

			if (fabs(sweep[maxIndex][i]) <= MAX_ERR)
			{
				//�t�s��͋��߂��Ȃ�
				return MakeMat3Identity();
			}

			//����(1):i�s�ڂ�maxIndex�s�ڂ����ւ���
			if (i != maxIndex)
			{
				for (size_t j = 0; j < 6; j++)
				{
					float tmp = sweep[maxIndex][j];
					sweep[maxIndex][j] = sweep[i][j];
					sweep[i][j] = tmp;
				}
			}

			//sweep[i][i]�Ɋ|�����1�ɂȂ�l�����߂�
			constTimes = 1 / sweep[i][i];

			//����(2):p�s�ڂ�a�{����
			for (size_t j = 0; j < 6; j++)
			{
				//����ɂ��sweep[i][i]��1�ɂȂ�
				sweep[i][j] *= constTimes;
			}

			//����(3)�ɂ��i�s�ڈȊO�̍s��i��ڂ�0�ɂ���
			for (size_t j = 0; j < 6; j++)
			{
				if (j == i)
				{
					//i�s�ڂ͂��̂܂�
					continue;
				}

				//i�s�ڂɊ|����l�����߂�
				constTimes = -sweep[j][i];

				for (size_t k = 0; k < 6; k++)
				{
					//j�s�ڂ�i�s�ڂ�a�{�����s�𑫂�
					//����ɂ��sweep[j][i]��0�ɂȂ�
					sweep[j][k] += sweep[i][k] * constTimes;
				}
			}
		}

		//sweep�̉E������mat�̋t�s��
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				retMat.m[i][j] = sweep[i][3 + j];
			}
		}

		return retMat;
	}

	Matrix3::Matrix3(const DirectX::XMFLOAT3X3& Matrix3)
	{
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				m[i][j] = Matrix3.m[i][j];
			}
		}
	}

	void Matrix3::MakeScaling(const Vector2& scale)
	{
		//�X�P�[�����O�{�����s��ɐݒ肷��
		m[0][0] = scale.x;
		m[1][1] = scale.y;
	}

	void Matrix3::MakeScaling(float x, float y)
	{
		MakeScaling(Vector2(x, y));
	}

	void Matrix3::MakeTranslation(const Vector2& trans)
	{
		m[3][0] = trans.x;
		m[3][1] = trans.y;
	}

	void Matrix3::MakeTranslation(float x, float y)
	{
		MakeTranslation(Vector2(x, y));
	}

	void Matrix3::MakeRotation(float angle)
	{
		m[0][0] = Cos(angle);
		m[0][1] = -Sin(angle);

		m[1][0] = Sin(angle);
		m[1][1] = Cos(angle);
	}

	Matrix3::operator DirectX::XMFLOAT3X3() const
	{
		DirectX::XMFLOAT3X3 mat {
		m[0][0], m[0][1], m[0][2],
		m[1][0], m[1][1], m[1][2],
		m[2][0], m[2][1], m[2][2]};

		return mat;
	}

	Matrix3 Matrix3::Transpose()
	{
		Matrix3 tmp(*this);
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = i; j < 3; j++)
			{
				float f = tmp.m[i][j];
				tmp.m[i][j] = tmp.m[j][i];
				tmp.m[j][i] = f;
			}
		}

		return tmp;
	}

	Matrix3& Matrix3::operator=(const Matrix3& _m)
	{
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				m[i][j] = _m.m[i][j];
			}
		}

		return *this;
	}

	const Matrix3& Matrix3::operator=(Matrix3& _m)
	{
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				m[i][j] = _m.m[i][j];
			}
		}

		return *this;
	}

	Matrix3& Matrix3::operator+=(const Matrix3& mat)
	{
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				m[i][j] += mat.m[i][j];
			}
		}

		return *this;
	}

	Matrix3& Matrix3::operator-=(const Matrix3& mat)
	{
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				m[i][j] -= mat.m[i][j];
			}
		}

		return *this;
	}

	Matrix3& Matrix3::operator*=(const Matrix3& mat)
	{
		Matrix3 temp(*this);

		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				double f = 0.0;
				for (size_t k = 0; k < 3; k++)
				{
					f += (double)temp.m[i][k] * (double)mat.m[k][j];

					m[i][j] = (float)f;
				}


			}
		}
		return *this;
	}

	Matrix3 Matrix3::operator+(const Matrix3& mat) const
	{
		Matrix3 temp(*this);
		temp += mat;
		return temp;
	}

	Matrix3 Matrix3::operator-(const Matrix3& mat) const
	{
		Matrix3 temp(*this);
		temp -= mat;
		return temp;
	}

	Matrix3 Matrix3::operator*(const Matrix3& mat) const
	{
		Matrix3 temp(*this);
		temp *= mat;
		return temp;
	}
}