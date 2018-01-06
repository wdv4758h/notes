Message Authentication Code
===============================================================================

Message Authentication Functions
----------------------------------------------------------------------

- Lower level function: 本章

- Higher level function


Lower level function: authenticator

    - Hash function

    - Message encryption

    - Message Authentication Code (MAC)


FCS: Frame check sequence, aka checksum
為了做 error-detection，要做在 encryption 之前。

兩種做法, figer 12.2：

    - internal error control

    - external error control


Public-Key encryption 慢，作為最後手段。


Brute-Force Attack
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

- key space

- MAC 的長度加長


HMAC: MAC based on Hash functions
----------------------------------------------------------------------

Y 從 msg 切 block

Hash((pad(K) XOR opad),
     Hash(IV, (pad(K) XOR ipad) concate Y))


還有 precomute 版本？為了效率


Security

取決於 hash function 的強度。


MAC based on Block Cipher: DAA and CMAC
----------------------------------------------------------------------

DAA: out-of-date

CMAC: DAA 的加強版


Counter with Ciper Block Chaining Message Authentication Code(CCM)
----------------------------------------------------------------------

Algo

CCM

CGM



Key Wra 12.8
