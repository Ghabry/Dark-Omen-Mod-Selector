#include "header.h"


void SkipWhiteSpaceAndComments( char*& str ){
	for(;;){
		while( *str == '\x20' || *str == '\x09' ) str++; // skip white space
		if( str[0] == '/' ){
			if( str[1] == '/' ) for( str+=2; ( *str != '\r' && *str != '\n' && *str != '\0' ); str++ ); // skip line comment
		}
		else break;
	}
}	

// ascii to unsigned long
// hex or decimal notation supported
// result can overflow undetected
// does not support decimal point
// does not support +/- signs
// returns value or 0 
DWORD ReadOutInteger( char* src, __out_opt DWORD* src_bytes_read ){
	char* str = src;
	DWORD acc = 0;

	if( str[0] == '0' && ( str[1] == 'x' || str[1] == 'X' ) ){ // hex
		for( str += 2 ;; str++ ){
			DWORD v;
			char c = *str;
			if( ( c >= '0' ) && ( c <= '9' ) ) v = (DWORD)((unsigned char)(c - '0'));
			else if( ( c >= 'a' ) && ( c <= 'f' ) ) v = (DWORD)((unsigned char)(c - 'a'));
			else if( ( c >= 'A' ) && ( c <= 'F' ) ) v = (DWORD)((unsigned char)(c - 'A'));
			else break; // bad digit
			acc <<= 4;
			acc |= v;
		}
	}
	else for( char c = *str; ( c < '0' || c > '9' ); c = *(++str) ) acc = ( acc * 10 ) + ( c - '0' ); // decimal
	if( src_bytes_read != NULL ) *src_bytes_read = str - src;
	return acc;
}

// copies text from src to dst 
// stops copying on null or non-quoted: \r, \n, //, /*, space, or tab 
// supports nested double-quotes
// src and dst must not overlap...
// dst gets null terminated
// returns the number of bytes required to hold the output...
DWORD ReadOutWord( char* dst, DWORD dst_size, char* src, __out_opt DWORD* src_bytes_read ){
	char* str = src;
	DWORD cnt = 0;
	BOOL quoted = FALSE;

	for( char c = *str; c != '\0'; c = *(++str) ){
		if( quoted == FALSE ){
			if( c == '\x20' ||  c == '\x09' || c == '\r' || c == '\n' ) break;
			if( c == '"' ) { quoted = TRUE; continue; }
			if( ( c == '/' ) && (( str[1] == '/' ) /* || ( str[1] == '*' ) */ ) ) break; // comment
		}
		else{
			if( c == '"' ){
				if( str[1] == '"' ) str++;  // pair of double quotes
				else{ quoted = FALSE; continue; }
			}
		}
		if( cnt < dst_size ) dst[cnt] = c;
		cnt++;
	}
	if( src_bytes_read != NULL ) *src_bytes_read = str - src;
	if( dst_size != 0 ){
		if( cnt >= dst_size ) dst[ dst_size - 1 ] = '\0'; 
		else dst[cnt] = '\0';
	}
	return ++cnt;
}

// read in a file
// place a nul byte at the end.
char* ReadInTextFile( const char* szFileName ){
	void* readbuf = NULL;
	DWORD dwBytesRead = 0;
	HANDLE hFile = CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if(hFile != INVALID_HANDLE_VALUE){
		DWORD dwBytesToRead = GetFileSize(hFile, NULL);
		if((dwBytesToRead != 0) && (dwBytesToRead != 0xFFFFFFFF)){
			readbuf = VirtualAlloc( NULL, dwBytesToRead + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE );
			if( readbuf != NULL){
				ReadFile(hFile, readbuf, dwBytesToRead, &dwBytesRead, NULL);
			}	
		}
		CloseHandle(hFile);
	}

	if( dwBytesRead == 0 ){
		if( readbuf != NULL ){
			DWORD dwErrCode = GetLastError();
			VirtualFree( readbuf, 0, MEM_RELEASE );
			SetLastError( dwErrCode );
			readbuf = NULL;
		}

		// print error
		char buf[320];
		DWORD dwErrorCode = GetLastError();
		Log("Error Accessing File: \"%s\"", szFileName);
		FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dwErrorCode, 0, buf, sizeof(buf), NULL );
		Log("%s", buf);
	}
	return (char*)readbuf;
}