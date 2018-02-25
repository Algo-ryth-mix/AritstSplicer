#include <iostream>
#include "artist_splicer.h"
#include "ID3.h"
int main(int argc,char** argv)
{
    if(argc < 2) return 1;
    std::string artists = getArtist(argv[1]);
    auto vec = splice_artists(artists);
    for( auto& e : vec)
    {
        std::cout << "\t-"<<e << std::endl;
    }
    return 0;
}