@EUDFunc
def f_f(A):
    B = EUDByteReader()
    B.seekepd(A)
    A << (B.k)
    _ATTW(B, 'k') << (1)
    _SV([A, _ATTW(B, 'k')], [3])
