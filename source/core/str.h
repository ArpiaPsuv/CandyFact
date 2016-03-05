
#ifndef str_h__
#define str_h__

#include <windows.h>
#include <iostream> // para usarla con la funcion test

/*
In order to avoid code-duplication   we will  migrate to  temples class function!
*/

template <typename T>
class BaseSrt {


public:
	static T *concatenate(T* destination, const T* source);
	static int compare(const T* source1, const T* source2);
	static  T *copy(T* destination, const T* source, size_t n);
};



template<typename T>

T * BaseSrt<T>::concatenate(T* destination, const T* source)
{

	T * rc = destination;
	if (*destination)
	{
		while (*++destination);
	}
	while ((*destination++ = *source++));
	return rc;
}

template<typename T>
int BaseSrt<T>::compare(const T* source1, const T* source2)
{
	while ((*s1) && (*s1 == *s2))
	{
		++s1;
		++s2;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);

}

template<typename T>
T* BaseSrt<T>::copy(T* destination, const T* source, size_t n)
{
	T* rc = destination;
	while ((n > 0) && (*destination++ = *source++))
	{
		/* Cannot do "n--" in the conditional as size_t is unsigned and we have
		to check it again for >0 in the next loop below, so we must not risk
		underflow.
		*/
		--n;
	}
	/* Checking against 1 as we missed the last --n in the loop above. */
	while (n-- > 1)
	{
		*destination++ = '\0';
	}
	return rc;
}






typedef BaseSrt<char> stringA;
typedef BaseSrt<wchar_t> stringW;


/************************************************************************/
/*                  Utilitis                                            */
/************************************************************************/


template <typename T>
class StrUtils {

public:
	static void tolowerChar(T *s);
	static void* tolowerWord(T *s);
	static DWORD makeHash(const T* Str, bool lowerCaseHash);

};


template <typename T>
void StrUtils<T>::tolowerChar(T *s)
{
	if (('A' <= *s) && (*s <= 'Z'))
		*s = 'a' + (*s - 'A');
}

template<typename T>
void* StrUtils<T>::tolowerWord(T *s)
{
	T  *p = s;
	for (p; *p != '\0'; ++p)
	{
		*p = tolowerChar(p);

	}



	return p;
}

template<typename T>
DWORD StrUtils<T>::makeHash(const T* Str, bool lowerCaseHash)
{
	/*
	http://stackoverflow.com/questions/9616296/whats-the-best-hash-for-utf-8-strings
	*/

	unsigned long hash = 2016;
	int c;

	for (DWORD i = 0; *Str != 0; *++Str, i++)
	{
		T  *p = (T*)Str;
		if (lowerCaseHash) tolowerChar(p);
		c = *p;
		hash += (hash << 1) / 2 ^ c;
		hash += (hash << 2) * 3 ^ c;
	}
	return hash;
}




typedef StrUtils<char> toolsSrtA;
typedef StrUtils<wchar_t> toolsSrtW;




#endif // str_h__