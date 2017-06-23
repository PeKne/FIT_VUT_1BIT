from CalcController import *
from tkinter import *
from tkinter import ttk
## Calc represents user interface - view.
class Calc(Tk):
    ## The constructor.
    def __init__(self):
        super().__init__() # call parent's init
        ## @var controller
        #  The reference to the controller object.
        self.controller = CalcController(self)
        ## @var inputEntryString
        #  StringVar that is associated with the input entry.
        self.inputEntryString = StringVar() # this is where input from the entry is stored
        self.defineUI()

    ## defineUI defines user interface.
    def defineUI(self):
        self.title("Pejaja calculator")
        # fill first cell of window and put it into the center
        mainframe = ttk.Frame(self, padding="10 5")
        mainframe.grid(column = 1, row = 1)
        entryFrame = ttk.Frame(mainframe, padding="0 5")
        entryFrame.grid(column=1, row=1, columnspan=2)
        inputEntry = ttk.Entry(entryFrame, textvariable=self.inputEntryString)
        inputEntry.grid(column = 1, row=1)
        # left frame
        left = ttk.Frame(mainframe)
        left.grid(column = 1, row = 2)
        # no need to reach anybutton from anywhere, no need to store any button
        value = 0
        # values <1,9> in buttons
        for row in range(2, 5):
            for column in range(1, 4):
                value += 1
                ttk.Button(left, text = str(value), width=4, command=lambda value=value: self.controller.buttonPressed(str(value))).grid(column=column, row=row)
        ttk.Button(left, text = "0", command=lambda: self.controller.buttonPressed("0")).grid(column=1, row=5, columnspan=4,sticky="we")

        # right frame
        right = ttk.Frame(mainframe, padding="5 0 0 0")
        right.grid(column=2, row=2)
        ttk.Button(right, text = "+", width=4, command=lambda: self.controller.buttonPressed("+")).grid(column=1, row=1)
        ttk.Button(right, text = "-", width=4, command=lambda: self.controller.buttonPressed("-")).grid(column=2, row=1)
        ttk.Button(right, text = "*", width=4, command=lambda: self.controller.buttonPressed("*")).grid(column=3, row=1)
        ttk.Button(right, text = "/", width=4, command=lambda: self.controller.buttonPressed("/")).grid(column=4, row=1)

        ttk.Button(right, text = "!", width=4, command=lambda: self.controller.buttonPressed("!")).grid(column=1, row=2)
        ttk.Button(right, text = "^", width=4, command=lambda: self.controller.buttonPressed("^")).grid(column=2, row=2)
        ttk.Button(right, text = "√", width=4, command=lambda: self.controller.buttonPressed("√")).grid(column=3, row=2)
        ttk.Button(right, text = "ln", width=4, command=lambda: self.controller.buttonPressed("ln")).grid(column=4, row=2)

        ttk.Button(right, text = "del", command=self.controller.delete).grid(column=1, row=3, columnspan=2, sticky="we")
        ttk.Button(right, text = "clear", command=self.controller.clear).grid(column=3, row=3,columnspan=2, sticky="we")

        ttk.Button(right, text = "=", command=self.controller.evaluate).grid(column=1, row=4, columnspan=2,sticky="we")
        ttk.Button(right, text = ".", command=lambda: self.controller.buttonPressed(".")).grid(column=3, row=4, columnspan=2,sticky="we")

    ## render renders state to the input entry.
    def render(self, state):
        self.inputEntryString.set(state)
calc = Calc()
calc.mainloop()
