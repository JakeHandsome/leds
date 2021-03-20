import sys
import board
import neopixel
pixels = neopixel.NeoPixel(board.D18, 150)

if len(sys.argv) == 4:
    pixels.fill((int(sys.argv[1]), int(sys.argv[2]), int(sys.argv[3])))
