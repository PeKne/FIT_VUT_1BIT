from collections import namedtuple
import mathlib
import math
## isSign checks whether a given character is "+" or "-".
#  @param character The character to check.
#  @returns True when the character is a sign character, otherwise False.
def isSign(character):
    return character == "+" or character == "-"

## isNumber checks if a given string is a valid floating point number.
#  @param character The string to check.
#  @returns True if the string is valid float.
def isNumber(string):
    try:
        float(string)
    except:
        return False
    return True

## CalcController handles view's events.
class CalcController:
    ## The constructor.
    #  @param view The reference to the view object.
    def __init__(self, view):
        ## @var view
        #  The reference to the view object.
        self.view = view
        ## @var tokens
        #  The list that holds tokens that make up an expression.
        self.tokens = []

    ## buttonPressed is called when button is pressed.
    #
    #  It appends the certain token that is associated with pressed button into the token list.
    #  @param token The value to add to the token list.
    def buttonPressed(self, token):
        self.tokens.append(token)
        self.viewTokens()

    ## clear is called when "clear button" is pressed.
    def clear(self):
        del self.tokens[:]  # delete all tokens
        self.view.render("")

    ## delete is called when "delete button" is pressed.
    def delete(self):
        if len(self.tokens) == 0:
            return
        del self.tokens[len(self.tokens)-1] # delete last token
        self.viewTokens()

    ## viewTokens renders tokens onto the view.
    def viewTokens(self):
        txt = ""
        for token in self.tokens:
            txt += str(token)
        self.view.render(txt)

    ## evaluateUnaryFunctions evaluates functions in the expression that are unary.
    #  @param unaryFunctionDictonary
    #  @parblock
    #  The dictonary that uses operators as keys - e.g. "ln", "!".
    #
    #  Values of the dictonary are of the type UnaryFunction.
    #  UnaryFunction holds a reference to the functon that implements a certain operation,
    #  offset of the operad - e.g. for "ln5" offset is 1, for "5!" offset is -1.
    #  Then it holds type of the operand.
    #
    #  Tokens that represents the operation are replaced with the number.
    #  @endparblock
    def evaluateUnaryFunctions(self, unaryFunctionDictonary):
        i = 0
        while i < len(self.tokens):
            token = self.tokens[i]
            if token in unaryFunctionDictonary.keys():
                unaryFunction = unaryFunctionDictonary[token]
                if unaryFunction.operandOffset < 0:
                    if i+unaryFunction.operandOffset < 0:
                        raise SyntaxError("number expected before "+token)
                else:
                    if i+unaryFunction.operandOffset > len(self.tokens) - 1:
                        raise SyntaxError("number expected after "+token)
                try:
                    number = unaryFunction.operandType(self.tokens[i+unaryFunction.operandOffset])
                except:
                    raise SyntaxError(str(unaryFunction.operandType)+" expected before "+token)
                result = unaryFunction.function(number)
                if math.isnan(result):
                    raise ValueError("math error")
                del self.tokens[i-1]
                i = i - 1
                self.tokens[i] = str(result)
            i = i + 1

    ## evaluateBinaryFunctions evaluates funcitons in the expression that are binary.
    #  @param functionDictonary
    #  @parblock
    #  The dictonary that uses operators as keys - e.g. "+", "-", "*"
    #
    #  As for the values it stores, they are of type BinaryFunction.
    #  This type is capable of storing a reference to the function that implements
    #  a certain operation. Then it stores names of the operands.
    #
    #  Tokens that represents the operation are replaced with the number.
    #  @endparblock
    def evaluateBinaryFunctions(self, functionDictonary):
        i = 0
        while i < len(self.tokens):
            token = self.tokens[i]
            if token in functionDictonary.keys():
                binaryFunction = functionDictonary[token]
                if i-1 < 0:
                    raise SyntaxError("missing "+binaryFunction.firstOperandName)
                if i+1 > len(self.tokens)-1:
                    raise SyntaxError("missing "+binaryFunction.secondOperandName)
                try:
                    a = float(self.tokens[i-1])
                except:
                    raise SyntaxError(binaryFunction.firstOperandName+" has to be a number")
                try:
                    b = float(self.tokens[i+1])
                except:
                    raise SyntaxError(binaryFunction.secondOperandName+" has to be a number")
                result = binaryFunction.function(a, b)
                if math.isnan(result):
                    raise ValueError("math error")
                del self.tokens[i-1]
                del self.tokens[i]
                i = i - 1
                self.tokens[i] = str(result)
            i += 1

    ## joinNumbers joins digits into numbers.
    def joinNumbers(self):
        i = 0
        numberString=""
        foundNumber=False
        while i < len(self.tokens):
            if numberString == "":
                start = i
            numberString+=self.tokens[i]
            try:
                float(numberString)
                if i == len(self.tokens)-1: # last token
                    subArray=self.tokens[start:]
                    numberString = "".join(subArray)
                    for j in range(start,len(self.tokens)):
                        del self.tokens[start]
                    self.tokens.insert(start, numberString)
                foundNumber=True
            except:
                if not foundNumber:
                    i=i+1
                    numberString=""
                    foundNumber=False # not realy necessary, but...
                    continue
                subArray=self.tokens[start:i]
                numberString="".join(subArray)
                for j in range(start, i):
                    del self.tokens[start]
                self.tokens.insert(start,numberString)
                numberString=""
                foundNumber=False
                i=start
            i=i+1

    ## joinTokens joins tokens that are at given indexies.
    #  @param first The index of the first token.
    #  @param second The index of the second token.
    def joinTokens(self, first, second):
        value = self.tokens[second]
        del self.tokens[second]
        self.tokens[first] = self.tokens[first]+value

    ## stickSignsToNumbers joins extra signs with numbers they belong to.
    def stickSignsToNumbers(self):
        # -3
        if len(self.tokens) > 1 and isSign(self.tokens[0]) and isNumber(self.tokens[1]):
            self.joinTokens(0, 1)
        # --3 | -+3 | +-3 | ++3
        if len(self.tokens) > 2 and isSign(self.tokens[0]) and isSign(self.tokens[1]) and isNumber(self.tokens[2]):
            if self.tokens[0] == "-":
                if self.tokens[1] == "-":
                    self.tokens[1] = "+"
                else:
                    self.tokens[1] = "-"
            del self.tokens[0]
            self.joinTokens(0, 1)
        i=1
        while i < len(self.tokens)-1:
            if isSign(self.tokens[i]) and isSign(self.tokens[i-1]) and isNumber(self.tokens[i+1]):
                self.joinTokens(i, i+1)
            i+=1

    ## joinFlotingPoints joins floating points with numbers.
    #
    #  In fact this funciton covers only ".x" case others are covered by function joinNumbers.
    def joinFlotingPoints(self):
        # "x.x" and "x." cases are covered by joinNumbers
        # need to cover .x case
        if self.tokens[0] == "." and isNumber(self.tokens[1]) and float(self.tokens[1]).is_integer():
            # join
            del self.tokens[0]
            self.tokens[0] = "." + self.tokens[0]
        l = len(self.tokens)

        i = 1
        while i < len(self.tokens)-1:
            if self.tokens[i] == "." and isNumber(self.tokens[i+1]) and float(self.tokens[i+1]).is_integer():
                numb = "." + self.tokens[i+1]
                del self.tokens[i]
                del self.tokens[i]
                self.tokens.insert(i, numb)
            i=i+1

    ## evaluate evaluates the expression user entered.
    #
    #  It gets called when "evaluation button" is pressed (-> "=").
    #  It sticks extra signs to numbers, then it creates numbers from separated digits and
    #  joins floating points to them.
    #  Here is how functions are evaluated:
    #   1. factorial, natural logarithm
    #   2. power, root
    #   3. multiplication, division
    #   4. summation, subtraction
    def evaluate(self):
        self.stickSignsToNumbers()
        self.joinNumbers()
        self.joinFlotingPoints()
        UnaryFunction = namedtuple("UnaryFunction", "function operandOffset operandType")
        unaryFunctionDictonary = {
            "!" : UnaryFunction(mathlib.factorial, -1, int),
            "ln": UnaryFunction(mathlib.log, 1, float)
        }
        try:
            self.evaluateUnaryFunctions(unaryFunctionDictonary)

            BinaryFunction = namedtuple("BinaryFunction", "function firstOperandName secondOperandName")
            binaryFunctionDictonary = {
                "^" : BinaryFunction(mathlib.pow, "base", "exponent"),
                "√" : BinaryFunction(mathlib.root, "index of root", "radicand")
            }
            self.evaluateBinaryFunctions(binaryFunctionDictonary)
            binaryFunctionDictonary = {
                "*" : BinaryFunction(mathlib.mul, "multiplicand", "multiplier"),
                "/" : BinaryFunction(mathlib.div, "dividend", "divisor")
            }

            self.evaluateBinaryFunctions(binaryFunctionDictonary)
            binaryFunctionDictonary = {
                "+" : BinaryFunction(mathlib.sum, "addend", "addend"),
                "-" : BinaryFunction(mathlib.sub, "minuend", "subtrahend")
            }
            self.evaluateBinaryFunctions(binaryFunctionDictonary)
            if len(self.tokens) > 1:
                raise SyntaxError("Syntax error")
            self.viewTokens()
        except Exception as e:
            self.clear()
            self.view.render(e)
