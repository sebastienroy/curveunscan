///////////////////////////////////////////////////////////
// RegularExpressions.h

#if !defined(_REGULARESPRESSIONS_H_)
#define _REGULARESPRESSIONS_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"

/*

^	Beginning of the string. The expression "^A" will match an ‘A’ only at the beginning of
	the string.
 
^	The caret (^) immediately following the left-bracket ([) has a different meaning.
	It is used to exclude the remaining characters within brackets from matching the 
	target string. The expression "[^0-9]" indicates that the target character should
	not be a digit.
 
$	The dollar sign ($) will match the end of the string. The expression "abc$" will
	match the sub-string "abc" only if it is at the end of the string.
 
|	The alternation character (|) allows either expression on its side to match the
	target string. The expression "a|b" will match ‘a’ as well as ‘b’.
 
.	The dot (.) will match any character.
 
*	The asterix (*) indicates that the character to the left of the asterix in the
	expression should match 0 or more times.
 
+	The plus (+) is similar to asterix but there should be at least one match of the
	character to the left of the + sign in the expression.
 
?	The question mark (?) matches the character to its left 0 or 1 times.
 
()	The parenthesis affects the order of pattern evaluation and also serves as a tagged
	expression that can be used when replacing the matched sub-string with another expression.
 
[]	Brackets ([ and ]) enclosing a set of characters indicates that any of the enclosed
	characters may match the target character.
 
*/

int RegSearchReplace( CString& string, LPCTSTR sSearchExp, 
					 LPCTSTR sReplaceExp );

bool RegSearchReplaceOnce( CString& string, LPCTSTR sSearchExp, 
					 LPCTSTR sReplaceExp );

bool StringReplace(CString& string, int nOffset, int nLength, LPCSTR pReplaceStr);

bool RegIsMatching(LPCTSTR string, LPCTSTR sSearchExp);

CString RegMatch(LPCTSTR string, LPCTSTR sSearchExp);



#endif // !defined(_REGULARESPRESSIONS_H_)