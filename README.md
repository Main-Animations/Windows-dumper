# windows-dumper
# ALL CREDITS TO SPEEDSTERKAWAII ON GITHUB.

roblox dumper that derives from disassembly. that means its not detected & its mostly just a parser.

# how to use?

1. paste this in terminal:
```mkdir ~/offsetsdumps/```

```otool -arch arm64 -tvV /Applications/Roblox.app/Contents/MacOS/RobloxPlayer > /Users/artrix/offsetdumps/roblox.asm ```

*this creates the file in /Users/offsetdumps so you can extract instructions*.

2. details

if you go to `dump.cpp` you can see how it works. you can tweak a few like for example:

to find spawn its "**Spawn function requires 1 argument**",

that starts at pushq	%rbp [__text:000000010144705C                 push    rbp]

so you just tweak or make another searcher that specifically finds that instruction above the spawn string

3. expanding support

if you're an absolute starter, read `handbook.md`. in **TextEdit** , manually open `roblox.asm` to study and find the functions. 

# for macos?

*yes* and *no*. you can use **IDA** to produce an assembly file. and `dump.cpp` must be modified  a little bit.
