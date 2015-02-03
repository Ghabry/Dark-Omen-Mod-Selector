extern "C"
{
	// Returns a pointer to the first occurrence of value in pvBuf
	void* memchr ( const void* pvBuf, int value, size_t cnt ){
		for(unsigned char* buf=(unsigned char*)pvBuf; buf!=((unsigned char*)pvBuf)+cnt; buf++)
			if( *buf == (unsigned char)value ) return buf;  
		return 0;
	}

	// Compare BYTES in two buffers.  Returns zero if they all match or
	// a value representing which buffer is greater if they do not.
	int memcmp( const void* pvBuf1, const void* pvBuf2, size_t cnt ){
		unsigned char* buf1 = (unsigned char*)pvBuf1;
		unsigned char* buf2 = (unsigned char*)pvBuf2;
		int result = 0;
		while( buf1 != ((unsigned char*)pvBuf1) + cnt) if(result = *buf1++ - *buf2++) break;
		return result;
	}

	// Copies cnt bytes from src to dst 
	void* memcpy( void* pvDst, const void* pvSrc, size_t cnt ){
		unsigned char* dst = (unsigned char*)pvDst;
		unsigned char* src = (unsigned char*)pvSrc;
		while(src != ((unsigned char*)pvSrc + cnt)) *dst++ = *src++;
		return pvDst;
	}

	// Copies cnt bytes from src to dst.
	// If some regions of the source area and the destination overlap, 
	// the original source bytes in the overlapping region are copied before being overwritten.
	void* memmove( void* pvDst, const void* pvSrc, size_t cnt ){ 
		if( pvDst <= pvSrc ){  // copy from front to back
			unsigned char* src = (unsigned char*)pvSrc;
			unsigned char* dst = (unsigned char*)pvDst;
			while(dst != ((unsigned char*)pvDst + cnt)) *dst++ = *src++;
			return pvDst;
		}
		else{ // copy from back to front
			unsigned char* src = ((unsigned char*)pvSrc) + cnt;
			unsigned char* dst = ((unsigned char*)pvDst) + cnt;
			while(dst != pvDst) *(--dst) = *(--src);
			return pvDst;
		}
	}

	// Sets the first cnt bytes of dst to the specified fill value (interpreted as an unsigned char).
	void* memset( void* pvDst, int fill, size_t cnt ){
		unsigned char* dst = (unsigned char*)pvDst;
		while( dst != (((unsigned char*)pvDst) + cnt) ) *dst++ = (unsigned char) fill;
		return pvDst;
	}

	// Copies src string to the end of dst string 
	char* strcat( char* dst, const char* src ){
		char* dst_start = dst;
		while(*dst)dst++;
		while(*dst++ = *src++);
		return dst_start;
	}

	// Returns a pointer to the first occurrence of value in str
	// The null terminator may be located 
	char* strchr ( const char* str, int value ){
		do{ if(*str == (char)value) return (char*)str; }while(*str++);
		return 0;
	}

	// Compares two null terminated strings
	int strcmp( const char* str1, const char* str2 ){
		for(;;){
			int result;
			if( (result = *str1 - *str2++) || !(*str1++))return result;
		}
	}

	// Copies a null terminated src string to dst 
	char* strcpy ( char* dst, const char* src ){
		char* dst_start = dst;
		while(*dst++ = *src++);
		return dst_start;
	}

	// Returns the number of characters in str, excluding the terminal NULL.
	size_t strlen( const char* str ){
		const char* s;
		for( s = str; *s; s++ );
		return (s - str);
	}

	// Appends cnt characters of src to dst, plus a terminating null-character.
	char* strncat ( char* dst, char* src, size_t cnt ){
		char* dst_start = dst;
		char* src_end = &src[cnt];
		while(*dst)dst++;
		while(src != src_end) if(!(*dst++ = *src++)) return dst_start;
		*dst = '\0';
		return dst_start;
	}

	// Compare cnt characters of two strings
	int strncmp ( const char* str1, const char* str2, size_t cnt ){
		const char* str1_end = str1 + cnt;
		int result = 0; 
		while( str1 != str1_end && (!(result = *str1 - *str2++)) && *str1++);
		return result;
	}

	// Copies cnt characters from src to dst.
	// if cnt > strlen(src) then the rest of dst IS filled with zeros (for no reason)
	char* strncpy ( char* dst, const char* src, size_t cnt ){
		char* cp = dst;
		while(cp != &dst[cnt]){ 
			if(!(*cp++ = *src++)){
				while(cp != &dst[cnt]) *cp++ = '\0';
			}
		}
		return dst;
	}

	// Returns a pointer to the last occurrence of value in str
	// The null terminator may be located 
	char* strrchr ( const char* str, int value){
		char* p = 0;
		do{ 
			if(*str == (char)value) p = (char*)str;
		}while(*str++);
		return p;
	}


	// find a sub-string with in a string
	char* strstr ( const char* str, const char* sub_str ){
		const char* sub_str_end = sub_str;
		while(*sub_str_end) sub_str_end++;
		while(*str){
			if( *str++ == *sub_str ){
				const char* s = str;
				const char* ss = &sub_str[1];
				do{
					if( ss == sub_str_end ) return ((char*)--str); // found
					if( *s != *ss++ ) break;
				}while( *s++ );
			}
		}
		return 0; // not found
	}

	// Returns a pointer to the first occurrence of any characters from str2 in str1, or a null pointer.
	// The search does not include the terminating null-characters.
	char* strpbrk ( const char* str1, const char* str2 ){
		for( ; *str1; str1++ ) for(const char* cp=str2; *cp; cp++) if(*cp == *str1) return (char*)str1;
		return 0;
	}

	// Returns the offset of the first of any characters from str2 found in str1
	// The search includes the null terminator
	size_t strcspn ( const char* str1, const char* str2 ){
		size_t i;
		for(i=0; str1[i]; i++) for(size_t ii=0; str2[ii]; ii++) if(str2[ii] == str1[i]) return i;
		return i;
	}

	// Get span of character from str2 at the start of str1
	size_t strspn ( const char* str1, const char* str2 ){
		size_t i, ii;
		for(i=0; str1[i]; i++){
			for(ii=0; str2[ii]; ii++){
				if(str2[ii] == str1[i])break;
			}
			if(!str2[ii])break;
		}
		return i;
	}
}
