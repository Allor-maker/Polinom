#pragma once
#include <iostream>
#include <vector>

class Monom
{
	int k = 0;
	int pow;
public:
	Monom(int k, int pow);

	Monom operator+(const Monom& b) const;
	Monom operator-(const Monom& b) const;
	Monom operator*(const Monom& b) const;
	Monom operator*(const int a) const;
	bool operator==(const Monom& b) const;
	bool operator!=(const Monom& m) const;

	static std::vector<int> get_pows(int i);
	void print() const;
	int get_value() const;
	int get_k() const;
	void set_k(int a);

	friend std::ostream& operator<<(std::ostream& ostr, const Monom& m);
};

#include "list.h"

class Polinom
{	
	List<Monom> l;
public:
	Polinom();
	Polinom(const Polinom& pol);
	Polinom(const Monom& mon);
	Polinom(const std::vector<Monom>& v);
	~Polinom();

	Polinom& operator=(const Polinom& pol);
	void clear();
	size_t size() const;
	Monom operator[](int i) const;
	Polinom operator+(const Polinom& p) const;
	Polinom operator+(const Monom& mon) const;
	Polinom operator-(const Monom& mon) const;
	Polinom operator-(const Polinom& p) const;
	Polinom operator*(const int a) const;
	Polinom operator*(const Monom& m) const;
	Polinom operator*(const Polinom& m) const;

	friend std::ostream& operator<<(std::ostream& ostr, const Polinom& m);
	friend Polinom operator*(const Monom& mon, const Polinom& pol);
	friend Polinom operator+(const Monom& mon, const Polinom& pol);
	friend Polinom operator-(const Monom& mon, const Polinom& pol);
};
