# ArtistSplicer

usage:

```bash
  ./identify_artists song.mp3
``` 

in code:
```c++
	#include "artist_splicer.h"
    
    [...]
    
    std::vector<std::string> artists = splice_artists("Some dude ft. some other dude");
    
    for( auto& e : artists)
    {
        std::cout << "\t-"<<e << std::endl;
    }
 ```
