# DataEraser
That's a program that changes every metadata byte of a file.

I've started coding this on April in 2018. At the time I was a little bit unaware of what the OS actually does to a "deleted" file (I already knew what happened, but I never cared about it), so I wanted to study it, to find some way how to vanish any sign that a file existed in your storage device.

The farthest I've got with this, was on changing every byte of a file like a .jpeg , .jpg or a .png . My choice to these extensions was on the fact that I could "see" if a file has been changed every time I used the program.

In a nutshell, the program works changing the file's metadata, and every extension (or in most part of each of them) has a pattern of where you can find the metadata area, it's predictable. Once the program knows what kind of file it's dealing with, it gets the actual size of the metadata in bytes, overwrite everything with random generated data and save the file, leaving it "safe" to erase.

As I hasn't continued it, you will find the code only for three extensions, and I actually didn't changed the header, because it would require some more research on what change, and I was running out of time on college.

I'm hoping to get some feedback on it, to know what I had done wrong, if I misunderstood any concept, or if my algorithm lacks on something.
