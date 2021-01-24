#include "SupremeCase.h"

Case::Case()
{
    year = -1;
}

Case::Case(string c)
{
    caseCitation = c;
    year = -2;
}


Case::Case(string c, string n, string j, string o, int y)
{
    caseCitation = c;
    caseName = n;
    chiefJustice = j;
    opWriter = o;
    year = y;
}

bool Case::operator<(const Case& right) const
{
    if (this->caseCitation < right.getCaseCitation())
        return true;
    return false;
}

bool Case::operator>(const Case& right) const
{
    if (this->caseCitation > right.getCaseCitation())
        return true;
    return false;
}

bool Case::operator==(const Case& right) const
{
    if (this->caseCitation == right.getCaseCitation())
        return true;
    return false;
}

// Overloaded << operator outputs contents of the Case to the stream (designed to write to file)
std::ostream& operator<<(std::ostream& stream, const Case& c)
{
    stream << c.caseCitation << std::endl << c.caseName << std::endl << c.chiefJustice << std::endl
        << c.opWriter << std::endl << c.year << std::endl;
    return stream;
}

bool Case::operator = (Case* right)
{
    if (!right)
        return false;

    this->caseCitation = right->getCaseCitation();
    this->caseName = right->getName();
    this->chiefJustice = right->getChiefJustice();
    this->year = right->getYear();
    this->opWriter = right->getOpWriter();
    return true;

}
