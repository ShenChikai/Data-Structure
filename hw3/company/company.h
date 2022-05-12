#ifndef COMPANY_HPP
#define COMPANY_HPP

#include <iostream>
#include <fstream>

using namespace std;

struct Company {
  Company *parent;   // the parent company, or nullptr if it has no parent

  Company *merge1, *merge2;

  /* the subcompanies that were merged to obtain this company, or
     nullptr if this is a 1-student company */

  Company ()
  { parent = nullptr; merge1 = nullptr; merge2 = nullptr; }

  Company (Company *m1, Company *m2)
  { parent = nullptr; merge1 = m1; merge2 = m2; }

};

class CompanyTracker {
public:
	CompanyTracker(int n);
	~CompanyTracker();
	void merge(int i, int j);
	void split (int i);
	bool inSameCompany (int i, int j);

private:
	Company **companies; // a pointer to a vector of pointers to company(s)
	int numCompanies;
};

#endif
