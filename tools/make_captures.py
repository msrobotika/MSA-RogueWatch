from pathlib import Path
from PIL import Image, ImageDraw, ImageFont

OUT = Path(__file__).parents[1] / "ui" / "captures"
OUT.mkdir(parents=True, exist_ok=True)
font = ImageFont.truetype("C:/Windows/Fonts/segoeui.ttf", 16)
bold = ImageFont.truetype("C:/Windows/Fonts/segoeuib.ttf", 34)
small = ImageFont.truetype("C:/Windows/Fonts/segoeui.ttf", 15)

views = [("radar", "RADAR", "SCANNING", (80,255,176), "2.4 GHz · 11 redes"), ("alertas", "ALERTAS", "0 ALERTAS", (255,209,102), "sin actividad sospechosa"), ("huellas", "HUELLAS", "27", (89,243,255), "dispositivos observados"), ("evidencias", "EVIDENCIAS", "SIN EVENTOS", (89,243,255), "registro local limpio")]
for name, title, value, color, subtitle in views:
    im = Image.new("RGB", (960,640), (7,16,24)); d = ImageDraw.Draw(im)
    d.rounded_rectangle((190,80,770,560), 24, fill=(16,43,59), outline=(29,233,255), width=5)
    d.text((225,110), "MSA_RogueWatch", font=bold, fill=(89,243,255))
    d.text((225,155), "PASSIVE WIRELESS DEFENDER · v0.1", font=font, fill=(128,174,187))
    cards = [(225,205,title,value,color,subtitle), (490,205,"ALERTAS","0",(255,209,102),"sin actividad sospechosa"), (225,355,"HUELLAS","27",(217,247,255),"dispositivos observados"), (490,355,"USB","CONECTADO",(80,255,176),"ESP32 online")]
    for x,y,label,val,col,sub in cards:
        d.rounded_rectangle((x,y,x+245,y+130), 12, fill=(10,27,40), outline=(29,113,130), width=2)
        d.text((x+20,y+20), label, font=font, fill=(217,247,255)); d.text((x+20,y+55), val, font=small if len(val)>10 else bold, fill=col); d.text((x+20,y+98), sub, font=small, fill=(217,247,255))
    d.text((225,525), "● USB conectado · ESP32 online", font=font, fill=(80,255,176))
    im.save(OUT / f"{name}.png")
