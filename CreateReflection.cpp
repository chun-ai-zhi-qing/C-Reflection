#include <fstream>
#include <vector>
#include <iostream>
std::string head = "#ifndef _Create_Reflection_CPP_\n#define _Create_Reflection_CPP_\n"; 
std::string classTextStart = "class Reflect\n\
{\n\
public:\n\
    void * CreateClassInfo(std::string name)\n\
    {\n";
std::string classTextEnd = "\n    }\n\
};\n\
    \n\n#endif";
void CreateText(std::string TextInfo,std::string findText,std::vector<std::string>& Info)
{
    std::string tmp = "",endFindText = findText;
    endFindText.insert(1,1,'/');
    while(TextInfo.find(findText)!=std::string::npos)
    {   
        size_t startindex= TextInfo.find(findText);
        startindex=findText.size()+startindex;
        int endindex = startindex;
        while(TextInfo[endindex]!='<') endindex++;
        tmp = TextInfo.substr(startindex,endindex - startindex);
        //int x = TextInfo.find("</ClassName>")-1;
        int x = TextInfo.find(endFindText);
        TextInfo = TextInfo.substr(TextInfo.find(endFindText)+endFindText.size());
        Info.push_back(tmp);
    }
}
int main()
{
    std::fstream XMLFile,CreateReflectionFileStream;
    std::vector<std::string> includeInfo,ClassNameInfo;
    std::string TextInfo;
    XMLFile.open("config.xml",std::ios::in);
    std::string tmp;
    while(!XMLFile.eof())
    {
        XMLFile >> tmp;
        TextInfo+=tmp;
    }
    XMLFile.close();

    CreateReflectionFileStream.open("Reflection.h",std::ios::out);
    CreateText(TextInfo,"<ClassName>",ClassNameInfo);
    CreateText(TextInfo,"<IncludeInfo>",includeInfo);
    
    CreateReflectionFileStream<<head;
    CreateReflectionFileStream<<"#include<iostream>"<<std::endl;
    
    for (size_t i = 0; i < includeInfo.size(); i++)
        CreateReflectionFileStream<<"#include\""<<includeInfo[i]<<"\""<<std::endl;
    CreateReflectionFileStream<<classTextStart;
    for (size_t i = 0; i < ClassNameInfo.size(); i++)
        CreateReflectionFileStream<<"\t\tif(name==\""<<ClassNameInfo[i]<<"\") return new "<<ClassNameInfo[i]<<"();"<<std::endl;
    
    CreateReflectionFileStream<<classTextEnd;
    CreateReflectionFileStream.close();
}
