import os.path
from PIL import Image
def open_ppm(file):
    png = file[:-4]+".png"
    os.system(f"convert {file} {png}")
    image = Image.open(png)
    os.unlink(png)
    return image
