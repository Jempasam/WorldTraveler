#include "Conversion.h"

int StringToInt(std::string STRING)
{
    int RETURN;
    std::stringstream convert;
    convert<<STRING;
    convert>>RETURN;
    return RETURN;

}
std::string IntToString(int INT)
{
    std::string RETURN;
    std::stringstream convert;
    convert<<INT;
    convert>>RETURN;
    return RETURN;

}
std::string intToString(int f_int)
{
    std::string RETURN="";
    int odg=10;//ORDRE DE GRANDEUR;
    if(f_int==0)return "0";
    while(f_int>0)
    {
        RETURN=char((f_int%odg)*10/odg+48)+RETURN;
        f_int-=(f_int%odg);
        odg=odg*10;
    }
    return RETURN;
}
