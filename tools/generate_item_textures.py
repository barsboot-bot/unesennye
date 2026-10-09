# -*- coding: utf-8 -*-
# Author: KRa Tos (Константин) | Unesennye Music System
"""Generate item textures (PNG/TGA). Convert to PAA with DayZ TexView2."""
import os
try:
    from PIL import Image, ImageDraw, ImageFont
except ImportError:
    print("Install Pillow: pip install Pillow")
    raise SystemExit(1)

OUT = os.path.join(os.path.dirname(__file__), "..", "data", "textures")
os.makedirs(OUT, exist_ok=True)

def make_tex(name, bg, accent, label, sub="UNESENNYE"):
    w = h = 256
    img = Image.new("RGBA", (w, h), bg)
    d = ImageDraw.Draw(img)
    d.rounded_rectangle([12, 12, w-13, h-13], radius=18, outline=accent, width=6)
    d.rounded_rectangle([28, 28, w-29, h-29], radius=12, fill=(accent[0], accent[1], accent[2], 40))
    if "sd" in name:
        d.rounded_rectangle([70, 50, 186, 210], radius=10, fill=accent)
        d.rectangle([70, 50, 100, 90], fill=(30, 30, 30, 255))
        for i in range(6):
            y = 55 + i * 8
            d.rectangle([74, y, 96, y+5], fill=(200, 180, 80, 255))
        d.rectangle([90, 170, 166, 190], fill=(20, 20, 20, 200))
    elif "cassette" in name:
        d.rounded_rectangle([40, 70, 216, 186], radius=8, fill=accent)
        d.ellipse([70, 100, 120, 150], outline=(20,20,20,255), width=4)
        d.ellipse([136, 100, 186, 150], outline=(20,20,20,255), width=4)
        d.rectangle([95, 115, 160, 135], fill=(15,15,15,255))
        d.rectangle([60, 80, 196, 95], fill=(240,240,240,230))
    elif "disk" in name:
        d.ellipse([36, 36, 220, 220], fill=accent)
        d.ellipse([100, 100, 156, 156], fill=(25,25,25,255))
        d.ellipse([118, 118, 138, 138], fill=(180,180,180,255))
    try:
        font = ImageFont.truetype("arial.ttf", 22)
    except Exception:
        font = ImageFont.load_default()
    d.text((40, 213), label, font=font, fill=(255,255,255,255))
    d.text((8, 8), sub, font=font, fill=(255,255,255,200))
    path = os.path.join(OUT, name + ".png")
    img.save(path, "PNG")
    img.save(os.path.join(OUT, name + ".tga"), "TGA")
    print("OK", path)

make_tex("sd_card_empty_co", (35, 40, 48, 255), (70, 130, 180, 255), "SD EMPTY")
make_tex("sd_card_co", (25, 40, 30, 255), (40, 180, 90, 255), "SD CARD")
make_tex("cassette_co", (40, 28, 20, 255), (200, 120, 50, 255), "CASSETTE")
make_tex("disk_co", (20, 20, 40, 255), (120, 90, 220, 255), "DISK")
print("Convert PNG/TGA to PAA via DayZ TexView2 into the same folder.")
