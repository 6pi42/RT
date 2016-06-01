import os

if os.name == 'posix':
	from Tkinter import *
	from tkColorChooser import *
elif os.name == 'nt':
	from tkinter import *
	from tkinter.colorchooser import *

from function import *
from objects import *




root = Tk()
root.title("Scene Generator")

title = Entry(root, width=10)
title.grid(row=0, column=0, padx = 5, pady = 5)
title.insert(0, "Scene Name")

widthl = Entry(root, width=5)
widthl.grid(row=1, column=0, padx = 5, pady = 5)
widthl.insert(0, "Width")

heightl = Entry(root, width=5)
heightl.grid(row=1, column=1, padx = 5, pady = 5)
heightl.insert(0, "Height")

samplst = ['Sampling: 0', 'Sampling: 2', 'Sampling: 4', 'Sampling: 8']
sampvar = StringVar()
sampvar.set(samplst[0])
samp = OptionMenu(root, sampvar, *samplst)
samp.grid(row = 1, column = 2,pady = 5, padx = 5)

shapelst = ['Plane','Sphere','Cylinder','Cone','Ellipsoid','Triangle','Cercle','Cube', 'Spotlight']
var = list()
var.append(StringVar())
var[0].set(shapelst[0])

drop = list()
drop.append(OptionMenu(root,var[0],*shapelst))
drop[0].grid(row = 4, column=0, padx=5, pady=5)

shapes = list()
shapes.append(-1)
edit = list()
edit.append(Button(root, text="edit", command= lambda a=0:edit_shape(a, shapelst, var, shapes)))
edit[0].grid(row=4, column=1, padx=5, pady=5)

add_button = Button(root, text = "More shape",
            command = lambda: add_shape(drop, root, var, shapelst, edit, shapes))
add_button.grid(row = 2, column=0, padx=5, pady=5)

less_button = Button(root, text = "Less shape",
            command = lambda: less_shape(drop, root, var, shapelst, edit, shapes))
less_button.grid(row = 2, column=1, padx=5, pady=5)

valid = Button(root, text="OK", command=lambda: create_file(shapes, title, widthl, heightl, sampvar))
valid.grid(row=0, column = 2, padx=5, pady=5)

root.mainloop()
