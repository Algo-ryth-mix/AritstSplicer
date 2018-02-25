#include <id3/tag.h>
#include <id3/misc_support.h>
#include <string>


//uses the id3 library to extract the artist name from an mp3 file
inline std::string getArtist(const std::string & filename)
{
    ID3_Tag myTag(filename.c_str());
    return ID3_GetArtist(&myTag);
}
