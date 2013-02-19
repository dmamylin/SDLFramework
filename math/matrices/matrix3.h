#ifndef MATRIX3_H
#define MATRIX3_H

class mat4;

class mat3
{
	private:
		float m[9];
	
	public:
		mat3() { Identity(); }
		mat3(float* M) { memcpy(m, M, sizeof(float) * 9); }
		mat3(const mat3& M) { memcpy(m, M.m, sizeof(float) * 9); }
		mat3(const mat4&);
	
		inline void operator = (const mat3& r) { memcpy(m, r.m, sizeof(float) * 9); }
		inline float& operator [] (int ind) { return m[ind]; }
		inline float operator [] (int ind) const { return m[ind]; }
		void operator /= (const float);
		void operator *= (const mat3&);
		void operator *= (const float);
		void operator += (const mat3&);
		void operator += (const float);
		void operator -= (const mat3&);
		void operator -= (const float);
		
		friend bool operator == (const mat3&, const mat3&);
		friend bool operator != (const mat3&, const mat3&);
		friend mat3 operator + (const mat3&, const mat3&);
		friend mat3 operator + (const mat3&, const float);
		friend mat3 operator + (const float, const mat3&);
		friend mat3 operator - (const mat3&, const mat3&);
		friend mat3 operator - (const mat3&, const float);
		friend mat3 operator - (const float, const mat3&);
		friend mat3 operator * (const mat3&, const mat3&);
		friend mat3 operator * (const mat3&, const float);
		friend mat3 operator * (const float, const mat3&);	
		friend mat3 operator / (const mat3&, const float);
		friend mat3 operator / (const float, const mat3&);
	
		inline void Null(void) { memset(m, 0, sizeof(float) * 9); }
		void Identity(void);
		void Transpose(void);
		
		inline float Determinant(void) { return m[4] * (m[0] * m[8] - m[6] * m[2]) + m[3] * (m[7] * m[2] - m[1] * m[8]) + m[5] * (m[6] * m[1] - m[0] * m[7]); }
		mat3 Inverse(void);
};

inline void mat3::operator /= (const float k)
{
	(*this) = (*this) / k;
}

inline void mat3::operator *= (const mat3& m)
{
	(*this) = (*this) * m;
}

inline void mat3::operator *= (const float k)
{
	(*this) = (*this) * k;
}

inline void mat3::operator += (const mat3& m)
{
	(*this) = (*this) + m;
}

inline void mat3::operator += (const float k)
{
	(*this) = (*this) + k;
}

inline void mat3::operator -= (const mat3& m)
{
	(*this) = (*this) - m;
}

inline void mat3::operator -= (const float k)
{
	(*this) = (*this) - k;
}

inline mat3 operator + (const float k, const mat3& m)
{
	return (m + k);
}

inline mat3 operator - (const float k, const mat3& m)
{
	return (m - k);
}

inline mat3 operator * (const float k, const mat3& m)
{
	return (m * k);
}

inline mat3 operator / (const float k, const mat3& m)
{
	return (m / k);
}

bool operator == (const mat3& m0, const mat3& m1)
{
	for (int i = 0; i < 9; i++)
		if (m0[i] != m1[i])
			return false;
	return true;
}

bool operator != (const mat3& m0, const mat3& m1)
{
	return !(m0 == m1);
}

mat3 operator + (const mat3& m0, const mat3& m1)
{
	mat3 temp;
	for (int i = 0; i < 9; i++)
		temp.m[i] = m0.m[i] + m1.m[i];
	return temp;
}

mat3 operator + (const mat3& m, const float k)
{
	mat3 temp;
	for (int i = 0; i < 9; i++)
		temp.m[i] = m[i] + k;
	return temp;
}

mat3 operator - (const mat3& m0, const mat3& m1)
{
	mat3 temp;
	for (int i = 0; i < 9; i++)
		temp.m[i] = m0.m[i] - m1.m[i];
	return temp;
}

mat3 operator - (const mat3& m, const float k)
{
	mat3 temp;
	for (int i = 0; i < 9; i++)
		temp.m[i] = m[i] - k;
	return temp;
}

mat3 operator * (const mat3& A, const mat3& B)
{
    mat3 M;
	
    M[0] = A[0] * B[0] + A[1] * B[3] + A[2] * B[6];
    M[1] = A[0] * B[1] + A[1] * B[4] + A[2] * B[7];
    M[2] = A[0] * B[2] + A[1] * B[5] + A[2] * B[8];
    M[3] = A[3] * B[0] + A[4] * B[3] + A[5] * B[6];
    M[4] = A[3] * B[1] + A[4] * B[4] + A[5] * B[7];
    M[5] = A[3] * B[2] + A[4] * B[5] + A[5] * B[8];
    M[6] = A[6] * B[0] + A[7] * B[3] + A[8] * B[6];
    M[7] = A[6] * B[1] + A[7] * B[4] + A[8] * B[7];
    M[8] = A[6] * B[2] + A[7] * B[5] + A[8] * B[8];
	
    return M;
}

mat3 operator * (const mat3& m, const float k)
{
	mat3 temp;
	for (int i = 0; i < 9; i++)
		temp.m[i] = m[i] * k;
	return temp;
}

mat3 operator / (const mat3& m, const float k)
{
	mat3 temp;
	for (int i = 0; i < 9; i++)
		temp.m[i] = m[i] / k;
	return temp;
}

void mat3::Identity(void)
{
	Null();
	m[0] = m[4] = m[8] = 1.0f;
}

void mat3::Transpose(void)
{
	mat3 temp;
	temp.Null();
	
	for (int i = 0; i < 3; i++)
		for (int j = 0, k = 3 * i; j < 9; j += 3, k++)
			temp.m[j + i] = m[k];
			
	(*this) = temp;
}

mat3 mat3::Inverse(void)
{
    float det = Determinant();

    float temp[9] = { 
                  m[4] * m[8] - m[7] * m[5], m[7] * m[2] - m[1] * m[8], m[1] * m[5] - m[4] * m[2],
                  m[6] * m[5] - m[3] * m[8], m[0] * m[8] - m[6] * m[2], m[3] * m[2] - m[0] * m[5],
                  m[3] * m[7] - m[6] * m[4], m[6] * m[1] - m[0] * m[7], m[0] * m[4] - m[3] * m[1]
                };

    for (int i = 0; i < 9; i++)
        temp[i] /= det;

    return mat3(temp);
}

#endif