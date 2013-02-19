#ifndef MATRIX4_H
#define MATRIX4_H

class vec3;
class mat3;

class mat4
{
	private:
		float m[16];
	
	public:
		mat4() { Identity(); }
		mat4(float* M) { memcpy(m, M, sizeof(float) * 16); }
		mat4(const mat4& M) { memcpy(m, M.m, sizeof(float) * 16); }
		mat4(const mat3&);
	
		inline void operator = (const mat4& r) { memcpy(m,r.m,sizeof(float)*16); }
		inline float& operator [] (int ind) { return m[ind]; }
		inline float operator [] (int ind) const { return m[ind]; }
		void operator /= (const float);
		void operator *= (const mat4&);
		void operator *= (const float);
		void operator += (const mat4&);
		void operator += (const float);
		void operator -= (const mat4&);
		void operator -= (const float);
		
		friend bool operator == (const mat4&, const mat4&);
		friend bool operator != (const mat4&, const mat4&);
		friend mat4 operator + (const mat4&, const mat4&);
		friend mat4 operator + (const mat4&, const float);
		friend mat4 operator + (const float, const mat4&);
		friend mat4 operator - (const mat4&, const mat4&);
		friend mat4 operator - (const mat4&, const float);
		friend mat4 operator - (const float, const mat4&);
		friend mat4 operator * (const mat4&, const mat4&);
		friend mat4 operator * (const mat4&, const float);
		friend mat4 operator * (const float, const mat4&);		
		friend mat4 operator / (const mat4&, const float);
		friend mat4 operator / (const float, const mat4&);
	
		inline void Null(void) { memset(m, 0, sizeof(float) * 16); }
		void Identity(void);
		void LookAt(vec3, vec3, vec3);
		void Rotation(float  x, float y, float z);
		void Rotation(const vec3&);
		void Translation(float x, float y, float z);
		void Translation(const vec3&);
		void Scale(float x , float y , float z);
		void Scale(const vec3&);
		void Perspective(float fov, float aspect, float znear, float zfar);
        void Ortho(float left, float right, float bottom, float top);
		void Transpose(void);
		
		float Determinant(void) const;
		mat4 Inverse(void) const;
		
		friend mat4 RotationMatrix(float x, float y, float z);
		friend mat4 RotationMatrix(const vec3&);
		friend mat4 TranslationMatrix(float x, float y, float z);
		friend mat4 TranslationMatrix(const vec3&);
		friend mat4 ScaleMatrix(float x, float y, float z);
		friend mat4 ScaleMatrix(const vec3&);
};

inline void mat4::operator /= (const float k)
{
	(*this) = (*this) / k;
}

inline void mat4::operator *= (const mat4& m)
{
	(*this) = (*this) * m;
}

inline void mat4::operator *= (const float k)
{
	(*this) = (*this) * k;
}

inline void mat4::operator += (const mat4& m)
{
	(*this) = (*this) + m;
}

inline void mat4::operator += (const float k)
{
	(*this) = (*this) + k;
}

inline void mat4::operator -= (const mat4& m)
{
	(*this) = (*this) - m;
}

inline void mat4::operator -= (const float k)
{
	(*this) = (*this) - k;
}

inline mat4 operator + (const float k, const mat4& m)
{
	return (m + k);
}

inline mat4 operator - (const float k, const mat4& m)
{
	return (m - k);
}

inline mat4 operator * (const float k, const mat4& m)
{
	return (m * k);
}

inline mat4 operator / (const float k, const mat4& m)
{
	return (m / k);
}

inline mat4 RotationMatrix(float x, float y, float z)
{
	mat4 temp;
	temp.Rotation(x, y, z);
	return temp;
}

inline mat4 TranslationMatrix(float x, float y, float z)
{
	mat4 temp;
	temp.Translation(x, y, z);
	return temp;
}

inline mat4 ScaleMatrix(float x, float y, float z)
{
	mat4 temp;
	temp.Scale(x, y, z);
	return temp;
}

bool operator == (const mat4& m0, const mat4& m1)
{
	for (int i = 0; i < 16; i++)
		if (m0[i] != m1[i])
			return false;
	return true;
}

bool operator != (const mat4& m0, const mat4& m1)
{
	return !(m0 == m1);
}

mat4 operator + (const mat4& m0, const mat4& m1)
{
	mat4 temp;
	for (int i = 0; i < 16; i++)
		temp.m[i] = m0.m[i] + m1.m[i];
	return temp;
}

mat4 operator + (const mat4& m, const float k)
{
	mat4 temp;
	for (int i = 0; i < 16; i++)
		temp.m[i] = m[i] + k;
	return temp;
}

mat4 operator - (const mat4& m0, const mat4& m1)
{
	mat4 temp;
	for (int i = 0; i < 16; i++)
		temp.m[i] = m0.m[i] - m1.m[i];
	return temp;
}

mat4 operator - (const mat4& m, const float k)
{
	mat4 temp;
	for (int i = 0; i < 16; i++)
		temp.m[i] = m[i] - k;
	return temp;
}

mat4 operator * (const mat4& A, const mat4& B)
{
    mat4 M;
	
    M[ 0] = A[ 0] * B[ 0] + A[ 1] * B [ 4] + A[ 2] * B [ 8] + A[ 3] * B[12];
    M[ 1] = A[ 0] * B[ 1] + A[ 1] * B [ 5] + A[ 2] * B [ 9] + A[ 3] * B[13];
    M[ 2] = A[ 0] * B[ 2] + A[ 1] * B [ 6] + A[ 2] * B [10] + A[ 3] * B[14];
    M[ 3] = A[ 0] * B[ 3] + A[ 1] * B [ 7] + A[ 2] * B [11] + A[ 3] * B[15];
    M[ 4] = A[ 4] * B[ 0] + A[ 5] * B [ 4] + A[ 6] * B [ 8] + A[ 7] * B[12];
    M[ 5] = A[ 4] * B[ 1] + A[ 5] * B [ 5] + A[ 6] * B [ 9] + A[ 7] * B[13];
    M[ 6] = A[ 4] * B[ 2] + A[ 5] * B [ 6] + A[ 6] * B [10] + A[ 7] * B[14];
    M[ 7] = A[ 4] * B[ 3] + A[ 5] * B [ 7] + A[ 6] * B [11] + A[ 7] * B[15];
    M[ 8] = A[ 8] * B[ 0] + A[ 9] * B [ 4] + A[10] * B [ 8] + A[11] * B[12];
    M[ 9] = A[ 8] * B[ 1] + A[ 9] * B [ 5] + A[10] * B [ 9] + A[11] * B[13];
    M[10] = A[ 8] * B[ 2] + A[ 9] * B [ 6] + A[10] * B [10] + A[11] * B[14];
    M[11] = A[ 8] * B[ 3] + A[ 9] * B [ 7] + A[10] * B [11] + A[11] * B[15];
    M[12] = A[12] * B[ 0] + A[13] * B [ 4] + A[14] * B [ 8] + A[15] * B[12];
    M[13] = A[12] * B[ 1] + A[13] * B [ 5] + A[14] * B [ 9] + A[15] * B[13];
    M[14] = A[12] * B[ 2] + A[13] * B [ 6] + A[14] * B [10] + A[15] * B[14];
    M[15] = A[12] * B[ 3] + A[13] * B [ 7] + A[14] * B [11] + A[15] * B[15];
	
    return M;
}

mat4 operator * (const mat4& m, const float k)
{
	mat4 temp;
	for (int i = 0; i < 16; i++)
		temp.m[i] *= k;
	return temp;
}

mat4 operator / (const mat4& m, const float k)
{
	mat4 temp;
	for (int i = 0; i < 16; i++)
		temp.m[i] /= k;
	return temp;
}

void mat4::Identity(void)
{
	Null();
	m[0] = m[5] = m[10] = m[15] = 1.0f;
}

void mat4::Rotation(float x, float y, float z)
{
	float A = cosf(x), B = sinf(x), C = cosf(y), D = sinf(y), E = cosf(z),
			 F = sinf(z);
	float AD = A * D, BD = B * D;
	
	Identity();
	
	m[0] = C * E;	m[1] = -C * F;	m[2] = D;
	m[4] = BD * E + A * F;	m[5] = -BD * F + A * E;	m[6] = -B * C;
	m[8] = -AD * E + B * F;	m[9] = AD * F + B * E;	m[10] = A * C;
}

void mat4::Translation(float x, float y, float z)
{
	Identity();
	m[3] = x;
	m[7] = y;
	m[11] = z;
}

void mat4::Scale(float x, float y, float z)
{
	Identity();
	m[0] = x;
	m[5] = y;
	m[10] = z;
}

void mat4::Perspective(float fov, float aspect, float znear, float zfar)
{
	float f = 1.0f / tanf(fov * float(PI) / 360.0f),
	A = (zfar + znear) / (znear - zfar),
	B = (2 * zfar * znear) / (znear - zfar);
	
	Null();
	m[0] = f / aspect;
	m[5] = f;
	m[10] = A;
	m[14] = -1;
	m[11] = B;
}

void mat4::Ortho(float left, float right, float bottom, float top)
{
    Null();
    m[0] = 2.0f / (right - left);
    m[3] = float(-(right + left)) / float(right - left);
    m[5] = 2.0f / (top - bottom);
    m[7] = -float(top + bottom) / float(top - bottom);
    m[10] = -1.0f;
    m[11] = 0.0f;
    m[15] = 1.0f;
}

void mat4::Transpose(void)
{
	mat4 temp;
	temp.Null();
	
	for (int i = 0; i < 4; i++)
		for (int j = 0, k = 4 * i; j < 16; j += 4, k++)
			temp.m[j + i] = m[k];
			
	(*this) = temp;
}

float mat4::Determinant(void) const
{
    float A, B, C, D, E, F;

    A = m[10] * m[15] - m[11] * m[14];
    B = m[9] * m[15] - m[11] * m[13];
    C = m[9] * m[14] - m[10] * m[13];
    D = m[8] * m[15] - m[11] * m[12];
    E = m[8] * m[14] - m[10] * m[12];
    F = m[8] * m[13] - m[9] * m[12];

    return m[0] * (A * m[5] - B * m[6] + C * m[7])
           - m[1] * (A * m[4] - D * m[6] + E * m[7])
           + m[2] * (B * m[4] - D * m[5] + F * m[7])
           - m[3] * (C * m[4] - E * m[5] + F * m[6]);
}

mat4 mat4::Inverse(void) const
{
    float det = 1.0f / Determinant();
    mat4 M;
    

    #define MDET3(a0, a1, a2, a3, a4, a5, a6, a7, a8) \
            ( a0 * (a4 * a8 - a5 * a7) \
            - a1 * (a3 * a8 - a5 * a6) \
            + a2 * (a3 * a7 - a4 * a6) )

    M[0] = MDET3(m[5], m[6], m[7], m[9], m[10], m[11], m[13], m[14], m[15]) *det;
    M[1] = -MDET3(m[1], m[2], m[3], m[9], m[10], m[11], m[13], m[14], m[15]) *det;
    M[2] = MDET3(m[1], m[2], m[3], m[5], m[6], m[7], m[13], m[14], m[15]) *det;
    M[3] = -MDET3(m[1], m[2], m[3], m[5], m[6], m[7], m[9], m[10], m[11]) *det;
    M[4] = -MDET3(m[4], m[6], m[7], m[8], m[10], m[11], m[12], m[14], m[15]) *det;
    M[5] = MDET3(m[0], m[2], m[3], m[8], m[10], m[11], m[12], m[14], m[15]) *det;
    M[6] = -MDET3(m[0], m[2], m[3], m[4], m[6], m[7], m[12], m[14], m[15]) *det;
    M[7] = MDET3(m[0], m[2], m[3], m[4], m[6], m[7], m[8], m[10], m[11]) *det;
    M[8] = MDET3(m[4], m[5], m[7], m[8], m[9], m[11], m[12], m[13], m[15]) *det;
    M[9] = -MDET3(m[0], m[1], m[3], m[8], m[9], m[11], m[12], m[13], m[15]) *det;
    M[10] = MDET3(m[0], m[1], m[3], m[4], m[5], m[7], m[12], m[13], m[15]) *det;
    M[11] = -MDET3(m[0], m[1], m[3], m[4], m[5], m[7], m[8], m[9], m[11]) *det;
    M[12] = -MDET3(m[4], m[5], m[6], m[8], m[9], m[10], m[12], m[13], m[14]) *det;
    M[13] = MDET3(m[0], m[1], m[2], m[8], m[9], m[10], m[12], m[13], m[14]) *det;
    M[14] = -MDET3(m[0], m[1], m[2], m[4], m[5], m[6], m[12], m[13], m[14]) *det;
    M[15] = MDET3(m[0], m[1], m[2], m[4], m[5], m[6], m[8], m[9], m[10]) *det;

    #undef MDET3
    
    return M;
}

#endif