#include "SimpleFunction.h"

std::vector<std::string> explode(std::string STRING,std::string SEPARATOR,std::string WORDSEP,std::string exceptionstart,std::string exceptionend,bool KEEP_SEP,bool KEEP_EMPTY)
{
    std::vector<std::string> RETURN;
    std::string WORD="";bool NEWWORD=false;
    for(int i=0;i<STRING.length();i++)
    {
        NEWWORD=false;
        for(int y=0;y<SEPARATOR.size();y++)
        {
            if(STRING[i]==SEPARATOR[y])
            {
                if(WORD!=""||KEEP_EMPTY){if(KEEP_SEP==true)WORD+=STRING[i];
                            RETURN.push_back(WORD);
                            WORD="";
                            }
                NEWWORD=true;
                break;
            }
        }
        for(int y=0;y<WORDSEP.size();y++)
        {
            if(STRING[i]==WORDSEP[y])
            {
                if(WORD=="")
                {
                    WORD+=STRING[i];
                    RETURN.push_back(WORD);
                    WORD="";
                }
                else
                {
                    RETURN.push_back(WORD);
                    WORD="";
                    WORD+=STRING[i];
                    RETURN.push_back(WORD);
                    WORD="";
                }
                NEWWORD=true;
                break;
            }
        }
        for(int y=0;y<exceptionstart.size();y++)
        {
            if(STRING[i]==exceptionstart[y])
            {
                int boxNumber=0;
                for(;i<STRING.length();i++)
                {
                    bool BREAK=false;
                    for(int u=0;u<exceptionend.size();u++)
                    {
                        if(STRING[i]==exceptionend[u])
                        {
                            if(boxNumber==0)
                            {
                                BREAK=true;
                                break;
                            }
                            else
                            {
                                boxNumber--;
                            }
                        }
                    }
                    for(int i=0;i<exceptionstart.size();i++)
                    {
                        if(STRING[i]==exceptionstart[i])
                        {
                            boxNumber++;
                        }
                    }
                    WORD+=STRING[i];
                    if(BREAK)break;
                }
                NEWWORD=true;
            }
        }
        if(NEWWORD==false)WORD+=STRING[i];

    }
    if(WORD!="")RETURN.push_back(WORD);
    return RETURN;
}
int getRandomNumber(int maxNumber)
{
    return static_cast<int>(rand()*1.00/RAND_MAX*(maxNumber+1)-0.01);
}
int getRandNumBetween(int min,int max)
{
    return static_cast<int>(rand()*1.00/RAND_MAX*(max-min+0.99)+min);
}
