# -*- coding: utf-8 -*-
# Author: KRa Tos (Константин) | Unesennye Music System v1.3.3
"""Generate all media textures (PNG/TGA 512). Convert to PAA with TexView2."""
import os, math, colorsys
try:
    from PIL import Image, ImageDraw, ImageFont, ImageFilter
except ImportError:
    print("pip install Pillow")
    raise SystemExit(1)

OUT = os.path.join(os.path.dirname(__file__), "..", "data", "textures")
os.makedirs(OUT, exist_ok=True)

def font(size):
    for p in [
        "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf",
        "C:/Windows/Fonts/arial.ttf",
        "arial.ttf",
    ]:
        if os.path.exists(p):
            return ImageFont.truetype(p, size)
    return ImageFont.load_default()

def gradient(size, c1, c2):
    w, h = size
    img = Image.new("RGBA", size)
    d = ImageDraw.Draw(img)
    for i in range(h):
        t = i / max(h - 1, 1)
        col = tuple(int(c1[j] + (c2[j] - c1[j]) * t) for j in range(4))
        d.line([(0, i), (w, i)], fill=col)
    return img

def rounded_mask(size, radius):
    m = Image.new("L", size, 0)
    ImageDraw.Draw(m).rounded_rectangle([0, 0, size[0] - 1, size[1] - 1], radius=radius, fill=255)
    return m

def save(img, name):
    path = os.path.join(OUT, name)
    img.save(path + ".png")
    img.convert("RGBA").save(path + ".tga")
    print("OK", name)

def make_sd(name, body, label, title, sub):
    W = H = 512
    img = Image.new("RGBA", (W, H), (0, 0, 0, 0))
    shadow = Image.new("RGBA", (W, H), (0, 0, 0, 0))
    ImageDraw.Draw(shadow).rounded_rectangle([90, 70, 420, 460], radius=28, fill=(0, 0, 0, 90))
    img = Image.alpha_composite(img, shadow.filter(ImageFilter.GaussianBlur(12)))
    d = ImageDraw.Draw(img)
    body_img = gradient((300, 380), body[0], body[1])
    body_img.putalpha(rounded_mask((300, 380), 24))
    img.paste(body_img, (106, 66), body_img)
    d = ImageDraw.Draw(img)
    d.rounded_rectangle([106, 66, 406, 446], radius=24, outline=(255, 255, 255, 50), width=2)
    d.rounded_rectangle([106, 66, 170, 160], radius=8, fill=(25, 28, 32, 255))
    for i in range(8):
        y = 78 + i * 9
        d.rectangle([118, y, 158, y + 6], fill=(185, 165, 90, 255))
    d.rounded_rectangle([360, 120, 392, 160], radius=4, fill=(40, 45, 50, 255))
    d.rounded_rectangle([140, 200, 370, 340], radius=10, fill=label)
    d.text((155, 210), "UNESENNYE", font=font(18), fill=(255, 255, 255, 220))
    d.text((155, 240), title, font=font(36), fill=(255, 255, 255, 255))
    d.text((155, 290), sub, font=font(16), fill=(255, 255, 255, 180))
    d.ellipse([320, 360, 390, 430], fill=(20, 20, 25, 230))
    d.text((332, 380), "SD", font=font(22), fill=(255, 255, 255, 255))
    save(img, name)

def make_cassette():
    W = H = 512
    img = Image.new("RGBA", (W, H), (0, 0, 0, 0))
    shadow = Image.new("RGBA", (W, H), (0, 0, 0, 0))
    ImageDraw.Draw(shadow).rounded_rectangle([50, 130, 462, 390], radius=16, fill=(0, 0, 0, 100))
    img = Image.alpha_composite(img, shadow.filter(ImageFilter.GaussianBlur(14)))
    d = ImageDraw.Draw(img)
    shell = gradient((400, 240), (55, 40, 28, 255), (35, 25, 18, 255))
    shell.putalpha(rounded_mask((400, 240), 14))
    img.paste(shell, (56, 136), shell)
    d = ImageDraw.Draw(img)
    d.rounded_rectangle([90, 155, 422, 230], radius=6, fill=(245, 235, 210, 255))
    d.text((105, 162), "UNESENNYE MUSIC", font=font(16), fill=(60, 40, 20, 255))
    d.text((105, 188), "CASSETTE  •  TYPE I", font=font(22), fill=(40, 25, 10, 255))
    d.text((105, 215), "KRa Tos (Константин)", font=font(12), fill=(100, 70, 40, 200))
    for cx in (160, 350):
        d.ellipse([cx - 45, 250, cx + 45, 340], fill=(30, 25, 20, 255))
        d.ellipse([cx - 45, 250, cx + 45, 340], outline=(200, 160, 80, 180), width=3)
        d.ellipse([cx - 18, 277, cx + 18, 313], fill=(15, 12, 10, 255))
    d.rectangle([200, 285, 310, 305], fill=(20, 15, 10, 255))
    save(img, "cassette_co")

def make_disk_simple():
    W = H = 512
    img = Image.new("RGBA", (W, H), (0, 0, 0, 0))
    d = ImageDraw.Draw(img)
    d.ellipse([80, 80, 432, 432], fill=(55, 40, 110, 255))
    for r in range(70, 150, 8):
        d.ellipse([256 - r, 256 - r, 256 + r, 256 + r], outline=(30, 20, 60, 80), width=1)
    d.ellipse([200, 200, 312, 312], fill=(25, 22, 35, 255))
    d.ellipse([230, 230, 282, 282], fill=(160, 160, 170, 255))
    d.ellipse([242, 242, 270, 270], fill=(40, 40, 50, 255))
    d.text((175, 145), "UNESENNYE", font=font(20), fill=(255, 255, 255, 230))
    d.text((220, 360), "DISK", font=font(28), fill=(255, 255, 255, 240))
    save(img, "disk_co")

def make_disc(name, title, subtitle, colors):
    W = H = 512
    cx = cy = 256
    img = Image.new("RGBA", (W, H), (0, 0, 0, 0))
    shadow = Image.new("RGBA", (W, H), (0, 0, 0, 0))
    ImageDraw.Draw(shadow).ellipse([55, 60, 457, 462], fill=(0, 0, 0, 110))
    img = Image.alpha_composite(img, shadow.filter(ImageFilter.GaussianBlur(18)))
    d = ImageDraw.Draw(img)
    d.ellipse([72, 72, 440, 440], fill=colors["outer"])
    d.ellipse([72, 72, 440, 440], outline=colors.get("rim", (255, 255, 255, 90)), width=3)
    for r in range(95, 175, 5):
        d.ellipse([cx - r, cy - r, cx + r, cy + r], outline=(*colors["mid"][:3], 40), width=1)
    for i in range(0, 360, 8):
        hue = i / 360.0
        rr, gg, bb = colorsys.hsv_to_rgb(hue, 0.35, 0.95)
        col = (int(rr * 255), int(gg * 255), int(bb * 255), 28)
        rad1, rad2 = math.radians(i), math.radians(i + 6)
        for rad in range(100, 178, 4):
            x1 = cx + int(rad * math.cos(rad1))
            y1 = cy + int(rad * math.sin(rad1))
            x2 = cx + int(rad * math.cos(rad2))
            y2 = cy + int(rad * math.sin(rad2))
            d.line([(x1, y1), (x2, y2)], fill=col, width=2)
    d.arc([95, 95, 417, 417], 200, 320, fill=(255, 255, 255, 70), width=16)
    d.ellipse([155, 155, 357, 357], fill=colors["label"])
    d.ellipse([210, 210, 302, 302], fill=colors["hub"])
    d.ellipse([232, 232, 280, 280], fill=(150, 150, 160, 255))
    d.ellipse([244, 244, 268, 268], fill=(35, 35, 42, 255))
    d.text((188, 168), "UNESENNYE", font=font(16), fill=colors["text"])
    d.text((cx - len(title) * 10, 318), title, font=font(26), fill=colors["text"])
    d.text((cx - len(subtitle) * 4, 350), subtitle, font=font(13), fill=colors.get("subtext", colors["text"]))
    d.rounded_rectangle([200, 385, 312, 415], radius=8, fill=colors.get("badge", (20, 20, 28, 230)))
    d.text((218, 390), title, font=font(14), fill=(255, 255, 255, 255))
    save(img, name)

make_sd("sd_card_co", [(30, 120, 70, 255), (20, 80, 50, 255)], (25, 90, 55, 255), "SD CARD", "Playlist ready")
make_sd("sd_card_empty_co", [(50, 90, 140, 255), (35, 60, 100, 255)], (40, 70, 110, 255), "SD EMPTY", "No data")
make_cassette()
make_disk_simple()
make_disc("cd_co", "CD", "Compact Disc  •  Music", {
    "outer": (55, 58, 70, 255), "mid": (90, 95, 110, 255), "label": (45, 48, 58, 255),
    "hub": (28, 30, 38, 255), "text": (240, 240, 245, 255), "subtext": (180, 185, 200, 220),
    "rim": (200, 210, 230, 120), "badge": (30, 90, 160, 230),
})
make_disc("dvd_co", "DVD", "Digital Versatile Disc", {
    "outer": (40, 25, 55, 255), "mid": (80, 50, 100, 255), "label": (55, 30, 70, 255),
    "hub": (22, 15, 30, 255), "text": (255, 230, 180, 255), "subtext": (220, 180, 140, 210),
    "rim": (255, 200, 120, 100), "badge": (140, 90, 30, 230),
})
make_disc("dvd_r_co", "DVD-R", "Recordable  •  Unesennye", {
    "outer": (25, 45, 90, 255), "mid": (40, 70, 130, 255), "label": (20, 40, 75, 255),
    "hub": (15, 25, 45, 255), "text": (220, 235, 255, 255), "subtext": (160, 190, 230, 210),
    "rim": (120, 180, 255, 110), "badge": (20, 70, 150, 230),
})
print("Convert PNG/TGA -> PAA with DayZ TexView2 into data/textures/")
