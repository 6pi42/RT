import os
from objects import *

if os.name == 'posix':
	from Tkinter import *
	from tkColorChooser import *
elif os.name == 'nt':
	from tkinter import *
	from tkinter.colorchooser import *

def get_object(index, entryx, entryy, entryz, tex, var, shapes, red, blue, green, norx, nory, norz, rad, child, pt3x, pt3y, pt3z):
	pos = (entryx.get(), entryy.get(), entryz.get())
	stype = var.get()
	if (stype != 'Spotlight'):
		rgb = (red.get(), blue.get(), green.get())
	if (stype == "Plane"):
		nor = (norx.get(), nory.get(), norz.get())
		shapes[index] = Plane(stype, pos, rgb, tex.get(), nor)
	elif (stype == "Sphere"):
		shapes[index] = Sphere(stype, pos, rgb, tex.get(), rad.get())
	elif (stype == "Cylinder") :
		axis = (norx.get(), nory.get(), norz.get())
		shapes[index] = Cylinder(stype, pos, rgb, tex.get(), axis, rad.get())
	elif (stype == "Cone"):
		axis = (norx.get(), nory.get(), norz.get())
		shapes[index] = Cone(stype, pos, rgb, tex.get(), axis, rad.get())
	elif (stype == "Ellipsoid"):
		rad_axis = (norx.get(), nory.get(), norz.get())
		shapes[index] = Ellipsoid(stype, pos, rgb, tex.get(), rad_axis)
	elif (stype == "Cube"):
		pt2 = (norx.get(), nory.get(), norz.get())
		shapes[index] = Cube(pos, pt2, rgb)
	elif (stype == "Triangle"):
		pt2 = (norx.get(), nory.get(), norz.get())
		pt3 = (pt3x.get(), pt3y.get(), pt3z.get())
		shapes[index] = Triangle(pos, pt2, pt3, rgb)
	elif (stype == "Cercle"):
		dire = (norx.get(), nory.get(), norz.get())
		rad = rad.get()
		shapes[index] = Cercle(pos, dire, rgb, rad)
	elif (stype == 'Spotlight'):
		shapes[index] = Spotlight(pos)

	child.destroy()

def add_shape(drop, root, var, shapelst, edit, shapes):
	var.append(StringVar())
	var[len(var) - 1].set(shapelst[0])
	drop.append(OptionMenu(root, var[len(var) - 1], *shapelst))
	drop[len(drop) - 1].grid(row=len(drop) + 4, column=0, padx=5,pady=5)
	edit.append(Button(root, text="edit",
		command= lambda a=len(edit):edit_shape(a, shapelst, var, shapes)))
	edit[len(edit) - 1].grid(row=len(drop) + 4, column=1, padx=5, pady=5)
	shapes.append(-1)

def less_shape(drop, root, var, shapelst, edit, shapes):
	if len(drop) > 1:
		drop[len(drop) - 1].grid_forget()
		var.pop()
		drop.pop()
		edit[len(edit) - 1].grid_forget()
		edit.pop()
		shapes.pop()


def edit_shape(index, shapelst, var, shapes):
	child = Toplevel()
	child.title('Object:' + str(var[index].get()))
	if (var[index].get() == "Cube" or var[index].get() == "Triangle"):
		text = "Pt1: (x, y , z)"
	else:
		text = "Pos: (x, y, z)"
	posl = Label(child, text="Pos: (x, y, z)")
	posl.grid(row=1, column=0, padx=5, pady=5)
	entryx = Entry(child, width=5)
	entryx.grid(row=1, column=1, padx=5, pady=5)
	entryy = Entry(child, width=5)
	entryy.grid(row=1, column=2, padx=5, pady=5)
	entryz = Entry(child, width = 5)
	entryz.grid(row=1, column=3, padx=5, pady=5)
	var1 = IntVar()
	if (var[index].get() == 'Spotlight'):
		ok = Button(child, text="OK", command= lambda a=index:
				get_object(a,entryx,entryy,entryz,var1,var[a], shapes, None,
					None, None, None, None, None, None, child, None, None, None))
		ok.grid(row=4, column=3, padx=5, pady=5)
		return 1
	rgbl = Label(child, text="RGB: (R, G, B)")
	rgbl.grid(row=2, column=0, padx=5, pady=5)
	entryr = Entry(child, width=5)
	entryr.grid(row=2, column=1, padx=5, pady=5)
	entryg = Entry(child, width=5)
	entryg.grid(row=2, column=2, padx=5, pady=5)
	entryb = Entry(child, width=5)
	entryb.grid(row=2, column=3, padx=5, pady=5)
	if (var[index].get() == "Plane"):
		tex = Checkbutton(child, text="chess board", variable=var1)
		tex.grid(row=6, column=0, padx=5, pady=5)
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
					entryg, entryb, normx, normy, normz, None, child, None, None, None))
		ok.grid(row=4, column=3, padx=5, pady=5)
	elif (var[index].get() == "Cone" or var[index].get() == "Cylinder"):
		if (var[index].get() == "Cone"):
			text = "K:"
		else:
			text= "Radius:"
		tex = Checkbutton(child, text="chess board", variable=var1)
		tex.grid(row=6, column=0, padx=5, pady=5)
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
					entryg, entryb, dirx, diry, dirz, kentry, child, None, None, None))
		ok.grid(row=6, column=3, padx=5, pady=5)
	elif (var[index].get() == "Sphere"):
		tex = Checkbutton(child, text="chess board", variable=var1)
		tex.grid(row=6, column=0, padx=5, pady=5)
		kl = Label(child, text="Radius")
		kl.grid(row=4, column=0, padx=5, pady=5)
		kentry = Entry(child, width=5)
		kentry.grid(row=4, column=1, padx=5, pady=5)
		ok = Button(child, text="OK", command= lambda a=index:
				get_object(a,entryx,entryy,entryz,var1,var[a], shapes, entryr,
					entryg, entryb, None, None, None, kentry, child, None, None, None))
		ok.grid(row=6, column=3, padx=5, pady=5)
	elif (var[index].get() == "Ellipsoid"):
		tex = Checkbutton(child, text="chess board", variable=var1)
		tex.grid(row=6, column=0, padx=5, pady=5)
		dirl = Label(child, text="Rad: (x, y, z)")
		dirl.grid(row=3, column=0, padx=5, pady=5)
		dirx = Entry(child, width=5)
		dirx.grid(row=3, column=1, padx=5, pady=5)
		diry = Entry(child, width=5)
		diry.grid(row=3, column=2, padx=5, pady=5)
		dirz = Entry(child, width=5)
		dirz.grid(row=3, column=3, padx=5, pady=5)
		ok = Button(child, text="OK", command= lambda a=index:
			get_object(a,entryx,entryy,entryz,var1,var[a], shapes, entryr,
				entryg, entryb, dirx, diry, dirz, None, child, None, None, None))
		ok.grid(row=6, column=3, padx=5, pady=5)
	elif (var[index].get() == "Cube"):
		dirl = Label(child, text="Pt2: (x, y, z)")
		dirl.grid(row=3, column=0, padx=5, pady=5)
		dirx = Entry(child, width=5)
		dirx.grid(row=3, column=1, padx=5, pady=5)
		diry = Entry(child, width=5)
		diry.grid(row=3, column=2, padx=5, pady=5)
		dirz = Entry(child, width=5)
		dirz.grid(row=3, column=3, padx=5, pady=5)
		ok = Button(child, text="OK", command= lambda a=index:
			get_object(a,entryx,entryy,entryz,var1,var[a], shapes, entryr,
				entryg, entryb, dirx, diry, dirz, None, child, None, None, None))
		ok.grid(row=6, column=3, padx=5, pady=5)
	elif (var[index].get() == "Triangle"):
		pt2l = Label(child, text="Pt2: (x, y, z)")
		pt2l.grid(row=3, column=0, padx=5, pady=5)
		pt2x = Entry(child, width=5)
		pt2x.grid(row=3, column=1, padx=5, pady=5)
		pt2y = Entry(child, width=5)
		pt2y.grid(row=3, column=2, padx=5, pady=5)
		pt2z = Entry(child, width=5)
		pt2z.grid(row=3, column=3, padx=5, pady=5)
		pt3l = Label(child, text="Pt2: (x, y, z)")
		pt3l.grid(row=4, column=0, padx=5, pady=5)
		pt3x = Entry(child, width=5)
		pt3x.grid(row=4, column=1, padx=5, pady=5)
		pt3y = Entry(child, width=5)
		pt3y.grid(row=4, column=2, padx=5, pady=5)
		pt3z = Entry(child, width=5)
		pt3z.grid(row=4, column=3, padx=5, pady=5)
		ok = Button(child, text="OK", command= lambda a=index: get_object(a, entryx,
			entryy, entryz, var1, var[a], shapes, entryr, entryg, entryb,
			pt2x, pt2y, pt2z, None, child, pt3x, pt3y, pt3z))
		ok.grid(row=6, column=3, padx=5, pady=5)
	elif (var[index].get() == "Cercle"):
		dirl = Label(child, text="Dir: (x, y, z)")
		dirl.grid(row=3, column=0, padx=5, pady=5)
		dirx = Entry(child, width=5)
		dirx.grid(row=3, column=1, padx=5, pady=5)
		diry = Entry(child, width=5)
		diry.grid(row=3, column=2, padx=5, pady=5)
		dirz = Entry(child, width=5)
		dirz.grid(row=3, column=3, padx=5, pady=5)
		radl = Label(child, text="Radius:")
		radl.grid(row=4, column=0, padx=5, pady=5)
		rad = Entry(child, width=5)
		rad.grid(row=4, column=1, padx=5, pady=5)
		ok = Button(child, text="OK", command= lambda a=index: get_object(a, entryx,
			entryy, entryz, var1, var[a], shapes, entryr, entryg, entryb,
			dirx, diry, dirz, rad, child, None, None, None))
		ok.grid(row=6, column=3, padx=5, pady=5)





def create_file(shapes, titlel, widthl, heightl, samplingl):
	sampling = samplingl.get()
	sampling = sampling[len(sampling) - 1]
	title = titlel.get()
	width = widthl.get()
	height = heightl.get()
	try:
		width = int(width)
		height = int(height)
		sampling = int(sampling)
	except ValueError:
		print "Height and Width must be integer"
		exit()
	if (os.path.isfile(title)):
		print "file already exist"
		exit()
	fichier = open(str(title), "a")
	fichier.write("SCENE\n\tWINDOW\n\t\twidth: " + str(width) + ".0\n\t\theight: " + str(height) +
		".0\n\n\tMULTI_SAMPLING\n\t\tpower: " + str(sampling) + "\n\n")
	fichier.write("SHAPES\n")
	j = 0

	for i in shapes:
		i.write(fichier)
	for i in shapes:
		try:
			i.write(fichier)
			j += 1
		except:
			print "error of writing: Object: " + str(j)
			return 0
	fichier.close()
	exit()
