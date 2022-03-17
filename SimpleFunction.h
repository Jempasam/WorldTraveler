#ifndef SIMPLEFUNCTION_H
#define SIMPLEFUNCTION_H

#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>

#define ret_cast reinterpret_cast
#define repeat(VAR,NUM) for(int VAR=NUM; VAR>=0; VAR--)

std::vector<std::string> explode(std::string STRING,std::string SEPARATOR,std::string WORDSEP="",std::string exceptionstart="",std::string exceptionend="",bool KEEP_SEP=false,bool KEEP_EMPTY=true);
int getRandomNumber(int maxNumber);
int getRandNumBetween(int min,int max);

template<typename T> constexpr T getRandEnum()
{
    return static_cast<T>(rand()%static_cast<int>(T::TOP));
}
template<typename T> constexpr T getRandElem(const std::vector<T> &vec)
{
    return vec[rand()%vec.size()];
}

#endif // SIMPLEFUNCTION_H
