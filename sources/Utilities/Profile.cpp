/////////////////////////////////////////////////////////////////
// Profile.cpp

#include "stdafx.h"

#include "Profile.h"

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

#include <iostream>
#include <fstream>
using namespace std;

#include "RegularExpressions.h"
#include "Tokenizer.h"


size_t getAllSectionNames(char *returnedString,
						  size_t capacity,
						  const char * fileName)
{
	ifstream iniFile(fileName, ios::in);
	CString listSectionNames;
	char buffer[1024];

	if (iniFile.is_open())
	{

		while (!iniFile.eof())
		{
			iniFile.getline(buffer,1024);
			CString currentLine=buffer;
			if (!currentLine.IsEmpty())
			{
//				RWCTokenizer field(currentLine);

				// Looking for ...[sectionName]...
				if (RegIsMatching(currentLine, "^[ \\t]*\\[.+\\]"))
				{
					// Add section name to list of section names
					CString currentSection = RegMatch(currentLine, "\\[.+\\]");
					currentSection = currentSection.Mid(1, currentSection.GetLength()-2);
					listSectionNames += currentSection + CString("\0");
				}
			} // if currentLine.isNull
		} // while !eof

		iniFile.close();
	} // if iniFile.isOpen

	listSectionNames += "\0";
	if (listSectionNames.GetLength() > capacity)
	{
		listSectionNames = listSectionNames.Mid(0, capacity-2);
		listSectionNames += "\0\0";
	}
	memcpy(returnedString, LPCTSTR(listSectionNames), listSectionNames.GetLength());
	return listSectionNames.GetLength();
}


size_t getAllEntryNames(const char *sectionName,
						char *returnedString,
						size_t capacity,
						const char * fileName)
{
	CString sectionStr(sectionName);
	sectionStr.MakeLower();
	CString listEntryNames;
	char buffer[1024];

	ifstream iniFile(fileName, ios::in);

	if (iniFile.is_open())
	{
		bool sectionFound=false;

		while (!iniFile.eof())
		{
			iniFile.getline(buffer,1024);
			CString currentLine=buffer;
			if (!currentLine.IsEmpty())
			{
				CTokenizer field(currentLine);

				// Looking for ...[sectionName]...
				if (RegIsMatching(currentLine, "^[ \\t]*\\[.+\\]"))
				{
					if (sectionFound)
						// Moving to a different section
						// ==> stop collecting entry names
						sectionFound = false;
					else
					{
						CString currentSection = RegMatch(currentLine,
																  "\\[.+\\]");
						currentSection = currentSection.Mid(1, currentSection.GetLength()-2);
						currentSection.MakeLower();
						if (currentSection == sectionStr)
							sectionFound = true;
					}
				}
				else
				{
					if (sectionFound)
					{
						// Get all the entry names for current section
						CString readField	= field("=");
						removeTrailingBlanks(readField);
						listEntryNames += readField + CString("\0");
					}
				}
			} // if currentLine.isNull
		} // while !eof

		iniFile.close();
	} // if iniFile.isOpen

	listEntryNames += "\0";
	if (listEntryNames.GetLength() > capacity)
	{
		listEntryNames = listEntryNames.Mid(0, capacity-2);
		listEntryNames += "\0\0";
	}
	memcpy(returnedString, listEntryNames, listEntryNames.GetLength());
	return listEntryNames.GetLength();
}


size_t GetProfileString(const char *sectionName,
							   const char *entryName,
							   const char *defaultValue,
							   char *returnedString,
							   size_t capacity,
							   const char * fileName)
{
	CString sectionStr(sectionName);
	sectionStr.MakeLower();
	CString keyStr(entryName);
	keyStr.MakeLower();
	CString keyValue;
	char buffer[1024];

	memset((void*)returnedString, 0, capacity);

	if (sectionStr == "")
		// Retrieve all the section names
		return getAllSectionNames(returnedString, capacity, fileName);

	if (keyStr == "")
		// Retrieve all the entry names
		return getAllEntryNames(sectionName, returnedString, capacity, fileName);

	ifstream iniFile(fileName, ios::in);

	if (iniFile.is_open())
	{
		bool sectionFound=false;
		bool keyFound=false;

		while (!iniFile.eof() && !keyFound)
		{
//			currentLine.readLine(iniFile, FALSE);
			iniFile.getline(buffer,1024);
			CString currentLine=buffer;
			if (!currentLine.IsEmpty())
			{
				CTokenizer field(currentLine);

				// Looking for ...[sectionName]...
				if (RegIsMatching(currentLine, "^[ \\t]*\\[.+\\]"))
				{
					if (sectionFound)
						keyFound = true; // the key looked for is not in the section
					else
					{
						CString currentSection = RegMatch(currentLine,
																  "\\[.+\\]");
						currentSection = currentSection.Mid(1, currentSection.GetLength()-2);
						currentSection.MakeLower();
						if (currentSection == sectionStr)
							sectionFound = true;
					}
				}
				else
				{
					if (sectionFound)
					{
						CString readField	= field("=");
						readField.MakeLower();
						removeTrailingBlanks(readField);

						if (readField == keyStr)
						{
							keyValue = field("=");
							removeTrailingBlanks(keyValue);
							if (keyValue[0] == '"')
								keyValue = keyValue.Mid(1, keyValue.GetLength()-2);

							keyFound = true;
						}
					}
				}
			} // if currentLine.isNull
		} // while !eof

		iniFile.close();
	} // if iniFile.isOpen

	sprintf(returnedString, "%s", keyValue);
	return keyValue.GetLength();
}


size_t GetProfileInt (const char *sectionName,
			    const char *entryName,
			    int defaultValue,
			    const char * fileName)
{
	char integerAsString[1024];
	memset(integerAsString, 0, sizeof(integerAsString));

	int size = GetProfileString(sectionName, entryName, "", integerAsString, sizeof(integerAsString), fileName);

	CString integerStr(integerAsString);

	int res=defaultValue;
	if (integerStr!="")
		res = atoi(integerAsString);

	return res;
}

bool WriteProfileString(const char *sectionName,
			       const char *entryName,
			       const char *value,
			       const char * fileName)
{

	bool isWritten=false;
	CString sectionStr(sectionName);
	CString strEntry(entryName);
	removeTrailingBlanks(strEntry);
//	CString keyValue;
	CString updatedFileName=fileName+CString('_');
	char buffer[2048];

	ifstream iniFile(fileName, ios::in);
	ofstream updatedIniFile(updatedFileName);

	if( (iniFile.is_open()) && (updatedIniFile.is_open()) )
	{
		bool sectionFound=false;
		bool sectionPassed=false;

		CString previousLine;
		while (!iniFile.eof() && (!isWritten) && (!sectionPassed))
		{
			iniFile.getline(buffer,2048);
			CString currentLine=buffer;

			// try to find the section
			if( (!sectionFound) && 
				(!currentLine.IsEmpty()) &&
				(RegIsMatching(currentLine, "^[ \\t]*\\[.+\\]")) )	
			{
				CString currentSection=RegMatch(currentLine,"\\[.+\\]");
				currentSection=currentSection.Mid(1,currentSection.GetLength()-2);

				if (currentSection==CString(sectionName))
				{
					sectionFound = true;
				}
			}
			// try to find entry
			else if ( sectionFound && (!currentLine.IsEmpty()) ) 
			{
				CString currentEntry;
				if(RegIsMatching(currentLine, "^[ \\t]*\\[.+\\]"))	// its an other section
				{
					sectionPassed=true;
				}
				else if(!(currentEntry=RegMatch(currentLine,"^.+=")).IsEmpty())	// its an entry
				{
					currentEntry=currentEntry.Left(currentEntry.GetLength()-1);	// remove '='
					removeTrailingBlanks(currentEntry);
					if(currentEntry==strEntry)
					{
						currentLine=CString(strEntry)+CString("=")+CString(value);
						isWritten=true;
					}
				}
			}

			updatedIniFile<<LPCTSTR(currentLine)<<endl;
		} 

		while(!iniFile.eof())
		{
			iniFile.getline(buffer,2048);
			updatedIniFile<<buffer<<endl;
		}
		

		iniFile.close();
		updatedIniFile.close();

		if(isWritten)
		{
			// remove current INI file
			remove(fileName);
			// rename updated INI file
			rename(updatedFileName, fileName);
		}

	} // if iniFile.isOpen

	return isWritten;
}



//-----------------------------------------------------------------------
// Removes beginning and ending blanks of a string: space and tab characters for instance
// Arguments:
// strLine: string to clean up
// strBlanks (optional): string containing all the blanks characters. Default value: " \t"
//-----------------------------------------------------------------------
void removeTrailingBlanks(CString &strLine,
						  const CString& strBlanks /*=CString(" \t")*/)
{
	// get beginning
	int firstNonNull=0;
	while( (firstNonNull<strLine.GetLength())
		&&( -1!=strBlanks.Find(strLine[firstNonNull])) )
	{
		firstNonNull++;
	}

	// get ending;
	int lastNonNull=strLine.GetLength()-1;
	while( (lastNonNull>firstNonNull)
		&&( -1!=strBlanks.Find(strLine[lastNonNull])) )
	{
		lastNonNull--;
	}

	// cut
	strLine=strLine.Mid(firstNonNull,lastNonNull-firstNonNull+1);
}
