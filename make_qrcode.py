import pyqrcode
import cairosvg

with open("main.exe", "rb") as f:
    data = f.read()
    img = pyqrcode.create(data, error="L", encoding="iso-8859-1", mode="binary")
    img.svg("qrcode.svg", scale=4)
    cairosvg.svg2png(url = "qrcode.svg", write_to="qrcode.png")
