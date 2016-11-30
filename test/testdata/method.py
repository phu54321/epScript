@EUDFunc
def f_f(A):
    B = EUDByteReader()
    B.seekepd(A)
    A << B.k
    _FWARP(B, 'k') << 1
    _SV([A, _FWARP(B, 'k')], [3])
