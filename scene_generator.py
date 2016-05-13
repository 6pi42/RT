import os
if os.name == 'posix':
	from Tkinter import *
if os.name == 'nt':
	from tkinter import *

root = Tk()
root.title("Scene Generator")

class Triple:
	def __init__(self, x, y, z):
		self.x = x
		self.y = y
		self.z = z
		self.w = 0.0

class Shape:
	def __init__(self, type, pos, rgb, tex, rad):
		self.type = type
		self.pos = pos
		self.rgb = rgb
		self.tex = tex
		self.rad = rad

def add_shape(drop, root, var, shapelst):
	var.append(StringVar())
	var[len(var) - 1].set(shapelst[0])
	drop.append(OptionMenu(root, var[len(var) - 1], *shapelst))
	drop[len(drop) - 1].grid(row=len(drop) + 4, column=0, padx=5,pady=5)


def less_shape(drop, root, var, shapelst):
	if len(drop) > 1:
		drop[len(drop) - 1].grid_forget()
		var.pop()
		drop.pop()

title = Entry(root)
title.grid(row=0, column=0, padx = 5, pady = 5)
title.insert(0, "Scene Name")

valid = Button(root, text="OK")
valid.grid(row=0, column = 2, padx=5, pady=5)

widthl = Entry(root)
widthl.grid(row=1, column=0, padx = 5, pady = 5)
widthl.insert(0, "Width")

heightl = Entry(root)
heightl.grid(row=1, column=1, padx = 5, pady = 5)
heightl.insert(0, "Height")

samplst = ['Sampling: 0', 'Sampling: 2', 'Sampling: 4', 'Sampling: 8']
sampvar = StringVar()
sampvar.set(samplst[0])
samp = OptionMenu(root, sampvar, *samplst)
samp.grid(row = 1, column = 2,pady = 5, padx = 5)

shapelst = ['Plan','Sphere','Cylindre','Cone','Ellipsoid','Triangle','Cercle','Cube']
var = list()
var.append(StringVar())
var[0].set(shapelst[0])

drop = list()
drop.append(OptionMenu(root,var[0],*shapelst))
drop[0].grid(row = 4, column=0, padx=5, pady=5)

add_button = Button(root, text = "More shape",
            command = lambda: add_shape(drop, root, var, shapelst))
add_button.grid(row = 2, column=0, padx=5, pady=5)

less_button = Button(root, text = "Less shape",
            command = lambda: less_shape(drop, root, var, shapelst))
less_button.grid(row = 2, column=1, padx=5, pady=5)

root.mainloop()
