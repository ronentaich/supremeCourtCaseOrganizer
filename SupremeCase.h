// Specification file for the Supreme court case class

#ifndef CASE_H
#define CASE_H
#include <iostream>

using std::string;

class Case
{
private:
    string caseCitation;
    string caseName;
    string chiefJustice;
    string opWriter;
    int year;
public:
    Case();
    Case(string c);
    Case(string c, string n, string j, string o, int year);
    
    // Setters
    void setCaseCitation(string cC) { caseCitation = cC; }
    void setName(string cN) { caseName = cN; }
    void setChiefJustice(string cJ) { chiefJustice = cJ; }
    void setOpWriter(string oW) {opWriter = oW; }
    void setYear(int y) { year = y; }
    
    // Getters
    string getCaseCitation() const { return caseCitation; }
    string getName() const {return caseName; }
    string getChiefJustice() const {return chiefJustice; }
    string getOpWriter() const { return opWriter; }
    int getYear() const { return year; }

    // Stream operator
    friend std::ostream& operator << (std::ostream&, const Case&);

    // Compare citation
    bool operator <(const Case&) const;
    bool operator >(const Case&) const;
    bool operator ==(const Case&) const;
    bool operator = (Case*);

    // Object conversion to string
    operator string() { return caseCitation; }
};

#endif
