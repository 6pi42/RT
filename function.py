import os
from objects import *

if os.name == 'posix':
	from Tkinter import *
	from tkColorChooser import *
elif os.name == 'nt':
	from tkinter import *
	from tkinter.colorchooser import *

def get_object(index, entryx, entryy, entryz, tex, var, color, shapes):
	pos = (entryx.get(), entryy.get(), entryz.get())
	print tex.get()
	shapes[index] = Shape(var, pos, color, tex.get(), 20)
	print(shapes[index].pos[0])

def add_shape(drop, root, var, shapelst, edit, color, shapes):
	var.append(StringVar())
	var[len(var) - 1].set(shapelst[0])
	drop.append(OptionMenu(root, var[len(var) - 1], *shapelst))
	drop[len(drop) - 1].grid(row=len(drop) + 4, column=0, padx=5,pady=5)
	edit.append(Button(root, text="edit",
		command= lambda a=len(edit):edit_shape(a, shapelst, var, color, shapes)))
	edit[len(edit) - 1].grid(row=len(drop) + 4, column=1, padx=5, pady=5)
	color.append((0, 0, 0))
	shapes.append(-1)

def less_shape(drop, root, var, shapelst, edit, color, shapes):
	if len(drop) > 1:
		drop[len(drop) - 1].grid_forget()
		var.pop()
		drop.pop()
		edit[len(edit) - 1].grid_forget()
		edit.pop()
		color.pop()
		shapes.pop()

def getColor(color, index):
	print(index)
	tmp = askcolor()
	print(color[index])
	print(tmp[0][0])
	print(tmp[0][1])
	print(tmp[0][2])


def edit_shape(index, shapelst, var, color, shapes):
	child = Toplevel()
	#namel = Label(child, text=shapelst[var[index]])
	#namel.grid(row=0, column=0, padx=5, pady=5)
	posl = Label(child, text="Pos: (x, y, z)")
	posl.grid(row=1, column=0, padx=5, pady=5)
	entryx = Entry(child, width=5)
	entryx.grid(row=1, column=1, padx=5, pady=5)
	entryy = Entry(child, width=5)
	entryy.grid(row=1, column=2, padx=5, pady=5)
	entryz = Entry(child, width = 5)
	entryz.grid(row=1, column=3, padx=5, pady=5)
	color = (0, 0, 0)
	rgb = Button(child,text='Select Color', command= lambda a=index:getColor(color, a))
	rgb.grid(row=2, column=0, padx=5, pady=5)
	#rgbl = Label(child, text="RGB: (R, G, B)")
	#rgbl.grid(row=2, column=0, padx=5, pady=5)
	#entryr = Entry(child)
	#entryr.grid(row=2, column=1, padx=5, pady=5)
	#entryg = Entry(child)
	#entryg.grid(row=2, column=2, padx=5, pady=5)
	#entryb = Entry(child)
	#entryb.grid(row=2, column=3, padx=5, pady=5)
	var1 = IntVar()
	tex = Checkbutton(child, text="chess board", variable=var1)
	tex.grid(row=3, column=0, padx=5, pady=5)
	ok = Button(child, text="OK", command= lambda a=index, b=entryx, c=entryy, d=entryz, e=var1: get_object(a,b,c,d,e,color[a], var[a], shapes))
	ok.grid(row=4, column=3, padx=5, pady=5)
