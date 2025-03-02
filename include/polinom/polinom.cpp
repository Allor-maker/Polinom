#include "polinom.h"

//Monom
Monom::Monom(int k = 0, int pow = 0) :k(k), pow(pow) {}
Monom Monom::operator+(const Monom& b) const
{
	if (pow != b.pow) throw 0;

	Monom c(k + b.k, pow);
	return c;
}
Monom Monom::operator-(const Monom& b) const
{
	if (pow != b.pow) throw 0;

	Monom c(k - b.k, pow);
	return c;
}
std::vector<int> Monom::get_pows(int i)
{
	int i1 = i / 100;
	int i2 = (i / 10) % 10;
	int i3 = i % 10;

	std::vector<int> v = { i1,i2,i3 };
	return v;
}
Monom Monom::operator*(const Monom& b) const
{
	std::vector<int> v1 = get_pows(pow);
	std::vector<int> v2 = get_pows(b.pow);
	if (v1[0] + v2[0] > 9 || v1[1] + v2[1] > 9 || v1[2] + v2[2] > 9) throw 0;

	int pow2 = pow + b.pow;
	Monom c(k * b.k, pow2);

	return c;
}
Monom Monom::operator*(const int a) const
{
	Monom m(k * a, pow);
	return m;
}
bool Monom::operator==(const Monom& b) const
{
	if (pow == b.pow && k == b.k) return true;
	return false;
}
bool Monom::operator!=(const Monom& m) const
{
	return !(*this == m);
}
void Monom::print() const
{
	std::cout << pow << std::endl;
}
int Monom::get_value() const
{
	return pow;
}
int Monom::get_k() const
{
	return k;
}
void Monom::set_k(int a)
{
	k = a;
}
std::ostream& operator<<(std::ostream& ostr, const Monom& m)
{
	ostr << "k = " << m.get_k() << std::endl;
	ostr << "pow = " << m.get_value() << std::endl;

	return ostr;
}
//Polinom

Polinom::Polinom() {}
Polinom::Polinom(const Polinom& pol)
{
	l = pol.l;
}
Polinom::Polinom(const Monom& mon)
{
	l.insert_front(mon);
}
Polinom::Polinom(const std::vector<Monom>& v)
{
	for (Monom m : v)
	{
		*this = operator+(m);
	}
}
Polinom::~Polinom() {}
Polinom& Polinom::operator=(const Polinom& pol)
{
	if (this == &pol) return *this;
	clear();
	l = pol.l;
	return *this;
}
void Polinom::clear()
{
	l.clear();
}
size_t Polinom::size() const
{
	return l.size();
}
Monom Polinom::operator[](int i) const
{
	return l[i];
}
Polinom Polinom::operator+(const Polinom& p) const
{
	Polinom pol;
	List<Monom>::Iterator curr3 = pol.l.end();
	List<Monom>::Iterator curr1 = l.begin();
	List<Monom>::Iterator curr2 = p.l.begin();

	while (curr1 != l.end() && curr2 != p.l.end())
	{
		if (l[curr1].get_value() < p.l[curr2].get_value())
		{
			pol.l.insert_after(l[curr1], curr3.get_curr());
			curr1++;
		}
		else if (l[curr1].get_value() == p.l[curr2].get_value())
		{
			if (l[curr1].get_k() + p.l[curr2].get_k() != 0)
			{
				pol.l.insert_after(l[curr1] + p.l[curr2], curr3.get_curr());
			}

			curr1++;
			curr2++;
		}
		else
		{
			pol.l.insert_after(p.l[curr2], curr3.get_curr());
			curr2++;
		}
		curr3++;
	}
	while (curr1 != l.end())
	{
		pol.l.insert_after(l[curr1], curr3.get_curr());
		curr1++;
		curr3++;
	}
	while (curr2 != p.l.end())
	{
		pol.l.insert_after(p.l[curr2], curr3.get_curr());
		curr2++;
		curr3++;
	}
	return pol;
}
Polinom Polinom::operator+(const Monom& mon) const
{
	Polinom curr(mon);
	Polinom pol = operator+(curr);

	return pol;
}
Polinom Polinom::operator-(const Monom& mon) const
{
	Polinom curr(mon);
	Polinom pol = operator-(curr);
	return pol;
}

Polinom Polinom::operator-(const Polinom& p) const
{
	Polinom pol;
	List<Monom>::Iterator curr3 = pol.l.end();
	List<Monom>::Iterator curr1 = l.begin();
	List<Monom>::Iterator curr2 = p.l.begin();

	while (curr1 != l.end() && curr2 != p.l.end())
	{
		if (l[curr1].get_value() < p.l[curr2].get_value())
		{
			pol.l.insert_after(l[curr1], curr3.get_curr());
			curr1++;
		}
		else if (l[curr1].get_value() == p.l[curr2].get_value())
		{
			pol.l.insert_after(l[curr1] - p.l[curr2], curr3.get_curr());
			curr1++;
			curr2++;
		}
		else
		{
			pol.l.insert_after(p.l[curr2] * (-1), curr3.get_curr());
			curr2++;
		}
		curr3++;
	}
	while (curr1 != l.end())
	{
		pol.l.insert_after(l[curr1], curr3.get_curr());
		curr1++;
		curr3++;
	}
	while (curr2 != p.l.end())
	{
		pol.l.insert_after(p.l[curr2] * (-1), curr3.get_curr());
		curr2++;
		curr3++;
	}
	return pol;

}

Polinom Polinom::operator*(const int a) const
{
	Polinom pol;
	List<Monom>::Iterator curr_pol = pol.l.end();
	List<Monom>::Iterator curr = l.begin();

	while (curr != l.end())
	{
		pol.l.insert_after(l[curr] * a, curr_pol.get_curr());
		curr++;
	}
	return pol;
}
Polinom Polinom::operator*(const Monom& m) const
{
	Polinom cur(m);
	Polinom pol = operator*(cur);
	return pol;
}
	
Polinom Polinom::operator*(const Polinom& p) const
{
	Polinom pol;
	List<Monom>::Iterator curr = pol.l.end();
	List<Monom>::Iterator curr1 = l.begin();


	while (curr1 != l.end())
	{
		List<Monom>::Iterator curr2 = p.l.begin();
		while (curr2 != p.l.end())
		{
			pol.l.insert_after(l[curr1] * p.l[curr2], curr.get_curr());
			curr2++;
		}
		curr1++;
	}

	List<Monom>::Iterator first = pol.l.begin();
	List<Monom>::Iterator last = pol.l.end();

	pol.l.sort();
	pol.l.del_similar();

	return pol;
}
std::ostream& operator<<(std::ostream& ostr, const Polinom& m)
{

	for (List<Monom>::Iterator it = m.l.begin(); it != m.l.end(); it++)
	{
		ostr << "k = " << (*it).get_k() << " ";
		ostr << "pow = " << (*it).get_value() << std::endl;
	}
	return ostr;
}
Polinom operator*(const Monom& mon, const Polinom& pol)
{
	return pol * mon;
}
Polinom operator+(const Monom& mon, const Polinom& pol)
{
	return pol + mon;
}
Polinom operator-(const Monom& mon, const Polinom& pol)
{
	Polinom p(mon);
	Polinom pol_res = p - pol;
	return pol_res;
}
