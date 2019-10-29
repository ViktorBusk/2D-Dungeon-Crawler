import os
import numpy
from PIL import Image
from pathlib import Path
import json
import re

def writeToTxtFile(path, fileName, data):
    filePathNameWExt = path + '/' + fileName + '.txt'
    with open(filePathNameWExt, 'w') as fp:
        for i in data:
            fp.write(str(i) + "\n")

def staticSheet(folder, folderPath, data):
    for img in folder:
        im = Image.open(folderPath + img)
        rgb_im = im.convert('RGBA')
        dimensions = [float(s) for s in re.findall(r'-?\d+\.?\d*', img)]
        cols = int(dimensions[0])
        rows = int(dimensions[1])
        
        cutX = rgb_im.size[0]/cols
        cutY = rgb_im.size[1]/rows
        
        index = 0
        for x in numpy.arange(cutX, rgb_im.size[0]+1, cutX):
            for y in numpy.arange(cutY, rgb_im.size[1]+1, cutY):
                row = y - cutY + 1
                col = x - cutX + 1
                pix = 0
                minimal_x = None
                minimal_y = None
                maximal_x = None
                maximal_y = None
                rowdata = ""
                while row < y + 1:
                    #print("")
                    #print("Row number: " + str(row))
                    while col < x + 1:
                        # get the RGB values from the current pixel
                        pixX = col - 1
                        pixY = row - 1
                        r, g, b, a = rgb_im.getpixel((pixX, pixY))
                        if(r != 0 and g != 0 and b != 0 and a != 0):
                            if(minimal_x == None or pixX < minimal_x):
                                minimal_x = pixX
                            if(minimal_y == None or pixY < minimal_y):
                                minimal_y = pixY
                            if(maximal_x == None or pixX > maximal_x):
                                maximal_x = pixX
                            if(maximal_y == None or pixY > maximal_y):
                                maximal_y = pixY
                        # append the RGB values to the rowdata variable as (R, G, B)
                        rowdata += "(" + str(r) + "," + str(g) + "," + str(b) + ") "
                        # increment the column count
                        col = col + 1
                        # increment the pixel count
                        pix = pix + 1
                    # print out all RGB values for the row
                    #print(rowdata)
                    # clear out rowdata variable
                    rowdata = ""
                    # increment the row...
                    row = row + 1
                    # reset the column count
                    col = x - cutX + 1
                #output for proof!
                #print("")
                #print("Width = " + str(cutX) + " pixels")
                #print("Height = " + str(cutY) + " pixels")
                #print("Total Pixels = " + str(pix) + ".")
                #print(minimal_x - x + cutX, minimal_y - y + cutY, maximal_x + 1 - x + cutX, maximal_y + 1 - y + cutY)
                width = maximal_x + 1 - x + cutX - (minimal_x - x + cutX)
                height = maximal_y + 1 - y + cutY - (minimal_y - y + cutY)
                dataName = str(img)

                data.extend([dataName, cutX, cutY, minimal_x - x + cutX, minimal_y - y + cutY, width, height])
                
                """ data[str(index) + "." + img] = {
                    'imgWidth': cutX,
                    'imgHeight': cutY,
                    'x': minimal_x - x + cutX,
                    'y': minimal_y - y + cutY,
                    'width': maximal_x + 1 - x + cutX - (minimal_x - x + cutX),
                    'height': maximal_y + 1 - y + cutY - (minimal_y - y + cutY)
                } """
                index+=1

def staticSingle(folder, folderPath, data):
    for img in folder:
        im = Image.open(folderPath + img)
        # Convert our image to RGB
        rgb_im = im.convert('RGB')
        # Use the .size object to retrieve a tuple contain (width,height) of the image
        # and assign them to width and height variables
        width = rgb_im.size[0]
        height = rgb_im.size[1]
        # set some counters for current row and column and total pixels
        row = 1
        col = 1
        pix = 0
        minimal_x = None
        minimal_y = None
        maximal_x = None
        maximal_y = None
        # create an empty output row
        rowdata = ""
        # loop through each pixel in each row outputting RGB value as we go...
        # all the plus and minus ones are to deal with the .getpixel class being
        # zero indexed and we want the output to start at pixel 1,1 not 0,0!
        while row < height + 1:
            #print("")
            #print("Row number: " + str(row))
            while col < width + 1:
                # get the RGB values from the current pixel
                x = col - 1
                y = row - 1

                r, g, b = rgb_im.getpixel((x, y))
                if(r != 0 and g != 0 and b != 0):
                    if(minimal_x == None or x < minimal_x):
                        minimal_x = x
                    if(minimal_y == None or y < minimal_y):
                        minimal_y = y
                    if(maximal_x == None or x > maximal_x):
                        maximal_x = x
                    if(maximal_y == None or y > maximal_y):
                        maximal_y = y
                # append the RGB values to the rowdata variable as (R, G, B)
                rowdata += "(" + str(r) + "," + str(g) + "," + str(b) + ") "
                # increment the column count
                col = col + 1
                # increment the pixel count
                pix = pix + 1
            # print out all RGB values for the row
            #print(rowdata)
            # clear out rowdata variable
            rowdata = ""
            # increment the row...
            row = row + 1
            # reset the column count
            col = 1
        #output for proof!
        #print("")
        #print("Width = " + str(width) + " pixels")
        #print("Height = " + str(height) + " pixels")
        #print("Total Pixels = " + str(pix) + ".")
        #print(minimal_x, minimal_y, maximal_x + 1, maximal_y + 1)
        data[img] = {
            'imgWidth': width,
            'imgHeight': height,
            'x': (minimal_x),
            'y': (minimal_y),
            'width': (maximal_x + 1) - (minimal_x),
            'height': (maximal_y + 1) - (minimal_y)
        }

dir_path = os.path.dirname(os.path.realpath(__file__))
imgType = dir_path + "\Textures\Spritesheets"

folder = os.listdir(imgType)
folderPath = str(Path(imgType).resolve())
folderPath += "/"

data = []
filename = "hitboxList"

staticSheet(folder, folderPath, data)

writeToTxtFile(dir_path, filename, data)
print("DONE!")
 
