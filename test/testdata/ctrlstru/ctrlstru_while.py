@EUDFunc
def f_x():
    if EUDWhile()(1 == 2):
        EUDContinue()
    EUDEndWhile()
    if EUDWhile()(Always(), neg=True):
        EUDContinue()
    EUDEndWhile()
