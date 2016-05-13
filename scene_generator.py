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
title.grid(row=0, column=2, padx = 5, pady = 5)
title.insert(0, "Scene Name")

shapelst = ['Plan','Sphere','Cylindre','Cone']
var = list()
var.append(StringVar())
var[0].set(shapelst[0])

drop = list()
drop.append(OptionMenu(root,var[0],*shapelst))
drop[0].grid(row = 2, column=0, padx=5, pady=5)

add_button = Button(root, text = "more shape",
            command = lambda: add_shape(drop, root, var, shapelst))
add_button.grid(row = 1, column=0, padx=5, pady=5)


root.mainloop()
