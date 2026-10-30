#!/usr/bin/env python3
"""Regenerate the Sora 800 brand atlas with every printable ASCII glyph.

Matches the reviewed atlas layout: white glyph coverage in alpha, 200 px em,
full-advance cells, 6 px padding, shelf packing into a 2048 px wide page.
"""
import sys
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont

# Usage: tools/fonts/sora_brand_atlas.py "openpilot/starpilot/ui/assets/fonts/Sora[wght].ttf" openpilot/starpilot/ui/assets/fonts
src, out_dir = Path(sys.argv[1]), Path(sys.argv[2])
SIZE, PAD, WIDTH = 200, 6, 2048
font = ImageFont.truetype(str(src), SIZE)
font.set_variation_by_axes([800])
ascent, _ = font.getmetrics()

glyphs = []
for cp in range(32, 127):
  ch = chr(cp)
  left, top, right, bottom = font.getbbox(ch, anchor='la')
  advance = int(round(font.getlength(ch)))
  if right <= left or bottom <= top:  # space: a one-pixel empty cell at the baseline
    glyphs.append((cp, Image.new('L', (advance, 1), 0), 0, ascent, advance))
    continue
  x0 = min(0, left)
  width = max(right, advance) - x0
  mask = Image.new('L', (width, bottom - top), 0)
  ImageDraw.Draw(mask).text((-x0, -top), ch, font=font, fill=255, anchor='la')
  glyphs.append((cp, mask, x0, top, advance))

placements, x, y, shelf = [], PAD, PAD, 0
for cp, mask, x0, top, advance in glyphs:
  if x + mask.width + PAD > WIDTH:
    x, y, shelf = PAD, y + shelf + 2 * PAD, 0
  placements.append((cp, mask, x, y, x0, top, advance))
  x += mask.width + 2 * PAD
  shelf = max(shelf, mask.height)
height = 1
while height < y + shelf + PAD:
  height *= 2

atlas = Image.new('RGBA', (WIDTH, height), (0, 0, 0, 0))
white = Image.new('RGBA', (1, 1), (255, 255, 255, 255))
lines = [
  'info face="Sora-800" size=-200 bold=1 italic=0 charset="" unicode=1 stretchH=100 smooth=1 aa=1 padding=0,0,0,0 spacing=0,0 outline=0',
  f'common lineHeight={SIZE} base={SIZE} scaleW={WIDTH} scaleH={height} pages=1 packed=0 alphaChnl=0 redChnl=4 greenChnl=4 blueChnl=4',
  'page id=0 file="Sora-800.png"',
  f'chars count={len(placements)}',
]
for cp, mask, px, py, x0, top, advance in placements:
  atlas.paste(white.resize(mask.size), (px, py), mask)
  lines.append(f'char id={cp} x={px} y={py} width={mask.width} height={mask.height} ' +
               f'xoffset={x0} yoffset={top} xadvance={advance} page=0 chnl=15')
# Keep RGB black wherever coverage is zero, like the reviewed atlas.
r, g, b, a = atlas.split()
black = Image.new('L', atlas.size, 0)
atlas = Image.merge('RGBA', (Image.composite(r, black, a), Image.composite(g, black, a), Image.composite(b, black, a), a))
atlas.save(out_dir / 'Sora-800.png', optimize=True)
(out_dir / 'Sora-800.fnt').write_text('\n'.join(lines) + '\n')
print(WIDTH, height, len(placements))
