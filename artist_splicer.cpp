#include "artist_splicer.h"
#include <algorithm>
#include <cctype>
#include <locale>

//words that usually are inbetween artist names
const char * linking_words[] = {
    "&",
    "vs",
    "feat",
    "and",
    "ft",
    NULL
};

//letters that are downright ignored
const char * additive_symbols = "().,[]";

namespace no_conflict {

    //remove any of the given input chars from the in/out string
    void remove_any(std::string &str,const char * sym)
    {
        std::replace_if(str.begin(),str.end(),[sym](unsigned char x){
            for(int i = 0;sym[i] != '\0';i++)
            {
                if(sym[i]==x) return true;
            }
            return false;
        },' ');
    }

    //returns the first position of any of the given words in a string
    int find_any (const std::string & str,const char ** words)
    {
        int best =-1;
        for(int i = 0;words[i] != NULL;i++)
        {
            int pos = 0;
            if((pos = str.find(words[i])) != std::string::npos) best = (best ==-1 ? pos : pos < best ? pos:best);
        }
        return best;
    }

    //splices a piece off, of the original string
    std::string splice_front(std::string& str,int pos){
        std::string tmp = str.substr(0,pos);
        str = str.substr(pos);
        return tmp;
    }

    // trim from start (in place)
    static inline void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
        }));
    }

    // trim from end (in place)
    static inline void rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }

    // trim from both ends (in place)
    static inline void trim(std::string &s) {
        ltrim(s);
        rtrim(s);
    }
}


//retuns a vector of strings with the recognized artist names from one single string
std::vector<std::string> splice_artists(std::string artists_combined)
{
    using namespace no_conflict;

    std::vector<std::string> artists_names;
    remove_any(artists_combined,additive_symbols);
    while(find_any(artists_combined,linking_words) != -1)
    {
        artists_names.push_back(splice_front(artists_combined,find_any(artists_combined,linking_words)));
        trim(artists_combined);
        artists_combined=artists_combined.substr(artists_combined.find_first_of(" \t")+1);
    }
    artists_names.push_back(artists_combined);

    for(auto& e : artists_names)
    {
        trim(e);
    }

    return artists_names;
}
