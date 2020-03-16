#!/bin/sh

B='#00000000'  # blank
C='#ffffff22'  # clear ish
D='#a107f9ff'  # default
T='#a107f9ff'  # text
W='#f4618bbb'  # wrong
V='#f4618bbb'  # verifying

i3lock \
--insidevercolor=$B   \
--ringvercolor=$V     \
\
--insidewrongcolor=$B \
--ringwrongcolor=$W   \
\
--insidecolor=$B      \
--ringcolor=$D        \
--linecolor=$B        \
--separatorcolor=$D   \
\
--verifcolor=$T        \
--wrongcolor=$T        \
--timecolor=$T        \
--datecolor=$T        \
--layoutcolor=$T      \
--keyhlcolor=$W       \
--bshlcolor=$W        \
\
--screen 1            \
--blur 8              \
--clock               \
--indicator           \
--timestr="%H:%M:%S"  \
--datestr="%d %m %Y" \

# --veriftext="Drinking verification can..."
# --wrongtext="Nope!"
# --textsize=20
# --modsize=10
# --timefont=comic-sans
# --datefont=monofur
# etc