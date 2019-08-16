// Coder.cpp: implementation of the CCoder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CoderV2.h"
#include "..\Utilities\UnscanException.h"

#include <md5/md5checksum.h>
#include "Crc32Dynamic.h"

#include <math.h>
#include <list>
using namespace std;

CCoder* CCoder::m_pInstance=NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCoder::CCoder()
{
	m_strCodeKey="0123456789";
	m_strCodeKey.SetAt(6,'S');
	m_strCodeKey.SetAt(1,'N');
	m_strCodeKey.SetAt(7,'I');
	m_strCodeKey.SetAt(4,'0');
	m_strCodeKey.SetAt(0,'6');
	m_strCodeKey.SetAt(9,'P');
	m_strCodeKey.SetAt(5,'O');
	m_strCodeKey.SetAt(2,'T');
	m_strCodeKey.SetAt(8,'D');
	m_strCodeKey.SetAt(3,'E');
}

CCoder::CCoder(CString strCodeKey)
{
	while(m_strCodeKey.GetLength()<10)
	{
		m_strCodeKey+='0';
	}
	m_strCodeKey.SetAt(6,strCodeKey[0]);
	m_strCodeKey.SetAt(1,strCodeKey[1]);
	m_strCodeKey.SetAt(7,strCodeKey[2]);
	m_strCodeKey.SetAt(4,strCodeKey[3]);
	m_strCodeKey.SetAt(0,strCodeKey[4]);
	m_strCodeKey.SetAt(9,strCodeKey[5]);
	m_strCodeKey.SetAt(5,strCodeKey[6]);
	m_strCodeKey.SetAt(2,strCodeKey[7]);
	m_strCodeKey.SetAt(8,strCodeKey[8]);
	m_strCodeKey.SetAt(3,strCodeKey[9]);
}

CCoder::~CCoder()
{

}

CString CCoder::GetEncodedTimeStamp()
{
	CTime currentTime=CTime::GetCurrentTime();
	CString strDate;
	int year=currentTime.GetYear();
	int month=currentTime.GetMonth();
	int day=currentTime.GetDay();

	int decimal;

	//process year
	for(decimal=1000;decimal>=1;decimal/=10)
		{
		int decimalValue=year/decimal;
		char aChar='0'+decimalValue;
		strDate+=aChar;
		year%=decimal;
		}
	//process month
	for(decimal=10;decimal>=1;decimal/=10)
		{
		int decimalValue=month/decimal;
		char aChar='0'+decimalValue;
		strDate+=aChar;
		month%=decimal;
		}
	//process day
	for(decimal=10;decimal>=1;decimal/=10)
		{
		int decimalValue=day/decimal;
		char aChar='0'+decimalValue;
		strDate+=aChar;
		day%=decimal;
		}

	CString result=getCodedString(strDate,m_strCodeKey);
	return result;

}

CString CCoder::EncodeString(const CString &inString)
{
	CString strUper=inString;
	strUper.MakeUpper();
	CString outString;

	for(int index=0;index<strUper.GetLength();index++)
		{
		char aChar=strUper.GetAt(index);
		char codeChar=GetCodeChar(index);
		char encodedChar=GetEncodedChar(aChar,codeChar);
		outString+=encodedChar;
		}

	return outString;
}

CString CCoder::DecodeString(const CString &inString)
{
	CString strUper=inString;
	strUper.MakeUpper();
	CString outString;

	for(int index=0;index<strUper.GetLength();index++)
		{
		char aChar=strUper.GetAt(index);
		char codeChar=GetCodeChar(index);
		char encodedChar=GetDecodedChar(aChar,codeChar);
		outString+=encodedChar;
		}

	return outString;
}

char CCoder::GetEncodedChar(char aChar, char codeChar) const
{
	int anIndex;
	int aCodeIndex;

	anIndex=(aChar<='9')?aChar-'0':aChar-'A'+10;
	aCodeIndex=(codeChar<='9')?codeChar-'0':codeChar-'A'+10;

	anIndex+=aCodeIndex;
	if(anIndex>35)
		{
		anIndex-=36;
		}
	char resultChar;
	resultChar=(anIndex>9)?anIndex-10+'A':anIndex+'0';

	return resultChar;
}

char CCoder::GetDecodedChar(char aChar, char codeChar) const
{
	int anIndex;
	int aCodeIndex;

	anIndex=(aChar<='9')?aChar-'0':aChar-'A'+10;
	aCodeIndex=(codeChar<='9')?codeChar-'0':codeChar-'A'+10;

	anIndex-=aCodeIndex;
	if(anIndex<0)
		{
		anIndex+=36;
		}
	char resultChar;
	resultChar=(anIndex>9)?anIndex-10+'A':anIndex+'0';

	return resultChar;

}

char CCoder::GetCodeChar(int index)
{
	index=index%(m_strCodeKey.GetLength());
	char result=m_strCodeKey.GetAt(index);
	return result;
}


CTime CCoder::GetDecodedTime(CString strCodedTime)
{
	CString strTime=getDecodedString(strCodedTime,m_strCodeKey);
	int year=0;
	int month=0;
	int day=0;

	int index;

	//--- Get year
	int decimal=1000;
	for(index=0;index<4;index++)
		{
		int digit=strTime.GetAt(index);
		if((digit<'0')||(digit>'9'))
			{
			throw CUnscanException("TimeStamp error : not a digit");
			}
		digit-='0';
		year+=digit*decimal;
		decimal/=10;
		}

	//--- Get Month
	decimal=10;
	for(index=4;index<6;index++)
		{
		int digit=strTime.GetAt(index);
		if((digit<'0')||(digit>'9'))
			{
			throw CUnscanException("TimeStamp error : not a digit");
			}
		digit-='0';
		month+=digit*decimal;
		decimal/=10;
		}
	if(month>12)
		{
			throw CUnscanException("TimeStamp error : month > 12");
		}

	//--- Get day
	decimal=10;
	for(index=6;index<8;index++)
		{
		int digit=strTime.GetAt(index);
		if((digit<'0')||(digit>'9'))
			{
			throw CUnscanException("TimeStamp error : not a digit");
			}
		digit-='0';
		day+=digit*decimal;
		decimal/=10;
		}
	if(day>31)
		{
			throw CUnscanException("TimeStamp error : day > 31");
		}

	CTime time(year,month,day,0,1,1,0);

	return time;
}

// New method used to encode a string. The key is not necessary the internal key
CString CCoder::getCodedString(const CString &inString, const CString &inKey) const
{
	CString strUper=inString;
	strUper.MakeUpper();
	CString outString;

	// classical encoding method
	for(int index=0;index<strUper.GetLength();index++)
		{
		char aChar=strUper.GetAt(index);
		char codeChar=inKey.GetAt(index%(inKey.GetLength()));
		char encodedChar=GetEncodedChar(aChar,codeChar);
		outString+=encodedChar;
		}

	// get the sum of the string
	int sum=0;
	for(index=0;index<strUper.GetLength();index++)
		{
		sum+=getCharValue(outString.GetAt(index));
		}
	sum%=36;
	// shift the string from this value;
	for(index=0;index<strUper.GetLength();index++)
		{
		int newValue=getCharValue(outString.GetAt(index))+sum;
		newValue%=36;
		outString.SetAt(index,getCharFromValue(newValue));
		}
	// add the value in front of the string
	outString.Insert(0,getCharFromValue(sum));
	return outString;

}

CString CCoder::getDecodedString(const CString &inString, const CString &inKey) const
{
	if(inString.GetLength()<2)
		{
		throw CUnscanException("The string to decod is less than two characters long.");
		}

	CString outString;

	// check the consistency, unshift from the sum
	int offset=int(getCharValue(inString.GetAt(0)));
	int index;
	int sum=0;
	for(index=1;index<inString.GetLength();index++)
		{
		int value=getCharValue(inString.GetAt(index));
		value+=36;
		value-=offset;
		value%=36;
		sum+=value;
		outString+=getCharFromValue(value);
		}
	sum%=36;
	if(sum!=offset)
		{
		throw CUnscanException("String encoding error");
		}

	// now decode the string
	for(index=0;index<outString.GetLength();index++)
		{
/*		int value=getCharValue(outString.GetAt(index));
		value+=36;
		value-=getCharValue(inKey.GetAt(index%inKey.GetLength()));
		value%=36;
		outString.SetAt(index,getCharFromValue(value));*/
		char newChar=GetDecodedChar(outString.GetAt(index),inKey.GetAt(index%inKey.GetLength()));
		outString.SetAt(index,newChar);
		}
	return outString;
}

int CCoder::getCharValue(char inChar) const
{
#if defined(_DEBUG)
	bool isNumber=(inChar>='0')&&(inChar<='9');
	bool isLetter=(inChar>='A')&&(inChar<='Z');
	if((!isNumber)&&(!isLetter))
		{
		throw CUnscanException("Invalid value in getCharValue() method.");
		}
#endif	// defined(_DEBUG)

	if((inChar>='0')&&(inChar<='9'))
		{
		return (inChar-'0');
		}
	else
		{
		return (10+inChar-'A');
		}
}

char CCoder::getCharFromValue(int value) const
{
#if defined(_DEBUG)
	if((value<0)||(value>35))
		{
		throw CUnscanException("Invalid value in getCharFromValue() method.");
		}
#endif	// defined(_DEBUG)

	if(value<10)
		{
		return ('0'+value);
		}
	else
		{
		return ('A'+value-10);
		}
}

// fills a vector with first numbers
void CCoder::getFirstNumbers(vector<int>& firstNumberVector,int nNumbers) const
	{
	// fill the first three numbers of the list and set an iterator on the third position.
	firstNumberVector.clear();
	firstNumberVector.reserve(nNumbers);
	firstNumberVector.push_back(1);
	vector<int>::iterator vectBegin=firstNumberVector.begin();
	firstNumberVector.push_back(2);
	vectBegin++;
	firstNumberVector.push_back(3);
	vectBegin++;


	int nCurrent=3;
	while(firstNumberVector.size()<nNumbers)
		{
		nCurrent+=2;

		// It is not necessary to test the numbers greater than the square root
		int square=sqrt(nCurrent);

		bool isDivisible=false;
		vector<int>::iterator iter=(vectBegin);
		while((!isDivisible)&&(*iter<=square)&&(iter!=firstNumberVector.end()))
			{
			isDivisible=(0==(nCurrent%(*iter)) );
			iter++;
			}
		if(!isDivisible)
			{
			firstNumberVector.push_back(nCurrent);
			}
		}
	}

CString CCoder::getRegistrationNumber(CString strSerial, CString strName, CString strCompany)
{
	// concatenate strings, add something between them to avoid equivalences
	CString strConcat=strSerial+CString("CONCAT")+strName+CString("CONCAT")+strCompany;

	//then, clean the string
	int nIndex;
	CString strSum;
	strConcat.MakeUpper();
	for(nIndex=0;nIndex<strConcat.GetLength();nIndex++)
		{
		char cCurrent=strConcat.GetAt(nIndex);
		bool isNumber=((cCurrent>='0')&&(cCurrent<='9'));
		bool isLetter=((cCurrent>='A')&&(cCurrent<='Z'));
		if(isNumber||isLetter)
			{
			strSum+=cCurrent;
			}
		}
	
	// code it, so it will be easy to change the coding
	strSum=getCodedString(strSum,m_strCodeKey);

	// Get a number depending on it
	vector<int> myVector;
	getFirstNumbers(myVector,40);
	int sum=368787;
	for(nIndex=0;nIndex<strSum.GetLength();nIndex++)
		{
		sum*=myVector[getCharValue(strSum.GetAt(nIndex))];
		sum%=10000000;
		}

	CString result;
	result.Format("%d",sum);

	return result;
}

bool CCoder::isRegistrationCodeCorrect(CString strSerial, CString strName, CString strCompany, CString strCode)
{
	m_strCurrentSerial=strSerial;
	m_strCurrentName=strName;
	m_strCurrentCompany=strCompany;
	// spaces are accepted at the beginning and at the end of the string.
	// so remove them before the comparison.


	// Now we can compare (no direct compareason)
	CString strMd5Attempted=GetMd5CodedRegistrationNumber();

	return( strCode==strMd5Attempted );
}

CString CCoder::getCodedString(const CString &inString) const
{
	return getCodedString(inString,m_strCodeKey);
}

CString CCoder::getDecodedString(const CString &inString) const
{
	return getDecodedString(inString,m_strCodeKey);
}

CCoder* CCoder::GetInstance()
{
	if(NULL==m_pInstance)
	{
		m_pInstance=new CCoderV2; // releases >=1.4
	}
	return m_pInstance;
}

CCoder* CCoder::GetInstanceV1(CString strCodeKey)	// used by the generator
{
	delete m_pInstance;
	m_pInstance=new CCoder(strCodeKey);
	return m_pInstance;
}

CCoder* CCoder::GetInstanceV2(CString strCodeKey)	// used by the generator
{
	delete m_pInstance;
	m_pInstance=new CCoderV2(strCodeKey);
	return m_pInstance;
}

void CCoder::Clear()
{
	delete m_pInstance;
	m_pInstance=NULL;
}

CString CCoder::GetMd5CodedRegistrationNumber() 
{
	// concatenate strings, add something between them to avoid equivalences
	CString strConcat=m_strCurrentSerial+CString("CONCAT")+m_strCurrentName+CString("CONCAT")+m_strCurrentCompany;

	//then, clean the string
	int nIndex;
	CString strSum;
	strConcat.MakeUpper();
	for(nIndex=0;nIndex<strConcat.GetLength();nIndex++)
		{
		char cCurrent=strConcat.GetAt(nIndex);
		bool isNumber=((cCurrent>='0')&&(cCurrent<='9'));
		bool isLetter=((cCurrent>='A')&&(cCurrent<='Z'));
		if(isNumber||isLetter)
			{
			strSum+=cCurrent;
			}
		}
	
	// code it, so it will be easy to change the coding
	strSum=getCodedString(strSum,m_strCodeKey);

	// Get a number depending on it
	vector<int> myVector;
	getFirstNumbers(myVector,40);
	int sum=368787;
	for(nIndex=0;nIndex<strSum.GetLength();nIndex++)
		{
		sum*=myVector[getCharValue(strSum.GetAt(nIndex))];
		sum%=10000000;
		}

	CString result;
	result.Format("%d",sum);
	CString strMd5codedResult=CMD5Checksum::GetMD5((BYTE*)(LPCSTR)result,result.GetLength());

	return strMd5codedResult;		
}

CString CCoder::Strip(const CString &string) const
{
	CString result=string;
	while( (result.GetLength()>0)&&(' '==result.GetAt(0)) )
	{
		result.Delete(0,1);
	}
	while((result.GetLength()>0)&&(' '==result.GetAt(result.GetLength()-1)))
	{
		result.Delete(result.GetLength()-1,1);
	}
	return result;
}

CString CCoder::GetCheckSumValue(const char *filename)
{
	DWORD nValue;
	CCrc32Dynamic crc;
	crc.FileCrc32Streams(filename,nValue);
	char buffer[256];
	sprintf(buffer,"%u",nValue);
	CString strTemp(buffer);
	CString strResult=CMD5Checksum::GetMD5((BYTE*)(LPCSTR)strTemp,strTemp.GetLength());
	return strResult;
}

CString CCoder::GetDataScramblingValue(const char *filename)
{
	DWORD nValue;
	CCrc32Dynamic crc;
	crc.FileCrc32Streams(filename,nValue);
	nValue ^= 42717296;
	char buffer[256];
	sprintf(buffer,"%u",nValue);
	CString strTemp(buffer);
	CString strResult=CMD5Checksum::GetMD5((BYTE*)(LPCSTR)strTemp,strTemp.GetLength());
	return strResult;
}
