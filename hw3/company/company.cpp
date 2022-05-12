#include "company.h"

CompanyTracker::CompanyTracker (int n)
  // initializes the tracker with n students and their 1-person companies
{
  numCompanies = n;
  companies = new Company* [numCompanies];
  for (int i = 0; i < numCompanies; ++i)
      companies[i] = new Company ();
}

CompanyTracker::~CompanyTracker ()
  // deallocates all dynamically allocated memory
{
  Company *p, *q;
  for (int i = 0; i < numCompanies; ++i) {
    p = companies[i];
    while(p->parent != nullptr) {
      q = p->parent;
      delete p;
      p = q;
    }
  }
}

void CompanyTracker::merge (int i, int j)
  /* Merges the largest companies containing students i and j,
     according to the rules described above.
     That is, it generates a new Company object which will
     become the parent company of the largest companies currently
     containing students i and j.
     If i and j already belong to the same company (or are the same),
     merge doesn't do anything.
     If either i or j are out of range, merge doesn't do anything. */
{
  if (i > numCompanies || j > numCompanies) return;  // OUT OF RANGE

  if (inSameCompany(i, j)) return;                   // i and j in same company

  Company *p;                  // go to the biggest Company of j
  p = companies[i];
  while (p->parent != nullptr) {
    p = p->parent;
  }

  Company *q;                  // go to the biggest Company of j
  q = companies[j];
  while (q->parent != nullptr) {
    q = q->parent;
  }

  p->parent = new Company(p, q);  // make the new parent company
  q->parent = p->parent;
}

void CompanyTracker::split (int i)
  /* Splits the largest company that student i belongs to,
     according to the rules described above.
     That is, it deletes that Company object, and makes sure that
     the two subcompanies have no parent afterwards.
     If i's largest company is a 1-person company, split doesn't do anything.
     If i is out of range, split doesn't do anything. */
{
  if (i > numCompanies) return;               // OUT OF RANGE

  if (companies[i]->parent == nullptr) return;   // i is a 1-student Company

  Company *p;                  // go to the biggest Company of j
  p = companies[i];
  while (p->parent != nullptr) {
    p = p->parent;
  }

  Company *m1, *m2;       // assign m1, m2 to the 2 children of parent p
  m1 = p->merge1;
  m2 = p->merge2;

  m1->parent = nullptr;    // disconnect children from the parent, LOL
  m2->parent = nullptr;
  p->merge1 = nullptr;
  p->merge2 = nullptr;
}

bool CompanyTracker::inSameCompany (int i, int j)
  /* Returns whether students i and j are currently in the same company.
     Returns true if i==j.
     Returns false if i or j (or both) is out of range. */
{
  if (i == j) return true;     // i == j

  if (i > numCompanies || i < 0 || j > numCompanies || j < 0) return false; // OUT OF RANGE

  if (companies[i]->parent == nullptr && companies[j]->parent == nullptr) return false;

  Company *p;                  // go to the biggest Company of j
  p = companies[i];
  while (p->parent != nullptr) {
    p = p->parent;
  }

  Company *q;                  // go to the biggest Company of j
  q = companies[j];
  while (q->parent != nullptr) {
    q = q->parent;
  }

  if (p == q) {
    return true;
  } else {
    return false;
  }
}

