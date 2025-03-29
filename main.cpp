#include "main.h"
#include "deflib/deflib.h"

void Program::Main(StringArray args) {
    Time t = Time::Now();

    DefCon::PrintLine("C-Style way of displaying time:");
    DefCon::PrintLine(Cvt::ToString(t));

    DefCon::PrintLine("Correct way of displaying time:");
    DefCon::PrintLine(Cvt::ToString(t, "dd.MM.yyyy HH:mm:ss\n"));

    DefCon::PrintLine("American way of displaying time:");
    DefCon::PrintLine(Cvt::ToString(t, "MM/dd/yyyy hh:mm tt\n"));

    DefCon::PrintLine("Verbose way:");
    StringArray suffixes = { "st", "nd", "rd" };
    string s;
    int i = t.day() % 10;
    if(i >= 1 && i <= 3) s = suffixes[i - 1];
    else s = "th";
    DefCon::PrintLine(Cvt::ToString(t, "dddd") + Cvt::ToString(t, ", ddxx of MMMM yyyy").replace("xx", s));
}



