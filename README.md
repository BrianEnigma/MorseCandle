#Morse Candle

##Overview

I help run a monthly puzzle event in Portland called [Puzzled Pint][].  Puzzled Pint is a sort of miniature version of [The Game][] designed such that a half-dozen puzzles can be completed over a few hours at a local pub over beer.

In both running the event and scouting locations, I keep running into "electric candles" placed at the tables.  These are little battery-operated [flickering LEDs][] placed in votive candle holders.  They provide ambiance and dissuade pyromania.  The flickering is kind of nice and natural, but my brain kept wanting to find patterns in it.

This, of course, drove me to design my own electric candle with intentional flicker patterns.

[Puzzled Pint]: http://puzzledpint.com "The Puzzled Pint website"
[The Game]: http://en.wikipedia.org/wiki/The_Game_(treasure_hunt) "The Game at Wikipedia"
[flickering LEDs]: http://shop.evilmadscientist.com/productsmenu/partsmenu/353 "Candle flicker LEDs at Evil Mad Scientist"

##Design - Hardware

TODO

![Schematic](./Schematics/Morse%20Candle%20Schematic.png)

##Design - Software

TODO

##Parts

* [Teensy 3.0](http://www.pjrc.com/store/teensy3.html)
* [4 AA battery holder with 9V clip](http://www.radioshack.com/product/index.jsp?productId=2062239)
* [9V battery clip](http://www.radioshack.com/product/index.jsp?productId=2062218)
* [2-inch mailing tube](http://www.tapplastics.com/product/plastics/plastic_rods_tubes_shapes/tube_pak/274), cut to 5 inches
* 5 inch paper diffuser (see ./Paper Diffuser/diffuser.pdf).  I printed mine on cream-colored paper, but regular white paper or cardstock probably work fine.
* [220Ω resistor](http://www.radioshack.com/product/index.jsp?productId=2062340)
* yellow LED
* heat-shrink tubing to protect the LED and resistor legs from shorting
* optional wooden base for the tube.  I started with a [rosette](http://www.homedepot.com/House-of-Fara/h_d1/N-25ecodZ5yc1vZr3/R-100042410/h_d2/ProductDisplay?catalogId=10053), routed out most of the circle, then stained it a dark brown.
* 22ga wire, solder, soldering iron

##Next Steps

I built this with scrap components I had lying about in the lab.  I see two main design improvements: battery and processor.

I went with an off-the-shelf battery holder connected via 9V clip to the Teensy board.  This has two major design flaws and one minor annoyances.  The ARM processor on the Teensy board really wants 3.3V.  It has a built-in voltage regulator, but it is only rated up to 5.5V.  I have 3V (2 AA) and 6V (4 AA) holders lying around, but 4.5V (3 AA) are a little more rare.  I hacked my 4 AA holder by sawing off a wooden dowel to the length of a battery, wrapping it in foil, then putting that "fake battery" in to bridge one of the AA slots.  If someone were to actually put 4 AAs in there, it would over-voltage the regulator.  Additionally, they AA battery pack is hooked up with a 9V battery clip.  If someone were to hook an actual 9V battery to the board, it would also over-voltage.  Since it is just me, I can deal with that, but if other less technical people were to start building and using these candles, I would like a more foolproof power system.  As for the annoyance, the 4 AA battery pack is a little bulky.  Smaller batteries (coin cells or lithium camera batteries) are more expensive and less common, but would help keep the design more compact and votive-candle-like.  Another alternative to this would be to keep AAs, but to use a taller base and carve out space for a battery holder down there.  It would also be nice to either have the battery holder directly wired up (sans 9V clip) or connect through the micro USB port.

As for the processor: it's overkill.  I use exactly one pin of a 32-bit 50MHz ARM processor.  I could probably get away with an [8-leg AVR][], but then I'd have the hassle of an [In-System Programmer][] (vs the Teensy's simple USB connection).

[8-leg AVR]: https://www.sparkfun.com/products/9378 "Atmel ATtiny85 at Sparkfun Electronics"
[In-System Programmer]: http://arduino.cc/en/Tutorial/ArduinoISP "Using an Arduino as an ISP"

##License

Basically: have fun with this, make modifications, share those modifications, but don't sell it!

Copyright © 2012, Brian Enigma <brian@netninja.com>, <http://nja.me/candle>
This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. To view a copy of this license, visit <http://creativecommons.org/licenses/by-nc-sa/3.0/>.

If you like this project, you may also be interested in Puzzled Pint <http://puzzledpint.com/>.
