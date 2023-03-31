#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

class Poly {
  private:
	double* ptr;
	int size;
	
	void changesize(int index)
	{
		if (index >= size) {
			double* newptr =
				(double*)realloc(this->ptr, (index + 1) * sizeof(double));
			if (!newptr)
				exit(8);
			this->ptr = newptr;
			for (int i = size; i <= index; i++) {
				this->ptr[i] = 0;
			}
			size = index + 1;
		}
	}

  public:
	Poly(double value = 0)
	{
		size = 1;
		ptr = (double*)malloc(sizeof(double));
		ptr[0] = value;
	};
	Poly(const Poly& p)
	{
		size = p.size;
		ptr = (double*)malloc(size * sizeof(double));
		for (int i = 0; i < p.size; i++) {
			ptr[i] = p.ptr[i];
		}
	};

	Poly operator-() const
	{
		Poly result;
		for (int i = 0; i < this->size; i++) {
            result[i] = -this->ptr[i];
		}
        result.size = this->size;
		return result;
	};

	double& operator[](int index)
	{
		if (index >= size) {
			this->changesize(index);
		}
		return this->ptr[index];
	}
	double operator()(double value) const
	{
		double result = 0;
		for (int i = 0; i < this->size; i++) {
            result += this->ptr[i] * pow(value, i);
		}
		return result;
	}

	Poly& operator=(const Poly& p1)
	{
		double* newptr = (double*)realloc(this->ptr, p1.size * sizeof(double));
		if (!newptr)
			exit(8);
		this->ptr = newptr;
		for (int i = 0; i < p1.size; i++) {
			this->ptr[i] = p1.ptr[i];
		}
		this->size = p1.size;
		return *this;
	}

	Poly operator+(const Poly& p) const
	{
		Poly result;
		int i;
		if (this->size > p.size) {
			for (i = 0; i < p.size; i++) {
                result[i] = this->ptr[i] + p.ptr[i];
			}
			for (; i < this->size; i++) {
                result[i] = this->ptr[i];
			}
		}
		else {
			for (i = 0; i < this->size; i++) {
                result[i] = this->ptr[i] + p.ptr[i];
			}
			for (; i < p.size; i++) {
                result[i] = p.ptr[i];
			}
		}

		return result;
	}
	Poly operator-(const Poly& p) const
	{
		Poly result;
		int i;
		if (this->size > p.size) {
			for (i = 0; i < p.size; i++) {
                result[i] = this->ptr[i] - p.ptr[i];
			}
			for (; i < this->size; i++) {
                result[i] = this->ptr[i];
			}
		}
		else {
			for (i = 0; i < this->size; i++) {
                result[i] = this->ptr[i] - p.ptr[i];
			}
			for (; i < p.size; i++) {
                result[i] = -p.ptr[i];
			}
		}
		return result;
	}
	Poly operator*(const Poly& p1) const
	{
		Poly result;
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < p1.size; j++) {
                result[i + j] += this->ptr[i] * p1.ptr[j];
			}
		}
		return result;
	}

	friend ostream& operator<<(ostream& outs, const Poly& poly)
	{
		int i;
		int ch = 0;
		for (i = poly.size - 1; i >= 0; i--) {
			if ((poly.ptr[i] != 0) && (i == 0)) {
				if (poly.ptr[i] < 0) {
					outs << " - ";
				}
				if (poly.ptr[i] > 0) {
					outs << " + ";
				}
				outs << abs(poly.ptr[i]);
				ch = 1;
			}
			else if ((poly.ptr[i] != 0) && (i == 1)) {
				if (poly.ptr[i] < 0) {
					outs << " - ";
				}
				if (poly.ptr[i] > 0) {
					outs << " + ";
				}
				ch = 1;
				outs << abs(poly.ptr[i]) << "x";
			}
			else if ((poly.ptr[i] != 0) && i == poly.size - 1) {
				if (abs(poly.ptr[i]) != 1) {
					outs << poly.ptr[i] << "x^" << i;
				}
				else {
					if (poly.ptr[i] < 0)
						outs << "-";
					outs << "x^" << i;
				}
				ch = 1;
			}
			else if ((poly.ptr[i] != 0) && i > 1) {
				if (poly.ptr[i] < 0) {
					outs << " - ";
				}
				if (poly.ptr[i] > 0) {
					outs << " + ";
				}
				if (abs(poly.ptr[i]) != 1) {
					outs << abs(poly.ptr[i]);
				}
				ch = 1;
				outs << "x^" << i;
			}
		}
		if (ch == 0)
			outs << "0";
		return outs;
	}
	~Poly()
	{
		free(this->ptr);
	}
};

inline Poly operator+(const double d1, const Poly& p1)
{
	Poly result;
    result = p1 + d1;
	return result;
}
inline Poly operator-(const double d1, const Poly& p1)
{
	Poly result;
    result = (-p1) + d1;
	return result;
}
inline Poly operator*(const double d1, const Poly& p1)
{
	Poly result;
    result = p1 * d1;
	return result;
}
