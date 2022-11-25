#pragma once
#include "pch.hpp"


namespace VSIF {
    class ValveScenesImageFile;
}

#pragma once
namespace Helper {
	static inline uint32_t FourCC(char ID[4]) {
		return (ID[0] | (ID[1] << 8) | (ID[2] << 16) | (ID[3] << 24));
	}

    extern VSIF::ValveScenesImageFile* vsif;


    static inline void ReplaceAll(std::string &str, const std::string& from, const std::string& to) {
        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
        }
        //return str;
    }

    static inline std::istream& safeGetline(std::istream& is, std::string& t)
    {
        t.clear();

        // The characters in the stream are read one-by-one using a std::streambuf.
        // That is faster than reading them one-by-one using the std::istream.
        // Code that uses streambuf this way must be guarded by a sentry object.
        // The sentry object performs various tasks,
        // such as thread synchronization and updating the stream state.

        std::istream::sentry se(is, true);
        std::streambuf* sb = is.rdbuf();

        for(;;) {
            int c = sb->sbumpc();
            switch (c) {
            case '\n':
                return is;
            case '\r':
                if(sb->sgetc() == '\n')
                    sb->sbumpc();
                return is;
            case std::streambuf::traits_type::eof():
                // Also handle the case when the last line has no line ending
                if(t.empty())
                    is.setstate(std::ios::eofbit);

                if (t.empty())
                    is.setstate(std::ios::badbit);
                return is;
            default:
                t += (char)c;
            }
        }
    }
    static inline bool compareChar(char & c1, char & c2)
    {
        if (c1 == c2)
            return true;
        else if (std::toupper(c1) == std::toupper(c2))
            return true;
        return false;
    }
    /*
     * Case Insensitive String Comparision
     */
    static inline bool caseInSensStringCompare(std::string & str1, std::string &str2)
    {
        return ( (str1.size() == str2.size() ) &&
                 std::equal(str1.begin(), str1.end(), str2.begin(), &compareChar) );
    }

    static inline bool matchWildCard(char const *needle, char const *haystack) {
        for (; *needle != '\0'; ++needle) {
            switch (*needle) {
            case '?':
                if (*haystack == '\0')
                    return false;
                ++haystack;
                break;
            case '*': {
                if (needle[1] == '\0')
                    return true;
                size_t max = strlen(haystack);
                for (size_t i = 0; i < max; i++)
                    if (matchWildCard(needle + 1, haystack + i))
                        return true;
                return false;
            }
            default:
                if (*haystack != *needle)
                    return false;
                ++haystack;
            }
        }
        return *haystack == '\0';
    };

};
