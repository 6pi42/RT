from Tkinter import *

root = Tk()
root.title("Scene Generator")

def get_choice(*args):
    print(drop["menu"].index(var.get()))

def add_shape(drop, root, var, shapelst):
    var.append(StringVar())
    var[len(var) - 1].set(shapelst[0])
    drop.append(OptionMenu(root, var[len(var) - 1], *shapelst))
    drop[len(drop) - 1].grid(row=len(drop) + 4, column=0, padx=5,pady=5)




title = Entry(root)
title.grid(row=0, column=0, padx = 5, pady = 5)
title.insert(0, "Scene Name")

valid = Button(root, text="OK", commad=None)
valid.grid(row=0, column = 2, padx=5, pady=5)

widthl = Entry(root)
widthl.grid(row=1, column=0, padx = 5, pady = 5)
widthl.insert(0, "Width")

heightl = Entry(root)
heightl.grid(row=1, column=1, padx = 5, pady = 5)
heightl.insert(0, "height")

samplst = ['sampling: 0', 'sampling: 2', 'sampling: 4', 'sampling: 8']
sampvar = StringVar()
sampvar.set(samplst[0])
samp = OptionMenu(root, sampvar, *samplst)
samp.grid(row = 1, column = 2,pady = 5, padx = 5)

shapelst = ['Plan','Sphere','Cylindre','Cone']
var = list()
var.append(StringVar())
var[0].set(shapelst[0])

drop = list()
drop.append(OptionMenu(root,var[0],*shapelst))
drop[0].grid(row = 4, column=0, padx=5, pady=5)

add_button = Button(root, text = "more shape",
            command = lambda: add_shape(drop, root, var, shapelst))
add_button.grid(row = 2, column=0, padx=5, pady=5)


root.mainloop()
