import os
from objects import *

if os.name == 'posix':
	from Tkinter import *
	from tkColorChooser import *
elif os.name == 'nt':
	from tkinter import *
	from tkinter.colorchooser import *

def get_object(index, entryx, entryy, entryz, tex, var, shapes, red, blue, green, norx, nory, norz, rad):
	pos = (entryx.get(), entryy.get(), entryz.get())
	rgb = (red, blue, green)
	shapes[index] = Shape(var, pos, rgb, tex.get(), 20)

def add_shape(drop, root, var, shapelst, edit, color, shapes):
	var.append(StringVar())
	var[len(var) - 1].set(shapelst[0])
	drop.append(OptionMenu(root, var[len(var) - 1], *shapelst))
	drop[len(drop) - 1].grid(row=len(drop) + 4, column=0, padx=5,pady=5)
	edit.append(Button(root, text="edit",
		command= lambda a=len(edit):edit_shape(a, shapelst, var, color, shapes)))
	edit[len(edit) - 1].grid(row=len(drop) + 4, column=1, padx=5, pady=5)
	color.append(Triple(0,0,0))
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


def edit_shape(index, shapelst, var, color, shapes):
	child = Toplevel()
	child.title('Object:' + str(var[index].get()))
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
	rgbl = Label(child, text="RGB: (R, G, B)")
	rgbl.grid(row=2, column=0, padx=5, pady=5)
	entryr = Entry(child, width=5)
	entryr.grid(row=2, column=1, padx=5, pady=5)
	entryg = Entry(child, width=5)
	entryg.grid(row=2, column=2, padx=5, pady=5)
	entryb = Entry(child, width=5)
	entryb.grid(row=2, column=3, padx=5, pady=5)
	var1 = IntVar()
	tex = Checkbutton(child, text="chess board", variable=var1)
	tex.grid(row=6, column=0, padx=5, pady=5)
	if (var[index].get() == "Plane"):
		lnorm = Label(child, text="normale (x, y, z)")
		lnorm.grid(row=3, column=0, padx=5, pady=5)
		normx =  Entry(child, width=5)
		normx.grid(row=3, column=1, padx=5, pady=5)
		normy =  Entry(child, width=5)
		normy.grid(row=3, column=2, padx=5, pady=5)
		normz =  Entry(child, width=5)
		normz.grid(row=3, column=3, padx=5, pady=5)
		ok = Button(child, text="OK", command= lambda a=index:
				get_object(a,entryx,entryy,entryz,var1,var[a], shapes, entryr,
					entryg, entryb, normx, normy, normz, None))
		ok.grid(row=4, column=3, padx=5, pady=5)
	elif (var[index].get() == "Cone" or var[index].get() == "Cylinder"):
		if (var[index].get() == "Cone"):
			text = "K:"
		else:
			text= "Radius:"
		kl = Label(child, text=text)
		kl.grid(row=4, column=0, padx=5, pady=5)
		kentry = Entry(child, width=5)
		kentry.grid(row=4, column=1, padx=5, pady=5)
		dirl = Label(child, text="Dir: (x, y, z)")
		dirl.grid(row=3, column=0, padx=5, pady=5)
		dirx = Entry(child, width=5)
		dirx.grid(row=3, column=1, padx=5, pady=5)
		diry = Entry(child, width=5)
		diry.grid(row=3, column=2, padx=5, pady=5)
		dirz = Entry(child, width=5)
		dirz.grid(row=3, column=3, padx=5, pady=5)
		ok = Button(child, text="OK", command= lambda a=index:
				get_object(a,entryx,entryy,entryz,var1,var[a], shapes, entryr,
					entryg, entryb, dirx, diry, dirz, kentry))
		ok.grid(row=6, column=3, padx=5, pady=5)
	elif (var[index].get() == "Sphere"):
		kl = Label(child, text="Radius")
		kl.grid(row=4, column=0, padx=5, pady=5)
		kentry = Entry(child, width=5)
		kentry.grid(row=4, column=1, padx=5, pady=5)
		ok = Button(child, text="OK", command= lambda a=index:
				get_object(a,entryx,entryy,entryz,var1,var[a], shapes, entryr,
					entryg, entryb, None, None, None, kentry))
		ok.grid(row=6, column=3, padx=5, pady=5)
