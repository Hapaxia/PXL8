PXL8
====

by Hapax
github.com/hapaxia
July 2014

Pixelation Class

Creates a pixelated render target. It is drawn to using views in a similar fashion to SFML.
The size of the pixels can be specified (both dimensions can be specified separately) which changes the amount of pixelation.
The final pixelated render is a standard sprite, ready to be drawn to your window as normal.

See example.cpp to see it in action.
It will require a font for the overlay text and an image as an example pixelation test.
Controls for example.cpp:
1 and 2 - reduce and expand respectively the pixel size.
3 and 4 - reduce and expand respectively the pixel width.
5 and 6 - reduce and expand respectively the pixel height.
BACKSPACE - reset the pixel size to 1x1.
ENTER - randomise the circles' colours.
SPACE - switch between the circles and the image.
ESCAPE - close application.

Requires SFML (www.sfml-dev.org)
